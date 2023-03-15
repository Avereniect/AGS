#ifndef AGS_THREADING_WORK_SHARING_THREAD_POOL_HPP
#define AGS_THREADING_WORK_SHARING_THREAD_POOL_HPP

#include "Task.hpp"

#include <aul/containers/Circular_array.hpp>
#include <aul/containers/Array_map.hpp>

#include <cstdint>
#include <vector>
#include <list>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <atomic>
#include <condition_variable>

namespace ags::threading {

    struct Work_sharing_thread_pool_members {

        ///
        /// List containing threads in pool
        ///
        std::vector<std::thread> threads{};


        ///
        /// Variable used to keep track of next task id to return
        ///
        task_family_id_type free_id = 0;


        ///
        /// Queue containing tasks which are ready to be executed. Tasks are
        /// sorted by their task_family
        ///
        aul::Circular_array<Thread_pool_task> ready_task_queue{};

        ///
        /// Mutex used to lock access to ready_task_queue
        ///
        std::mutex ready_task_queue_mutex{};


        ///
        /// Queue containing tasks which are waiting on other tasks to be
        /// completed. Tasks are sorted by the wait_family.
        ///
        aul::Circular_array<Thread_pool_task> waiting_task_queue{};

        ///
        /// Mutex used to lock access to waiting_task_queue
        ///
        std::mutex waiting_task_queue_mutex{};



        ///
        /// Map which associates task family ids to the number of tasks enqueued
        /// that belong to them.
        ///
        aul::Array_map<task_family_id_type, std::uint32_t> task_family_counts;

        ///
        /// Mutex protecting task_family_counts
        ///
        std::mutex task_family_counts_mutex;


        ///
        /// Flag which indicates that worker threads should terminate after
        /// completing currently executing task.
        ///
        std::atomic_bool terminate_flag{false};

        ///
        /// Flag which indicates that worker threads should pop tasks from
        /// task_queue and execute them instead of idling. Should not be written
        /// to by worker threads
        ///
        std::atomic_bool pause_flag{false};



        ///
        /// Atomic counter that is used to
        ///
        ///
        ///count how many threads are not idling
        ///
        std::uint32_t active_thread_count = 0;

        ///
        /// Although active_thread_count is atomic, this mutex is required for
        /// using the use of idle_condition_var
        ///
        std::mutex active_thread_count_mutex{};


        ///
        /// Conditional variable that's used in the wait subroutine to wait on
        /// all tasks to complete.
        ///
        std::condition_variable wait_condition_var{};

        ///
        /// Conditional variable that's used in the wait subroutine to wait on
        /// all worker threads to complete their current task
        ///
        std::condition_variable threads_paused_condition_var{};

        ///
        /// Condition variable used to wake up idling threads
        ///
        std::condition_variable continue_condition_var;

    };

    class Work_sharing_thread_pool {
    public:

        struct Task_family;

        //=================================================
        // Type aliases
        //=================================================

        using size_type = std::size_t;

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param thread_count Number of threads which the thread pool should
        ///      have in reserve. Defaults to the hardware concurrency reported
        ///      by std::thread::hardware_concurrency
        explicit Work_sharing_thread_pool(size_type thread_count = std::thread::hardware_concurrency());

        Work_sharing_thread_pool(const Work_sharing_thread_pool&) = delete;

        Work_sharing_thread_pool(Work_sharing_thread_pool&&) noexcept;

        ///
        /// Tells current worker threads to terminate after completing their
        /// current task if it exists, or immediately if it does not. This
        /// thread wait for all worker threads to join before returning.
        ///
        ~Work_sharing_thread_pool();

        //=================================================
        // Assignment operators
        //=================================================

        Work_sharing_thread_pool& operator=(const Work_sharing_thread_pool&) = delete;

        Work_sharing_thread_pool& operator=(Work_sharing_thread_pool&&) noexcept;

        //=================================================
        // Thread worker management
        //=================================================

        ///
        /// Begin dispatching tasks to threads. Must be called before the thread
        /// pool will begin executing tasks
        ///
        void start();

        ///
        /// Stop dispatching tasks to threads. Will return immediately so tasks
        /// may still continue to execute afterwards. Call stop_wait() if
        /// wanting to ensure that all tasks currently in flight have completed.
        ///
        void pause();

        ///
        /// Stop dispatching tasks to threads and wait for workers to complete
        /// their current tasks before beginning to idle.
        ///
        void stop_wait();

        ///
        /// Waits for all currently enqueued tasks to complete before returning.
        ///
        void wait();

        //=================================================
        // Task submission
        //=================================================

        ///
        /// \tparam Func Callable type
        /// \param id ID of task family to wait on. Should be a value returned
        /// by an earlier call to submit. Submitting a value that does not meet
        /// this criteria is undefined behavior.
        /// \param f Callable object representing task that needs to be done.
        /// \return
        template<class Func>
        task_family_id_type submit(task_family_id_type wait_id, Func f) {
            m->free_id += 1;
            task_family_id_type family_id = m->free_id;

            {
                // Task family counts need to be updated before ready queue
                // since the task could and attempt to update its task family
                // count before this function returns.
                std::scoped_lock lk{m->task_family_counts_mutex};
                m->task_family_counts.emplace(family_id, 1);
            }
                //Add to waiting_task_queue at sorted position

                bool waiting_unnecessary = false;

            {
                if (wait_id == 0) {
                    waiting_unnecessary = true;
                } else {
                    std::unique_lock lk{m->task_family_counts_mutex};
                    waiting_unnecessary =
                        !m->task_family_counts.empty() &&
                        (wait_id < m->task_family_counts.keys()[0]);
                }
            }

            if (waiting_unnecessary) {
                {
                    std::scoped_lock lk{m->ready_task_queue_mutex};
                    m->ready_task_queue.emplace_back(family_id, wait_id, f);
                }

                if (!m->pause_flag) {
                    m->continue_condition_var.notify_one();
                }
            } else {
                std::scoped_lock lk{m->waiting_task_queue_mutex};
                auto it = aul::binary_search(
                    m->waiting_task_queue.begin(),
                    m->waiting_task_queue.end(),
                    wait_id,
                    wait_id_comparator
                );

                m->waiting_task_queue.emplace(it, family_id, wait_id, f);
            }

            return family_id;
        }

        ///
        /// \tparam Func Callable type
        /// \tparam Args Type of arguments passed when calling callable
        /// \param f Callable object
        /// \param args Arguments passed when calling callable
        template<class Func, class...Args>
        task_family_id_type submit(task_family_id_type wait_id, Func f, Args&&...args) {
            return submit(wait_id, f, args...);
        }

        ///
        /// \tparam Func Callable object type that takes no parameters and has
        ///     void return type
        /// \param f Function object to call
        template<class Func>
        task_family_id_type submit(Func f) {
            task_family_id_type default_id = 0;
            return submit(default_id, f);
        }

        ///
        /// \tparam Func Callable type
        /// \tparam Args Type of arguments passed when calling callable
        /// \param f Callable object
        /// \param args Arguments passed when calling callable
        template<class Func, class...Args>
        task_family_id_type submit(Func f, Args&&...args) {
            auto task = [f, args...] () {
                f(args...);
            };

            return submit(task);
        }

        /*
        task_family_id_type submit(std::vector<threading::Task>&& tasks) {
            free_id += 1;
            task_family_id_type family_id = free_id;

            //TODO: Complete implementation
        }
        */

        //=================================================
        // Misc. mutators
        //=================================================

        ///
        /// Remove all remaining tasks from queue
        ///
        void clear_tasks();

        //=================================================
        // Accessors
        //=================================================

        ///
        /// Performance note: This function requires the locking of two mutexes
        /// so calling it often is not advised.
        ///
        /// \return Number of remaining enqueued tasks
        [[nodiscard]]
        size_type task_count();

        ///
        /// \return Number of threads which the pool has.
        [[nodiscard]]
        size_type thread_count() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Pointer to struct containing the state associated with this thread
        /// pool.
        ///
        std::unique_ptr<Work_sharing_thread_pool_members> m;

        //=================================================
        // Helper functions
        //=================================================

        ///
        /// Sets the termination flag and waits until all threads in the thread
        /// pool have completed their tasks and waits for them to join with the
        /// current thread.
        ///
        void terminate_threads();

        ///
        /// \param thread_index Index of current thread in pool->threads
        /// \param pool Pointer to thread pool to which the thread belongs
        static void thread_worker(
            size_type thread_index,
            Work_sharing_thread_pool* pool
        );

        ///
        ///
        /// \param lhs
        /// \param rhs
        /// \return
        static bool wait_id_comparator(const Thread_pool_task& lhs, task_family_id_type rhs);

    };

}

#endif //AGS_THREADING_WORK_SHARING_THREAD_POOL_HPP
