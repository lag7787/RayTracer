#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Usings

using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // [0, 1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // [min,max)
    return min + (max - min) * random_double();
}

inline void swap(double& x, double& y) {
    double temp = x;
    x = y;
    y = temp;
}

// common headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif


// this is a general, main header file. really cool!