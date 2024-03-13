//
// Created by l4zy9uy on 2/28/24.
//

#include "Intersections.h"
#include <algorithm>

void Intersections::addIntersection(const double &distance, Shape *shape) {
  sorted_ = false;
  list_.emplace_back(distance, shape);
}

void Intersections::addList(const Intersections &list) {
  for (const auto &intersection : list.list_) {
    list_.push_back(intersection);
  }
  sorted_ = false;
}

const std::vector<Intersection> &Intersections::getList() const {
  return list_;
}

void Intersections::setList(const std::vector<Intersection> &list) {
  list_ = list;
}

std::optional<Intersection> Intersections::hit() const {
  if (!sorted_)
    sort();

  if (list_.empty())
    return std::nullopt;
  auto result = std::find_if(list_.begin(), list_.end(), [&](const Intersection &i) {
    return i.t_ > 0.0;
  });

  if (result == list_.end())
    return std::nullopt;
  return std::make_optional<Intersection>(*result);
}

void Intersections::sort() const {
  std::sort(list_.begin(), list_.end(), [&](const Intersection &lhs, const Intersection &rhs) {
    return lhs.t_ < rhs.t_;
  });
  sorted_ = true;
}

void Intersections::addIntersection(const Intersection &intersection) {
  list_.push_back(intersection);
}

Intersections::Intersections(const std::vector<Intersection> &list, bool sorted) : list_(
    list), sorted_(sorted) {}

Intersections::Intersections() : sorted_(false) {

}
void Intersections::addIntersections(const Intersections &intersections) {
  for (const auto &i : intersections.list_) {
    list_.push_back(i);
  }
}
