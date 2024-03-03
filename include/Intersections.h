//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTIONS_H
#define RAYTRACERV2_INTERSECTIONS_H
#include <vector>
#include "Intersection.h"
#include <optional>
class Intersection;
class Sphere;

class Intersections {
private:
  std::vector<Intersection> list_;
  bool sorted;
public:
  Intersections(const std::vector<Intersection> &list, bool sorted);
  Intersections();
  [[nodiscard]] const std::vector<Intersection> &getList() const;

  void setList(const std::vector<Intersection> &list);
  std::optional<Intersection> hit();

public:
  void addIntersection(float &distance, Sphere *sphere);
  void addIntersection(const Intersection &intersection);
  void addList(const Intersections &list);
  void sort();
};

#endif //RAYTRACERV2_INTERSECTIONS_H
