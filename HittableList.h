#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"
#include "Ray.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
public:
	std::vector<shared_ptr<Hittable>> objects;

	HittableList() {}
	HittableList(shared_ptr<Hittable> object) { add(object); }

	void clear() { objects.clear(); }

	void add(shared_ptr<Hittable> object)
	{
		objects.push_back(object);
	}

	bool hit(const Ray &r, double rayTMin, double rayTMax, HitRecord &record) const override
	{
		HitRecord tempRec;
		bool hitAnything = false;
		auto closestSoFar = rayTMax;

		for (const auto &object : objects)
		{
			if (object->hit(r, rayTMin, closestSoFar, tempRec))
			{
				hitAnything = true;
				closestSoFar = tempRec.t;
				record = tempRec;
			}
		}

		return hitAnything;
	}
};

#endif