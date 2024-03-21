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
  glm::dvec4 local_normal_at(const glm::dvec4 &point) const override;
  void addChild(const std::shared_ptr<Shape> &shape);
  const std::vector<std::shared_ptr<Shape>> &getChildVector() const;
private:
  std::vector<std::shared_ptr<Shape>> child_vector_;

};

#endif //RAYTRACERV2_INCLUDE_SHAPE_GROUP_H
