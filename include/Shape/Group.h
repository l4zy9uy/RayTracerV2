//
// Created by l4zy9uy on 3/21/24.
//

#ifndef RAYTRACERV2_INCLUDE_SHAPE_GROUP_H
#define RAYTRACERV2_INCLUDE_SHAPE_GROUP_H
#include "Shape.h"

class Group : public Shape {
public:
  Group() = default;
  Intersections local_intersect(const Ray &ray) override;
  [[nodiscard]] glm::dvec4 local_normal_at(const glm::dvec4 &point, const Intersection &hit) const override;
  void addChild(std::unique_ptr<Shape> shape);
  [[nodiscard]] const std::vector<std::unique_ptr<Shape>> & getChild() const;
private:
  std::vector<std::unique_ptr<Shape>> child_;

};

#endif //RAYTRACERV2_INCLUDE_SHAPE_GROUP_H
