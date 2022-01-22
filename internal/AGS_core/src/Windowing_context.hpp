//
// Created by avereniect on 1/18/22.
//

#ifndef AGS_WINDOWING_CONTEXT_HPP
#define AGS_WINDOWING_CONTEXT_HPP

namespace ags {

    class Windowing_context {
    public:

        static void init();

        static void term();

        static void poll_events();

    private:

        static void error_callback(int error_code, const char* message);

    };

}

#endif //AGS_WINDOWING_CONTEXT_HPP
