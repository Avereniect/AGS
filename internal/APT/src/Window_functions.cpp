//
// Created by avereniect on 6/14/22.
//
#include "Window_functions.hpp"

namespace ags::apt {

    real box_window(real x, real y) {
        return 1.00;
    }

    real pyramid_window(real x, real y) {
        using std::min;
        using std::abs;

        return real(3.0f) * (min(-abs(x), -abs(y)) + real{1.0});
    }

    real cone_window(real x, real y) {
        using std::max;
        using std::sqrt;

        real d = real{1.0} - sqrt(x * x + y * y);
        return (12.0f / M_PI) * max(real{0.0}, d);
    }

    real han_window(real x, real y) {
        using std::sqrt;
        using std::sin;
        using std::max;

        real d = real{1.0} - sqrt(x * x + y * y);

        real s = sin(max(d, real{0.0}) * real(M_PI / 2.0));
        real tmp0 = real{1.0} - s * s;

        return (32.0f / M_PI) * tmp0;
    }

    real lanczos_window(real x, real y) {
        using std::sqrt;
        using std::sin;

        real d = real{1.0} - sqrt(x * x + y * y);

        d *= M_PI;

        return 1.41028648394f  * (sin(d) / d);
    }

}
