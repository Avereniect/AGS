//
// Created by avereniect on 5/21/22.
//
#include "Work_sharing_thread_pool.hpp"

#include <chrono>
#include <iostream>
#include <aul/Algorithms.hpp>

namespace ags::threading {

    //=====================================================
    // Type aliases
    //=====================================================

    using size_type = Work_sharing_thread_pool::size_type;

    //=====================================================
    // -ctors
    //=====================================================

    Work_sharing_thread_pool::Work_sharing_thread_pool(size_type thread_count):
        m(std::make_unique<Work_sharing_thread_pool_members>()) {

        thread_count = std::max(size_type(1), thread_count);
        m->threads.reserve(thread_count);
        for (size_type i = 0; i < thread_count; ++i) {
            m->threads.emplace_back(thread_worker, i, this);
        }
    }

    Work_sharing_thread_pool::Work_sharing_thread_pool(ags::threading::Work_sharing_thread_pool&& other) noexcept:
        m(std::move(other.m)) {}

    Work_sharing_thread_pool::~Work_sharing_thread_pool() {
        terminate_threads();
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    Work_sharing_thread_pool& Work_sharing_thread_pool::operator=(ags::threading::Work_sharing_thread_pool&& rhs) noexcept {
        m = std::move(rhs.m);
        return *this;
    }

    //=====================================================
    // Mutators
    //=====================================================

    void Work_sharing_thread_pool::start() {
        m->pause_flag = false;
        m->continue_condition_var.notify_all();
    }

    void Work_sharing_thread_pool::pause() {
        m->pause_flag = true;
    }

    void Work_sharing_thread_pool::stop_wait() {
        pause();

        auto wake_predicate = [&] () {
            return m->active_thread_count == 0;
        };

        std::unique_lock lock{m->active_thread_count_mutex};
        if (!wake_predicate()) {
            m->threads_paused_condition_var.wait(lock);
        }
    }

    void Work_sharing_thread_pool::wait() {
        start();

        auto wake_predicate = [&] () {
            if (!m->ready_task_queue.empty()) {
                return false;
            } else {
                //Use of try_lock prevents deadlock with workers attempting to
                //move tasks to ready_task_queue from waiting_task_queue
                if (m->waiting_task_queue_mutex.try_lock()) {
                    bool ret = m->waiting_task_queue.empty();
                    m->waiting_task_queue_mutex.unlock();
                    return ret;
                } else {
                    return false;
                }
            }
        };

        std::unique_lock lock{m->ready_task_queue_mutex};
        if (!wake_predicate()) {
            m->wait_condition_var.wait(lock);
        }
    }

    //=====================================================
    // Misc. mutators
    //=====================================================

    void Work_sharing_thread_pool::clear_tasks() {
        {
            std::lock_guard lk{m->ready_task_queue_mutex};
            m->ready_task_queue.clear();
        }

        {
            std::lock_guard lk{m->waiting_task_queue_mutex};
            m->waiting_task_queue.clear();
        }
    }

    //=====================================================
    // Accessors
    //=====================================================

    size_type Work_sharing_thread_pool::task_count() {
        size_type ret = 0;

        m->ready_task_queue_mutex.lock();
        ret += m->ready_task_queue.size();
        m->ready_task_queue_mutex.unlock();

        m->waiting_task_queue_mutex.lock();
        ret += m->waiting_task_queue.size();
        m->waiting_task_queue_mutex.unlock();

        return ret;
    }

    size_type Work_sharing_thread_pool::thread_count() const {
        return m->threads.size();
    }

    //=====================================================
    // Helper functions
    //=====================================================

    void Work_sharing_thread_pool::terminate_threads() {
        if (m->terminate_flag) {
            return;
        }

        m->terminate_flag = true;

        for (auto& th : m->threads) {
            m->continue_condition_var.notify_all();
            th.join();
        }
    }

    void Work_sharing_thread_pool::thread_worker(size_type thread_index, Work_sharing_thread_pool* pool_ptr) {
        auto& pool = *pool_ptr->m;

        //
        // Lambda function used as parameter to wait function on condition
        // variables. Returns true should the thread need to wake up.
        //
        // Should wake if there is work available and the pause flag is not set
        // Should wake if the terminate flag was set
        //
        auto wake_predicate = [&pool] () {
            return
                (!pool.ready_task_queue.empty() && !pool.pause_flag) ||
                pool.terminate_flag;
        };

        {
            std::lock_guard lk{pool.active_thread_count_mutex};
            pool.active_thread_count += 1;
        }

        while (true) {
            Thread_pool_task task{};

            {
                std::unique_lock ready_task_queue_lk{pool.ready_task_queue_mutex};

                //Handle termination
                if (pool.terminate_flag) {
                    return;
                }

                //Handle idling
                if (pool.ready_task_queue.empty() || pool.pause_flag) {
                    // Signals pool-owning thread that the current thread is going
                    // to be idling
                    {
                        std::lock_guard lk{pool.active_thread_count_mutex};
                        pool.active_thread_count -= 1;
                        if (pool.active_thread_count == 0) {
                            pool.wait_condition_var.notify_one();
                            pool.threads_paused_condition_var.notify_one();
                        }
                    }

                    // Wait until the wake predicate yields true
                    if (!wake_predicate()) {
                        pool.continue_condition_var.wait(ready_task_queue_lk, wake_predicate);
                    }

                    {
                        std::lock_guard lk{pool.active_thread_count_mutex};
                        pool.active_thread_count += 1;
                    }

                    continue;
                }

                //Retrieve next available task
                task = std::move(pool.ready_task_queue.front());
                pool.ready_task_queue.pop_front();
            }

            try {
                task.callable();
            } catch (std::exception& e) {
                std::cerr << "Exception thrown in thread pool worker when invoking callable:\n"
                    << e.what() << std::endl;
            }

            //Check if this task was the last one in its family
            bool was_last_task = false;
            {
                std::lock_guard lk{pool.task_family_counts_mutex};
                auto it = pool.task_family_counts.find(task.task_family);
                if (it == pool.task_family_counts.end()) {
                    std::cerr << "This should never happen" << std::endl;
                }

                was_last_task = (*it == 1);

                if (was_last_task) {
                    pool.task_family_counts.erase(it);
                } else {
                    *it -= 1;
                }
            }

            // If it was, add tasks waiting on the family from the
            // waiting_task_queue to the ready queue.
            if (was_last_task) {
                //Although locking both may lead to additional contention, it
                //prevents a potential deadlock case when waiting for both
                //queues to be empty
                std::lock(
                    pool.ready_task_queue_mutex,
                    pool.waiting_task_queue_mutex
                );

                auto it0 = aul::binary_search(
                    pool.waiting_task_queue.begin(),
                    pool.waiting_task_queue.end(),
                    task.task_family,
                    wait_id_comparator
                );

                if (it0 == pool.waiting_task_queue.end()) {
                    //No tasks waiting on the current task were found, so we can
                    //continue with the next iteration a little sooner
                    pool.ready_task_queue_mutex.unlock();
                    pool.waiting_task_queue_mutex.unlock();
                    continue;
                }

                auto it1 = it0;
                while (it1->wait_family == task.task_family) {
                    ++it1;
                }

                //Add tasks to ready queue
                for (auto iter = it0; iter != it1; ++iter) {
                    pool.ready_task_queue.emplace_back(std::move(*iter));
                }

                //Remove tasks from waiting queue
                pool.waiting_task_queue.erase(it0, it1);

                pool.ready_task_queue_mutex.unlock();
                pool.waiting_task_queue_mutex.unlock();
            }
        }
    }

    bool Work_sharing_thread_pool::wait_id_comparator(const Thread_pool_task& lhs, task_family_id_type rhs) {
        return lhs.wait_family < rhs;
    }

}
