//
// Created by avereniect on 5/23/22.
//

#ifndef AGS_THREADING_WORK_SHARING_THREAD_POOL_TESTS_HPP
#define AGS_THREADING_WORK_SHARING_THREAD_POOL_TESTS_HPP

#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>

#include <ags/Threading.hpp>

namespace ags::threading::tests {

    //=====================================================
    // Constructor/Destructor tests
    //=====================================================

    /*
    TEST(Threading, Consutrctor_destructor_zero_threads) {
        Work_sharing_thread_pool pool{0};
        EXPECT_EQ(pool.thread_count(), 0);
        EXPECT_EQ(pool.task_count(), 0);
    }

    TEST(Threading, Consutrctor_destructor_one_thread) {
        Work_sharing_thread_pool pool{1};
        EXPECT_EQ(pool.thread_count(), 1);
        EXPECT_EQ(pool.task_count(), 0);
    }

    TEST(Threading, Consutrctor_destructor_two_threads) {
        Work_sharing_thread_pool pool{2};
        EXPECT_EQ(pool.thread_count(), 2);
        EXPECT_EQ(pool.task_count(), 0);
    }

    TEST(Threading, Consutrctor_destructor_four_threads) {
        Work_sharing_thread_pool pool{4};
        EXPECT_EQ(pool.thread_count(), 4);
        EXPECT_EQ(pool.task_count(), 0);
    }

    TEST(Threading, Consutrctor_destructor_eight_threads) {
        Work_sharing_thread_pool pool{8};
        EXPECT_EQ(pool.thread_count(), 8);
        EXPECT_EQ(pool.task_count(), 0);
    }

    TEST(Threading, Consutrctor_destructor_default_threads) {
        Work_sharing_thread_pool pool{};
        EXPECT_EQ(pool.thread_count(), std::thread::hardware_concurrency());
        EXPECT_EQ(pool.task_count(), 0);
    }
    */

    //=====================================================
    // Simple tasks
    //=====================================================

    TEST(Threading, Simple_tasks) {
        constexpr std::uint32_t task_count = 1024 * 4;
        std::uint32_t outputs[task_count];

        {
            Work_sharing_thread_pool pool{8};

            for (std::uint32_t i = 0; i < task_count; ++i) {
                std::uint32_t* output_location = outputs + i;
                std::uint32_t index = i;

                auto task = [output_location, index]() {
                    *output_location = index;
                };

                pool.submit(task);
            }

            pool.wait();
        }

        for (std::uint32_t i = 0; i < task_count; ++i) {
            EXPECT_EQ(outputs[i], i);
        }
    }

    void write_uint_to_loc(std::uint32_t* loc, std::uint32_t data) {
        *loc = data;
    }

    TEST(Threading, Submit_lambda_width_capture) {
        constexpr std::uint32_t task_count = 1;
        std::uint32_t outputs[task_count];

        std::uint32_t magic_offset = 15;

        {
            Work_sharing_thread_pool pool{1};

            for (std::uint32_t i = 0; i < task_count; ++i) {
                std::uint32_t* output_location = outputs + i;
                std::uint32_t value = i + magic_offset;

                auto task = [output_location, value] () {
                    write_uint_to_loc(output_location, value);
                };

                pool.submit(task);
            }

            pool.wait();
        }

        for (std::uint32_t i = 0; i < task_count; ++i) {
            EXPECT_EQ(outputs[i], i + magic_offset);
        }
    }

    TEST(Threading, Stop_wait) {
        constexpr std::uint32_t task_count = 1024;
        std::uint32_t outputs[task_count];

        {
            Work_sharing_thread_pool pool{8};

            pool.pause();
            for (std::uint32_t i = 0; i < task_count; ++i) {
                std::uint32_t* output_location = outputs + i;
                std::uint32_t index = i;

                auto task = [output_location, index]() {
                    *output_location = index;
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                };

                pool.submit(task);
            }
            pool.start();

            pool.stop_wait();
            EXPECT_NE(pool.task_count(), 0);
        }
    }

}

#endif //AGS_THREADING_WORK_SHARING_THREAD_POOL_TESTS_HPP
