#include "Vector3.h"

#ifndef HITTABLE_H
#define HITTABLE_H

class HitRecord
{
public:
	Vector3 position;
	Vector3 normal;
	double t;
	bool frontFace;

	void setFaceNormal(const Ray &ray, const Vector3 &outwardNormal)
	{
		// Sets the hit record normal vector.
		// NOTE: the parameter `outward_normal` is assumed to have unit length.
		frontFace = dot(ray.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray &ray, double rayTMin, double rayTMax, HitRecord &record) const = 0;
};

#endif