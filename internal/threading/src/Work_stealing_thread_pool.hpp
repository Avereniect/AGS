//
// Created by avereniect on 8/22/22.
//

#ifndef AGS_THREADING_WORK_STEALING_THREAD_POOL_HPP
#define AGS_THREADING_WORK_STEALING_THREAD_POOL_HPP

#include <aul/

#include <memory>
#include <vector>
#include <thread>

namespace ags::threading {

    struct Work_stealing_thread_pool_members {

        std::vector<std::thread> threads;



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
