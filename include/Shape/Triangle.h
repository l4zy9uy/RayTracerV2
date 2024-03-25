//
// Created by l4zy9uy on 3/22/24.
//

#ifndef RAYTRACERV2_INCLUDE_SHAPE_TRIANGLE_H
#define RAYTRACERV2_INCLUDE_SHAPE_TRIANGLE_H
#include "Shape.h"

class Triangle : public Shape{
private:
  glm::dvec4 p1_{};
  glm::dvec4 p2_{};
  glm::dvec4 p3_{};
public:
  const glm::dvec4 &getP1() const;
  void setP1(const glm::dvec4 &P1);
  const glm::dvec4 &getP2() const;
  void setP2(const glm::dvec4 &P2);
  const glm::dvec4 &getP3() const;
  void setP3(const glm::dvec4 &P3);
  const glm::dvec4 &getE1() const;
  void setE1(const glm::dvec4 &E1);
  const glm::dvec4 &getE2() const;
  void setE2(const glm::dvec4 &E2);
  const glm::dvec4 &getNormal() const;
  void setNormal(const glm::dvec4 &Normal);
private:
  glm::dvec4 e1_{};
  glm::dvec4 e2_{};
public:
  Intersections local_intersect(const Ray &ray) override;
  glm::dvec4 local_normal_at(const glm::dvec4 &point) const override;
private:
  glm::dvec4 normal_{};
public:
  Triangle() = default;
  Triangle(const glm::dvec4 &p1, const glm::dvec4 &p2, const glm::dvec4 &p3);
};

#endif //RAYTRACERV2_INCLUDE_SHAPE_TRIANGLE_H
