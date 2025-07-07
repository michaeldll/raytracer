#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vector3.h"

class Sphere : public Hittable
{
public:
	Sphere(const Vector3 &center, double radius) : center(center), radius(std::fmax(0, radius)) {}

	bool hit(const Ray &ray, double rayTMin, double rayTMax, HitRecord &record) const override
	{
		Vector3 fromCenter = center - ray.origin();
		auto a = ray.direction().lengthSquared();
		auto h = dot(ray.direction(), fromCenter);
		auto c = fromCenter.lengthSquared() - radius * radius;

		auto discriminant = h * h - a * c;
		if (discriminant < 0)
			return false;

		auto squared = std::sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (h - squared) / a;
		if (root <= rayTMin || rayTMax <= root)
		{
			root = (h + squared) / a;
			if (root <= rayTMin || rayTMax <= root)
				return false;
		}

		record.t = root;
		record.position = ray.at(record.t);
		record.normal = (record.position - center) / radius;
		Vector3 outwardNormal = (record.position - center) / radius;
		record.setFaceNormal(ray, outwardNormal);

		return true;
	}

private:
	Vector3 center;
	double radius;
};

#endif