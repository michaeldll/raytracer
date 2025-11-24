#ifndef COMMON_H
#define COMMON_H

// C++ Std Library
#include <cmath>
#include <cstdlib>
#include <random>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double INFINITY_LIMIT = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589793;

// Utility Functions
inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

// Common Headers
#include "Color.h"
#include "Interval.h"
#include "Ray.h"
#include "Vector3.h"
#include "Hittable.h"

#endif