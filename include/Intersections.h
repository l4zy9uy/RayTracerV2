//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTIONS_H
#define RAYTRACERV2_INTERSECTIONS_H
#include <vector>
#include "Intersection.h"
#include <optional>
class Intersection;
class Shape;

class Intersections {
private:
  mutable std::vector<Intersection> list_;
  mutable bool sorted_;
public:
  Intersections(const std::vector<Intersection> &list, bool sorted);
  Intersections();
  [[nodiscard]] const std::vector<Intersection> &getList() const;
  void setList(const std::vector<Intersection> &list);
  void addIntersection(const double &distance, Shape *shape);
  void addIntersection(const Intersection &intersection);
  void addIntersections(const Intersections &intersections);
  void addList(const Intersections &list);

public:
  [[nodiscard]] std::optional<Intersection> hit() const;
  void sort() const;
};

#endif //RAYTRACERV2_INTERSECTIONS_H
