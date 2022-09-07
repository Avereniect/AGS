//
// Created by avereniect on 8/22/22.
//

#ifndef AGS_THREADING_WORK_STEALING_THREAD_POOL_HPP
#define AGS_THREADING_WORK_STEALING_THREAD_POOL_HPP

#include "Task.hpp"

#include <aul/containers/Circular_array.hpp>

#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace ags::threading {

    struct Work_stealing_thread_pool_members {

        ///
        /// Vectors of tasks
        ///
        std::vector<std::thread> threads{};

        ///
        ///
        ///
        std::vector<aul::Circular_array<Thread_pool_task>> local_queues{};

        ///
        ///
        ///
        std::vector<std::mutex> local_queue_mutexes{};

        ///
        ///
        ///
        aul::Circular_array<Thread_pool_task> shared_ready_queue{};

        ///
        ///
        ///
        std::mutex shared_ready_queue_mutex{};

        ///
        ///
        ///
        aul::Circular_array<Thread_pool_task> shared_waiting_queue{};

        ///
        ///
        ///
        std::mutex shared_waiting_queue_mutex{};

        ///
        ///
        ///
        std::uint32_t active_thread_count{};

    };

    class Work_stealing_thread_pool {
    public:



    private:

        //=================================================
        // Helper classes
        //=================================================

        struct Members;

        //=================================================
        // Instance members
        //=================================================

        std::unique_ptr<Members> m;

    };

}

#endif //AGS_THREADING_WORK_STEALING_THREAD_POOL_HPP
