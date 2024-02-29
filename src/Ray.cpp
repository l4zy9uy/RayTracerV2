//
// Created by l4zy9uy on 2/28/24.
//

#include "../include/Ray.h"

Ray::Ray(const glm::vec4 &originPoint, const glm::vec4 &directionVector) : origin_point_(originPoint),
																		   direction_vector_(directionVector) {}

const glm::vec4 &Ray::getOriginPoint() const {
  return origin_point_;
}

void Ray::setOriginPoint(const glm::vec4 &originPoint) {
  origin_point_ = originPoint;
}

const glm::vec4 &Ray::getDirectionVector() const {
  return direction_vector_;
}

void Ray::setDirectionVector(const glm::vec4 &directionVector) {
  direction_vector_ = directionVector;
}

Ray Ray::transform(const glm::mat4 &transform_matrix) const {
  return {origin_point_ * glm::transpose(transform_matrix), direction_vector_ * glm::transpose(transform_matrix)};
}

glm::vec4 position(const Ray &ray, const float &t) {
  return ray.getOriginPoint() + ray.getDirectionVector() * t;
}
