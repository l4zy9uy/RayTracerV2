//
// Created by l4zy9uy on 3/21/24.
//

#include "Shape/Group.h"
#include <algorithm>

Intersections Group::local_intersect(const Ray &ray) {
  Intersections xs;
  for(auto &shape : child_vector_) {
    xs.addIntersections(shape->intersect(ray));
  }
  xs.sort();
  return xs;
}
glm::dvec4 Group::local_normal_at(const glm::dvec4 &point) const {
  return Shape::local_normal_at(point);
}
void Group::addChild(Shape *shape) {
  child_vector_.push_back(shape);
  shape->setParentPtr(this);
}
const std::vector<Shape *> & Group::getChildVector() const {
  return child_vector_;
}
