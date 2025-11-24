// Simple unit test: create two overlapping spheres and assert the closer one is hit
#include <iostream>
#include <cmath>
#include "common.h"
#include "HittableList.h"
#include "Sphere.h"

int main()
{
    // Ray from origin looking down -Z
    Ray r(Vector3(0, 0, 0), Vector3(0, 0, -1));

    // Far sphere: center at z = -1, radius 0.5
    Sphere farSphere(Vector3(0, 0, -1.0), 0.5);
    // Near sphere: center at z = -0.5, radius 0.25
    Sphere nearSphere(Vector3(0, 0, -0.5), 0.25);

    // Two lists: one where far is added first, one where near is first
    HittableList list1;
    list1.add(make_shared<Sphere>(farSphere));
    list1.add(make_shared<Sphere>(nearSphere));

    HittableList list2;
    list2.add(make_shared<Sphere>(nearSphere));
    list2.add(make_shared<Sphere>(farSphere));

    Interval tRange = Interval::universe;
    HitRecord rec;

    auto check = [&](const HittableList &list, const char *label) {
        HitRecord rrec;
        bool hit = list.hit(r, tRange, rrec);
        if (!hit) {
            std::cerr << label << ": no hit found\n";
            return false;
        }
        // expected near t is (-center.z) - radius = 0.5 - 0.25 = 0.25
        double expectedNear = 0.25;
        if (std::abs(rrec.t - expectedNear) > 1e-3) {
            std::cerr << label << ": hit t=" << rrec.t << " expected~" << expectedNear << "\n";
            return false;
        }
        return true;
    };

    bool ok1 = check(list1, "list1");
    bool ok2 = check(list2, "list2");

    if (ok1 && ok2) {
        std::cout << "PASS: closer sphere reported in both orders\n";
        return 0;
    }

    std::cerr << "FAIL: closer sphere not reported\n";
    return 1;
}
