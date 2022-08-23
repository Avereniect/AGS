//
// Created by avereniect on 8/22/22.
//

#ifndef AGS_THREADING_TASK_HPP
#define AGS_THREADING_TASK_HPP

#include <cstdint>
#include <functional>

namespace ags::threading {

    using task_family_id_type = std::uint64_t;

    using callable_type = std::function<void()>;

    struct Task {

        //=================================================
        // Constructors
        //=================================================

        template<class C>
        explicit Task(C callable):
            callable(callable) {}

        template<class C, class...Args>
        explicit Task(C callable, Args&&...args):
            callable(
                [callable, args...] () {
                    callable(args...);
                }
            ),
            wait_id() {}

        template<class C>
        explicit Task(task_family_id_type wait_id, C callable):
            callable(callable),
            wait_id(wait_id) {}

        template<class C, class...Args>
        explicit Task(task_family_id_type wait_id, C callable, Args&&...args):
            callable(
                [callable, args...] () {
                    callable(args...);
                }
            ),
            wait_id(wait_id) {}

        //=================================================
        // Instance members
        //=================================================

        callable_type callable{};

        task_family_id_type wait_id = 0;

    };

    struct Thread_pool_task {

        //=================================================
        // -ctors
        //=================================================

        Thread_pool_task(task_family_id_type task_family, task_family_id_type wait_family, std::function<void()> func):
            task_family(task_family),
            wait_family(wait_family),
            callable(std::move(func)) {}

        Thread_pool_task() = default;

        Thread_pool_task(const Thread_pool_task&) = delete;

        Thread_pool_task(Thread_pool_task&& task) noexcept:
            task_family(std::exchange(task.task_family, 0)),
            wait_family(std::exchange(task.wait_family, 0)),
            callable(std::exchange(task.callable, {})) {}

        ~Thread_pool_task() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Thread_pool_task& operator=(const Thread_pool_task&) = delete;

        Thread_pool_task& operator=(Thread_pool_task&& rhs) noexcept {
            task_family = std::exchange(rhs.task_family, 0);
            wait_family = std::exchange(rhs.wait_family, 0);
            callable = std::exchange(rhs.callable, {});

            return *this;
        }

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Family to which the current task belongs
        ///
        task_family_id_type task_family = 0;

        ///
        /// Task family on which the task should wait on
        ///
        task_family_id_type wait_family = 0;

        ///
        /// The object which should be called
        ///
        std::function<void()> callable{};

    };

}

#endif //AGS_THREADING_TASK_HPP
