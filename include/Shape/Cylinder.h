//
// Created by l4zy9uy on 3/20/24.
//

#ifndef RAYTRACERV2_INCLUDE_SHAPE_CYLINDER_H
#define RAYTRACERV2_INCLUDE_SHAPE_CYLINDER_H
#include "Shape.h"
#include "myMath.h"
class Cylinder : public Shape {
public:
  [[nodiscard]] const double & getMinimum() const;
  void setMinimum(const double &Minimum);
  [[nodiscard]] const double & getMaximum() const;
  void setMaximum(const double &Maximum);
  [[nodiscard]] const bool & isClose() const;
  void setClose(const bool &Close);
public:
  Intersections local_intersect(const Ray &ray) override;
  [[nodiscard]] glm::dvec4 local_normal_at(const glm::dvec4 &point, const Intersection &hit) const override;
  static bool checkCap(const Ray &ray, const double &t);
  void intersect_cap(const Ray &ray, Intersections &xs);
private:
  double minimum_ = NegInfinity;
  double maximum_ = PosInfinity;
  bool close_ = false;
};

#endif //RAYTRACERV2_INCLUDE_SHAPE_CYLINDER_H
