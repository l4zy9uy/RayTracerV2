//
// Created by l4zy9uy on 3/1/24.
//

#include "Computation.h"

Computation::Computation(float t, Sphere *spherePtr, const glm::vec4 &point, const glm::vec4 &eyev,
                         const glm::vec4 &normalv) : t_(t), sphere_ptr(spherePtr), point_(point), eyev_(eyev),
                                                     normalv_(normalv) {
    if(glm::dot(normalv, eyev) < 0) {
        inside_ = true;
        normalv_ = -normalv;
    }
    else inside_ = false;
}

float Computation::getT() const {
    return t_;
}

void Computation::setT(float t) {
    t_ = t;
}

Sphere *Computation::getSpherePtr() const {
    return sphere_ptr;
}

void Computation::setSpherePtr(Sphere *spherePtr) {
    sphere_ptr = spherePtr;
}

const glm::vec4 &Computation::getPoint() const {
    return point_;
}

void Computation::setPoint(const glm::vec4 &point) {
    point_ = point;
}

const glm::vec4 &Computation::getEyev() const {
    return eyev_;
}

void Computation::setEyev(const glm::vec4 &eyev) {
    eyev_ = eyev;
}

const glm::vec4 &Computation::getNormalv() const {
    return normalv_;
}

void Computation::setNormalv(const glm::vec4 &normalv) {
    normalv_ = normalv;
}

bool Computation::isInside() const {
    return inside_;
}

void Computation::setInside(bool inside) {
    inside_ = inside;
}
