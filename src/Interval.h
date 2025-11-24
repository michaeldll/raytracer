#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

class Interval
{
public:
    double min, max;

    Interval() : min(INFINITY_LIMIT), max(-INFINITY_LIMIT) {} // Default interval is empty

    Interval(double min, double max) : min(min), max(max) {}

    double size() const
    {
        return max - min;
    }

    bool contains(double x) const
    {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const
    {
        return min < x && x < max;
    }

    static const Interval empty, universe;
};

const Interval Interval::empty = Interval(INFINITY_LIMIT, -INFINITY_LIMIT);
const Interval Interval::universe = Interval(-INFINITY_LIMIT, INFINITY_LIMIT);

#endif