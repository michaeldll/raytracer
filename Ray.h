#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray {
  public:
    Ray() {}

    Ray(const Vector3& origin, const Vector3& direction) : originPoint(origin), directionVector(direction) {}

    const Vector3& origin() const  { return originPoint; }
    const Vector3& direction() const { return directionVector; }

    Vector3 at(double t) const {
        return originPoint + t * directionVector;
    }

  private:
    Vector3 originPoint;
    Vector3 directionVector;
};

#endif
