//
// Created by avereniect on 12/11/21.
//

#ifndef AGS_ENGINE_HPP
#define AGS_ENGINE_HPP

namespace ags {

    class Engine {
    public:

        //=================================================
        // State methods
        //=================================================

        ///
        /// \return True if engine was initialized successfully. False
        ///     otherwise. May be false if engine was already initialized
        static bool init();

        static void term();

    private:

        //=================================================
        // Static members
        //=================================================

        static bool is_initialized;

    };

}

#endif //AGS_ENGINE_HPP
