//
// Created by l4zy9uy on 2/28/24.
//


#include "Intersection.h"

Intersection::Intersection(float t, Sphere* sphere) : t_(t), sphere_ptr_(sphere) {}

float Intersection::getT() const {
    return t_;
}

void Intersection::setT(float t) {
    t_ = t;
}

const Sphere* Intersection::getSpherePtr() const {
    return sphere_ptr_;
}

void Intersection::setSpherePtr( Sphere *spherePtr) {
    sphere_ptr_ = spherePtr;
}
