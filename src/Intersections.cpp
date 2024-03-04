//
// Created by l4zy9uy on 2/28/24.
//

#include "Intersections.h"
#include <algorithm>

void Intersections::addIntersection(double &distance, Sphere *sphere) {
  sorted = false;
  list_.emplace_back(distance, sphere);
}

void Intersections::addList(const Intersections &list) {
  for (const auto &intersection : list.list_) {
    list_.push_back(intersection);
  }
  sorted = false;
}

const std::vector<Intersection> &Intersections::getList() const {
  return list_;
}

void Intersections::setList(const std::vector<Intersection> &list) {
  list_ = list;
}

std::optional<Intersection> Intersections::hit() {
  if (!sorted)
    sort();

  if (list_.empty())
    return std::nullopt;
  auto result = std::find_if(list_.begin(), list_.end(), [&](const Intersection &i) {
    return i.getT() > 0;
  });

  if (result == list_.end())
    return std::nullopt;
  return std::make_optional<Intersection>(*result);
}

void Intersections::sort() {
  std::sort(list_.begin(), list_.end(), [&](const Intersection &lhs, const Intersection &rhs) {
    return lhs.getT() < rhs.getT();
  });
}

void Intersections::addIntersection(const Intersection &intersection) {
  list_.push_back(intersection);
}

Intersections::Intersections(const std::vector<Intersection> &list, bool sorted) : list_(
    list), sorted(sorted) {}

Intersections::Intersections() : sorted(false) {

}
