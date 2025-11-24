#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"
#include "Ray.h"
#include "Interval.h"

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

	bool hit(const Ray &r, Interval rayT, HitRecord &record) const override
	{
		HitRecord tempRec;
		bool hitAnything = false;
		auto closestSoFar = rayT.max;

		for (const auto &object : objects)
		{
			Interval currentT(rayT.min, closestSoFar);
			if (object->hit(r, currentT, tempRec))
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