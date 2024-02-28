//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_RAY_H
#define RAYTRACERV2_RAY_H
#include <glm/vec4.hpp>

class Ray {
public:
    const glm::vec4 &getOriginPoint() const;
    void setOriginPoint(const glm::vec4 &originPoint);
    const glm::vec4 &getDirectionVector() const;
    void setDirectionVector(const glm::vec4 &directionVector);
    Ray(const glm::vec4 &originPoint, const glm::vec4 &directionVector);
private:
    glm::vec4 direction_vector_;
    glm::vec4 origin_point_;
public:
};

glm::vec4 position(const Ray &ray, const float &t);

#endif //RAYTRACERV2_RAY_H
