#ifndef AGS_LOCKED_QUEUE_HPP
#define AGS_LOCKED_QUEUE_HPP

#include "aul/containers/Circular_array.hpp"

#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>
#include <optional>
#include <atomic>

namespace ags::threading {

    template<class T>
    class Locked_queue {
    public:

        //=================================================
        // -ctors
        //=================================================

        Locked_queue() = default;
        Locked_queue(const Locked_queue&) = delete;
        Locked_queue(Locked_queue&&) noexcept = delete;

        ~Locked_queue() {
            destruction_flag = true;
            wake_condition_var.notify_all();

            // Spin lock may not be ideal
            while (waiting_counter) {}
        }

        //=================================================
        // Assignment operators
        //=================================================

        Locked_queue& operator=(const Locked_queue&) = delete;
        Locked_queue& operator=(Locked_queue&&) noexcept = delete;

        //=================================================
        // Mutators
        //=================================================

        template<class...Args>
        void emplace_back(Args&&...args) {
            if (destruction_flag) {
                return;
            }

            std::unique_lock lk{backing_array_mutex};
            backing_array.emplace_back(std::forward(args...));
        }

        ///
        /// \param v Value to push onto queue
        void push_back(const T& v) {
            if (destruction_flag) {
                return;
            }

            std::unique_lock lk{backing_array_mutex};
            backing_array.push_back(v);
        }

        ///
        /// Attempts to pop an element from the queue. If no such element
        /// exists, blocks the calling thread until either the data is available
        /// or until the Locked_queue object is destroyed. If the function
        /// returned because an element became available, then the object will
        /// be present in the returned object. If the function returned because
        /// the Locked_queue object was destroyed, then the returned value will
        /// be falsy.
        ///
        /// \return std::optional object which contains any element which may
        /// have been popped from the queue
        [[nodiscard]]
        std::optional<T> wait_pop() {
            if (destruction_flag) {
                return {};
            }

            std::unique_lock lk{backing_array_mutex};

            auto wake_predicate = [this] () -> bool {
                return destruction_flag || !backing_array.empty();
            };

            waiting_counter += 1;
            wake_condition_var.wait(lk, wake_predicate);

            if (destruction_flag) {
                waiting_counter -= 1;
                return {};
            } else {
                std::optional<T> ret{std::move(backing_array.front())};
                backing_array.pop_front();
                waiting_counter -= 1;
                return ret;
            }
        }

        ///
        /// Attempts to pop an element from the queue. If an element is
        /// available, the returned object is truthy, containing the popped
        /// element. If no such element exists, returns immediately and the
        /// returned object is falsy.
        ///
        /// \return std::optional object which contains any element which may
        /// have been popped from the queue
        [[nodiscard]]
        std::optional<T> try_pop() {
            if (destruction_flag) {
                return {};
            }

            std::scoped_lock lk{backing_array_mutex};

            if (backing_array.empty() || destruction_flag) {
                return {};
            } else {
                std::optional<T> ret{std::move(backing_array.front())};
                backing_array.pop_front();
                return ret;
            }
        }

        //=================================================
        // Accessors
        //=================================================

        ///
        /// \return True if there are no elements in the queue, false otherwise
        [[nodiscard]]
        bool empty() {
            if (destruction_flag) {
                return true;
            }

            std::scoped_lock lk{backing_array_mutex};
            return backing_array.empty();
        }

        ///
        /// \return Number of elements in queue
        [[nodiscard]]
        std::size_t size() {
            if (destruction_flag) {
                return 0;
            }

            std::scoped_lock lk{backing_array_mutex};
            return backing_array.size();
        }

    private:

        //=================================================
        // Instance Members
        //=================================================

        ///
        /// Flag that is set when the queue is about to be destroyed.
        ///
        std::atomic_bool destruction_flag = false;

        ///
        ///
        ///
        std::atomic_int_least32_t waiting_counter = 0;

        ///
        /// Mutex used to guard backing_array
        ///
        std::mutex backing_array_mutex;

        ///
        /// Container used to store queue contents
        ///
        aul::Circular_array<T> backing_array;

        ///
        /// Condition variable that's used to notify waiting threads that an
        /// element is available
        ///
        std::condition_variable wake_condition_var;

    };

}

#endif //AGS_LOCKED_QUEUE_HPP
