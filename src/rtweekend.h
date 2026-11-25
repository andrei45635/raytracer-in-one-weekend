#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <cstdlib>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    std::random_device rd;
    std::uniform_real_distribution dis(0.0, 1.0);
    std::mt19937 mt(rd());
    return dis(mt);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

// common includes
#include "colour.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif //RTWEEKEND_H
