#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vector3 {
    public:
        double elements[3];

        Vector3() : elements{0,0,0} {}
        Vector3(double element0, double element1, double element2) : elements{element0, element1, element2} {}

        double x() const { return elements[0]; }
        double y() const { return elements[1]; }
        double z() const { return elements[2]; }

        Vector3 operator-() const { return Vector3(-elements[0], -elements[1], -elements[2]); }
        double operator[](int index) const { return elements[index]; }
        double& operator[](int index) { return elements[index]; }

        Vector3& operator+=(const Vector3& vector) {
                elements[0] += vector.elements[0];
                elements[1] += vector.elements[1];
                elements[2] += vector.elements[2];
                return *this;
        }

        Vector3& operator*=(double scalar) {
                elements[0] *= scalar;
                elements[1] *= scalar;
                elements[2] *= scalar;
                return *this;
        }

        Vector3& operator/=(double scalar) {
                return *this *= 1/scalar;
        }

        double length() const {
                return std::sqrt(lengthSquared());
        }

        double lengthSquared() const {
                return elements[0]*elements[0] + elements[1]*elements[1] + elements[2]*elements[2];
        }
};

/**
 * Utility Functions
 */
inline std::ostream& operator<<(std::ostream& out, const Vector3& vector) {
    return out << vector.elements[0] << ' ' << vector.elements[1] << ' ' << vector.elements[2];
}

inline Vector3 operator+(const Vector3& vector1, const Vector3& vector2) {
    return Vector3(vector1.elements[0] + vector2.elements[0], vector1.elements[1] + vector2.elements[1], vector1.elements[2] + vector2.elements[2]);
}

inline Vector3 operator-(const Vector3& vector1, const Vector3& vector2) {
    return Vector3(vector1.elements[0] - vector2.elements[0], vector1.elements[1] - vector2.elements[1], vector1.elements[2] - vector2.elements[2]);
}

inline Vector3 operator*(const Vector3& vector1, const Vector3& vector2) {
    return Vector3(vector1.elements[0] * vector2.elements[0], vector1.elements[1] * vector2.elements[1], vector1.elements[2] * vector2.elements[2]);
}

inline Vector3 operator*(double scalar, const Vector3& vector) {
    return Vector3(scalar*vector.elements[0], scalar*vector.elements[1], scalar*vector.elements[2]);
}

inline Vector3 operator*(const Vector3& vector, double scalar) {
    return scalar * vector;
}

inline Vector3 operator/(const Vector3& vector, double scalar) {
    return (1/scalar) * vector;
}

inline double dot(const Vector3& vector1, const Vector3& vector2) {
    return vector1.elements[0] * vector2.elements[0]
         + vector1.elements[1] * vector2.elements[1]
         + vector1.elements[2] * vector2.elements[2];
}

inline Vector3 cross(const Vector3& vector1, const Vector3& vector2) {
    return Vector3(vector1.elements[1] * vector2.elements[2] - vector1.elements[2] * vector2.elements[1],
                vector1.elements[2] * vector2.elements[0] - vector1.elements[0] * vector2.elements[2],
                vector1.elements[0] * vector2.elements[1] - vector1.elements[1] * vector2.elements[0]);
}

inline Vector3 normalize(const Vector3& vector) {
    return vector / vector.length();
}

#endif
