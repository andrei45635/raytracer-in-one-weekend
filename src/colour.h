#ifndef COLOUR_H
#define COLOUR_H

#include "rtweekend.h"
#include "vec3.h"
#include "interval.h"

using colour = vec3;

inline double linear_to_gamma(double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }

    return 0;
}

inline void write_colour(std::ostream& out, const colour& pixel_colour) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // translating the [0, 1] component values to the byte range [0, 255]
    static const interval intensity(0.000, 0.999);
    int rbyte = static_cast<int>(intensity.clamp(r) * 256);
    int gbyte = static_cast<int>(intensity.clamp(g) * 256);
    int bbyte = static_cast<int>(intensity.clamp(b) * 256);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif //COLOUR_H
