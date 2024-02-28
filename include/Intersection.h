//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTION_H
#define RAYTRACERV2_INTERSECTION_H

#include "Sphere.h"
#include <memory>
class Intersection {
private:
    float t_;
    std::shared_ptr<Sphere> sphere_ptr_;
public:
    Intersection(float &t, std::shared_ptr<Sphere> &sphere);
};


#endif //RAYTRACERV2_INTERSECTION_H
