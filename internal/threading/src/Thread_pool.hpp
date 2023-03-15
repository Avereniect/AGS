#ifndef AGS_THREAD_POOL_HPP
#define AGS_THREAD_POOL_HPP

#include <aul/containers/Array_map.hpp>
#include <aul/containers/Circular_array.hpp>

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <vector>
#include <queue>

#include <memory>

#include <cstdint>

#include <functional>

namespace ags::threading {

    class Thread_pool_queue{
    public:


    };

    ///
    /// An enum representing how work is allocated to worker threads within the
    /// thread pool.
    ///
    /// SHARING - Threads retrieve work from a single shared pool of work. May
    /// lead to subpar performance for due to synchronization overhead.
    ///
    /// STEALING - Threads retrieve multiple tasks at a time to store in
    /// thread-local queues. Work is stolen from other thread's local queue's if
    /// the main queue runs out of work to complete.
    ///
    enum class Task_allocation : std::uint8_t {
        SHARING,
        STEALING
    };

    constexpr Task_allocation TASK_SHARING = Task_allocation::SHARING;
    constexpr Task_allocation TASK_STEALING = Task_allocation::STEALING;



    ///
    /// An enum representing the order in which tasks are assigned to threads
    ///
    /// IN_ORDER - Tasks are assigned to threads in the order in which they were
    /// submitted. Incurs lower memory and synchronization overhead.
    ///
    /// PRIORITIZED - Tasks feature an associated priority and are completed in
    /// order from highest to lowest priority
    ///
    enum class Task_scheduling : std::uint8_t {
        IN_ORDER,
        PRIORITIZED
    };

    constexpr Task_scheduling IN_ORDER_SCHEDULING = Task_scheduling::IN_ORDER;
    constexpr Task_scheduling PRIORITIZED_SCHEDULING = Task_scheduling::PRIORITIZED;



    ///
    /// An enum representing the ways that tasks are grouped together
    ///
    /// INDIVIDUAL - Tasks are submitted individually. Incurs lower memory and
    /// synchronization overhead
    ///
    /// BATCHED - Tasks are submitted in batches.
    ///
    enum class Task_batching : std::uint8_t {
        INDIVIDUAL,
        BATCHED
    };

    constexpr Task_batching INDIVIDUAL_TASKS = Task_batching::INDIVIDUAL;
    constexpr Task_batching BATCHED_TASKS = Task_batching::BATCHED;



    ///
    /// An enum represent whether or not tasks/task batches can wait on each
    /// other.
    ///
    /// NO_WAITING - Tasks cannot be told to wait on other tasks. Incurs lower
    /// memory and synchronization overhead
    ///
    /// WAITING - Tasks can be told to wait on other tasks.
    ///
    enum class Task_waiting : std::uint8_t {
        NO_WAITING,
        WAITING
    };

    constexpr Task_waiting NO_TASK_WAITING = Task_waiting::NO_WAITING;
    constexpr Task_waiting TASK_WAITING = Task_waiting::WAITING;



    ///
    ///
    ///
    /// \tparam task_allocation
    /// \tparam task_scheduling
    /// \tparam task_batching
    /// \tparam task_waiting
    template<
        Task_allocation task_allocation,
        Task_scheduling task_scheduling,
        Task_batching task_batching,
        Task_waiting task_waiting
    >
    class Thread_pool_task;



    ///
    ///
    ///
    /// \tparam task_allocation
    /// \tparam task_scheduling
    /// \tparam task_batching
    /// \tparam task_waiting
    template<
        Task_allocation task_allocation,
        Task_scheduling task_scheduling,
        Task_batching task_batching,
        Task_waiting task_waiting
    >
    class Thread_pool_task {

    };

    namespace {

        struct Submission_id {
            std::uint32_t x;

            friend class Thread_pool_queue;
        };

        ///
        /// \tparam task_allocation
        /// \tparam task_scheduling
        /// \tparam task_batching
        /// \tparam task_waiting
        template<
            Task_allocation task_allocation,
            Task_scheduling task_scheduling,
            Task_batching task_batching,
            Task_waiting task_waiting
        >
        class Thread_pool_members {
        public:

            //=============================================
            // Type aliases
            //=============================================

            using Task = Thread_pool_task<
                task_allocation,
                task_scheduling,
                task_batching,
                task_waiting
            >;

            //=============================================
            // Instance members
            //=============================================

            // General members

            ///
            /// Contains threads used by thread pool to perform work
            ///
            std::vector<std::thread> threads{};

            ///
            /// Queue containing tasks which are ready to be executed. Tasks are
            /// sorted by their task_family
            ///
            aul::Circular_array<Task> primary_task_queue{};

            ///
            /// Mutex used to lock access to ready_task_queue
            ///
            std::mutex primary_task_queue_mutex{};

            // Thread communication members

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

    }


    ///
    /// \tparam task_allocation
    /// \tparam task_scheduling
    /// \tparam task_batching
    /// \tparam task_waiting
    template<
        Task_allocation task_allocation,
        Task_scheduling task_scheduling,
        Task_batching task_batching,
        Task_waiting task_waiting
    >
    class Thread_pool {
    public:

        //=================================================
        // Type Aliases
        //=================================================

        using Task = Thread_pool_task<
            task_allocation,
            task_scheduling,
            task_batching,
            task_waiting
        >;

    private:

        using Members = Thread_pool_members<
            task_allocation,
            task_scheduling,
            task_batching,
            task_waiting
        >;

    public:

        //=================================================
        // Type Aliases
        //=================================================



        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param thread_count Number of threads which the thread pool should
        /// have in reserve. Defaults to the value reported by
        /// std::thread::hardware_concurrency
        Thread_pool(std::size_t thread_count = std::thread::hardware_concurrency());

        Thread_pool(const Thread_pool&) = delete;
        Thread_pool(Thread_pool&&) noexcept;

        ///
        /// Tells current worker threads to terminate after completing their
        /// current task if it exists, or immediately if it does not. This
        /// thread wait for all worker threads to join before returning.
        ///
        ~Thread_pool();

        //=================================================
        // Assignment operators
        //=================================================

        Thread_pool& operator=(const Thread_pool&) = delete;
        Thread_pool& operator=(Thread_pool&&) noexcept;

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

        ///
        /// Blocks the current thread until the specified task(s) complete
        /// their execution
        ///
        /// \param task_id
        void wait(Submission_id submission_id);

        ///
        /// Remove all tasks from queue
        ///
        void clear_tasks();

        //=================================================
        // Task submission
        //=================================================

        ///
        /// \tparam Func Callable object type that takes no parameters and has
        ///     void return type
        /// \param f Function object to call
        template<class Func>
        void submit(Func f) {
            {
                std::lock_guard<std::mutex> lk{m->primary_task_queue_mutex};
                m->primary_task_queue.emplace_back(f);
            }

            if (!m->pause_flag) {
                //TODO: Signal any threads which may be currently waiting for a
                // task to complete
            }
        }

        ///
        /// \tparam Func Callable type
        /// \tparam Args Type of arguments passed when calling callable
        /// \param f Callable object
        /// \param args Arguments passed when calling callable
        template<class Func, class...Args>
        void submit(Func f, Args&&...args) {
            auto task = [f, args...] {
                f(args...);
            };

            submit_task(task);
        }

        //=================================================
        // Accessors
        //=================================================

        ///
        /// Performance note: This function requires the locking of mutexes
        /// so calling it often is not advised.
        ///
        /// \return Number of remaining enqueued tasks
        [[nodiscard]]
        std::size_t task_count() {
            std::lock_guard<std::mutex> lk{m->primary_task_queue_mutex};
            m->primary_task_queue.size();
        }

        ///
        ///
        /// \return Number of threads which the pool has.
        [[nodiscard]]
        std::size_t thread_count() const {
            m->threads.size();
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        std::unique_ptr<Members> m{};

    };

}

#endif //AGS_THREAD_POOL_HPP