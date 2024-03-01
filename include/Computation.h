//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_COMPUTATION_H
#define RAYTRACERV2_COMPUTATION_H
#include "Sphere.h"

class Sphere;
class Ray;

class Computation {
private:
    float t_;
    Sphere *sphere_ptr;
public:
    Computation(float t, Sphere *spherePtr, const glm::vec4 &point, const glm::vec4 &eyev, const glm::vec4 &normalv);

private:
    glm::vec4 point_;
    glm::vec4 eyev_;
    bool inside_;
public:
    bool isInside() const;

    void setInside(bool inside);

    [[nodiscard]] float getT() const;

    void setT(float t);

    [[nodiscard]] Sphere *getSpherePtr() const;

    void setSpherePtr(Sphere *spherePtr);

    [[nodiscard]] const glm::vec4 &getPoint() const;

    void setPoint(const glm::vec4 &point);

    [[nodiscard]] const glm::vec4 &getEyev() const;

    void setEyev(const glm::vec4 &eyev);

    [[nodiscard]] const glm::vec4 &getNormalv() const;

    void setNormalv(const glm::vec4 &normalv);

private:
    glm::vec4 normalv_;
};


#endif //RAYTRACERV2_COMPUTATION_H
