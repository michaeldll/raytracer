#ifndef COMMON_H
#define COMMON_H

// C++ Std Library
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// Common Headers
#include "Color.h"
#include "Ray.h"
#include "Vector3.h"
#include "Hittable.h"

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589793;

// Utility Functions
inline double degreesToRadians(double degrees)
{
	return degrees * pi / 180.0;
}

#endif