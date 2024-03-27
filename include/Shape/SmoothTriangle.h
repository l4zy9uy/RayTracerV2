//
// Created by l4zy9uy on 3/26/24.
//

#ifndef RAYTRACERV2_INCLUDE_SHAPE_SMOOTHTRIANGLE_H
#define RAYTRACERV2_INCLUDE_SHAPE_SMOOTHTRIANGLE_H
#include "Triangle.h"

class SmoothTriangle : public Triangle{
public:
  SmoothTriangle(const glm::dvec4 &P1,
                 const glm::dvec4 &P2,
                 const glm::dvec4 &P3,
                 const glm::dvec4 &N1,
                 const glm::dvec4 &N2,
                 const glm::dvec4 &N3);
  Intersections local_intersect(const Ray &ray) override;
  glm::dvec4 local_normal_at(const glm::dvec4 &point, const Intersection &hit) const override;
  ~SmoothTriangle() override = default;
private:
  glm::dvec4 n1_{};
  glm::dvec4 n2_{};
  glm::dvec4 n3_{};
};

#endif //RAYTRACERV2_INCLUDE_SHAPE_SMOOTHTRIANGLE_H
