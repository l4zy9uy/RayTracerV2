//
// Created by l4zy9uy on 3/21/24.
//

#include "Shape/Group.h"
#include <algorithm>

Intersections Group::local_intersect(const Ray &ray) {
  Intersections xs;
  for(auto &shape : child_) {
    xs.addIntersections(shape->intersect(ray));
  }
  xs.sort();
  return xs;
}
glm::dvec4 Group::local_normal_at(const glm::dvec4 &point) const {
  return Shape::local_normal_at(point);
}
void Group::addChild(std::unique_ptr<Shape> shape) {
  shape->setParentPtr(this);
  child_.push_back(std::move(shape));
}
const std::vector<std::unique_ptr<Shape>> & Group::getChild() const {
  return child_;
}
