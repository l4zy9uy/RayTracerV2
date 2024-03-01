//
// Created by l4zy9uy on 2/28/24.
//

#include "Intersections.h"
#include <algorithm>

void Intersections::addIntersection(float &distance, Sphere *sphere) {
  sorted = false;
  intersections_.emplace_back(distance, sphere);
}

void Intersections::addIntersections(const Intersections &intersections) {
  for (const auto &intersection : intersections.intersections_) {
	intersections_.push_back(intersection);
  }
  sorted = false;
}

const std::vector<Intersection> &Intersections::getIntersections() const {
  return intersections_;
}

void Intersections::setIntersections(const std::vector<Intersection> &intersections) {
  intersections_ = intersections;
}

std::optional<Intersection> Intersections::hit() {
  if (!sorted)
	sort();

  if (intersections_.empty())
	return std::nullopt;
  auto result = std::find_if(intersections_.begin(), intersections_.end(), [&](const Intersection &i) {
	return i.getT() > 0;
  });

  if (result == intersections_.end())
	return std::nullopt;
  return std::make_optional<Intersection>(*result);
}

void Intersections::sort() {
  std::sort(intersections_.begin(), intersections_.end(), [&](const Intersection &lhs, const Intersection &rhs) {
	return lhs.getT() < rhs.getT();
  });
}

void Intersections::addIntersection(const Intersection &intersection) {
  intersections_.push_back(intersection);
}

Intersections::Intersections(const std::vector<Intersection> &intersections, bool sorted) : intersections_(
	intersections), sorted(sorted) {}

Intersections::Intersections() : sorted(false) {

}
