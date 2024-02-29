//
// Created by l4zy9uy on 2/28/24.
//

#include "../include/Sphere.h"

Sphere::Sphere(const glm::mat4 &model, const float &radius, const glm::vec4 &position) : model_(model), radius_(radius), position_(position) {}

Intersections Sphere::intersect(const Ray &ray) {
    Intersections result;
    auto ray2 = ray.transform(glm::inverse(model_));
    auto sphere_to_ray = ray2.getOriginPoint() - position_;
    auto a = glm::dot(ray2.getDirectionVector(), ray2.getDirectionVector());
    auto b = 2 * glm::dot(ray2.getDirectionVector(), sphere_to_ray);
    auto c = glm::dot(sphere_to_ray, sphere_to_ray) - 1;
    auto discriminant = b*b - 4*a*c;

    if(discriminant < 0) {
        return result;
    }
    auto t1 = (-b - glm::sqrt(discriminant)) / (2*a);
    auto t2 = (-b + glm::sqrt(discriminant)) / (2*a);
    result.addIntersection(t1, this);
    result.addIntersection(t2,  this);
    return result;
}

Sphere::Sphere() : model_(glm::identity<glm::mat4>()), radius_(1.0f), position_(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) {}

void Sphere::setTransform(const glm::mat4 &transform_matrix) {
    model_ = transform_matrix;
}
