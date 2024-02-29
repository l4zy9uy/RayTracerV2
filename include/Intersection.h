//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTION_H
#define RAYTRACERV2_INTERSECTION_H

#include <memory>
#include "Sphere.h"

class Sphere;

class Intersection {
private:
    float t_;
public:
    float getT() const;

    void setT(float t);

    [[nodiscard]] const Sphere* getSpherePtr() const;

    void setSpherePtr(Sphere* spherePtr);

private:
    Sphere* sphere_ptr_;
public:
    Intersection(float t, Sphere* sphere);
};


#endif //RAYTRACERV2_INTERSECTION_H
