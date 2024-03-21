//
// Created by l4zy9uy on 2/28/24.
//

#include "Ray.h"

Ray::Ray(const glm::dvec4 &originPoint, const glm::dvec4 &directionVector) : origin_point_(originPoint),
                                                                             direction_vector_(directionVector) {}

const glm::dvec4 &Ray::getOriginPoint() const {
  return origin_point_;
}

void Ray::setOriginPoint(const glm::dvec4 &originPoint) {
  origin_point_ = originPoint;
}

const glm::dvec4 &Ray::getDirectionVector() const {
  return direction_vector_;
}

void Ray::setDirectionVector(const glm::dvec4 &directionVector) {
  direction_vector_ = directionVector;
}

Ray Ray::transform(const glm::dmat4 &transform_matrix) const {
  return {origin_point_ * glm::transpose(transform_matrix), direction_vector_ * glm::transpose(transform_matrix)};
}
glm::dvec4 Ray::at(const double &t) const {
  return origin_point_ + direction_vector_ * t;
}
bool Ray::operator==(const Ray &rhs) {
  return origin_point_ == rhs.origin_point_ && direction_vector_ == rhs.direction_vector_;
}
bool Ray::operator!=(const Ray &rhs) {
  return origin_point_ != rhs.origin_point_ || direction_vector_ != rhs.direction_vector_;
}

