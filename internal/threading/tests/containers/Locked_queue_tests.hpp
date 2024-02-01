#ifndef AGS_LOCKED_QUEUE_TESTS_HPP
#define AGS_LOCKED_QUEUE_TESTS_HPP

#include <gtest/gtest.h>

#include <ags/threading/Locked_queue.hpp>

#include <chrono>

namespace ags::threading::tests {

    using namespace std::chrono_literals;

    TEST(Locked_queue, Default_constructed) {
        Locked_queue<std::uint32_t> queue{};

        EXPECT_TRUE(queue.empty());
        EXPECT_EQ(queue.size(), 0);
    }

    TEST(Locked_queue, Try_pop_on_empty) {
        Locked_queue<std::uint32_t> queue{};

        auto thread_worker = [&queue] () {
            for (int i = 0; i < 128; ++i) {
                auto value = queue.try_pop();
                EXPECT_FALSE(value);
                std::this_thread::sleep_for(1ms);
            }
        };

        std::thread th0{thread_worker};
        std::thread th1{thread_worker};
        std::thread th2{thread_worker};
        std::thread th3{thread_worker};
        th0.join();
        th1.join();
        th2.join();
        th3.join();
    }

    TEST(Locked_queue, Wait_pop_on_empty) {
        using queue_type = Locked_queue<std::uint32_t>;

        auto queue_ptr = std::make_unique<queue_type>();

        auto thread_worker = [&queue_ptr] () {
            auto value = queue_ptr->wait_pop();
            EXPECT_FALSE(value);
        };

        std::thread th0{thread_worker};
        std::thread th1{thread_worker};
        std::thread th2{thread_worker};
        std::thread th3{thread_worker};

        // Need to wait for worker threads to wait on queue before deleting
        // queue
        // If reading from a nullptr, then this wait period isn't long enough
        std::this_thread::sleep_for(100ms);
        delete queue_ptr.release();

        th0.join();
        th1.join();
        th2.join();
        th3.join();
    }


}

#endif //AGS_LOCKED_QUEUE_TESTS_HPP
