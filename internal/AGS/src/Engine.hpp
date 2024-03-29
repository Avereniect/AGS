//
// Created by avereniect on 12/11/21.
//

#ifndef AGS_ENGINE_HPP
#define AGS_ENGINE_HPP

namespace ags {

    ///
    /// A class managing the core functionality of ARE.
    ///
    class Engine {
    public:

        //=================================================
        // State methods
        //=================================================

        ///
        /// \return True if engine was initialized successfully. False
        ///     otherwise. May be false if engine was already initialized
        static void init();

        ///
        /// Releases all resources acquired during initialization
        ///
        static void term();

    };

}

#endif //AGS_ENGINE_HPP
