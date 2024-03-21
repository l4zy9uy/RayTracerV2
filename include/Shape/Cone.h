//
// Created by l4zy9uy on 3/20/24.
//

#ifndef RAYTRACERV2_INCLUDE_SHAPE_CONE_H
#define RAYTRACERV2_INCLUDE_SHAPE_CONE_H
#include "Shape.h"

class Cone : public Shape {
public:
  Intersections local_intersect(const Ray &ray) override;
  glm::dvec4 local_normal_at(const glm::dvec4 &point) const override;
  bool checkCap(const Ray &ray, const double &t, const double &y) const;
  void intersect_cap(const Ray &ray, Intersections &xs);
private:
  double minimum_ = -1000000000;
public:
  double getMinimum() const;
  void setMinimum(double Minimum);
  double getMaximum() const;
  void setMaximum(double Maximum);
  bool isClose() const;
  void setClose(bool Close);
private:
  double maximum_ = 1000000000;
  bool close_ = false;
};

#endif //RAYTRACERV2_INCLUDE_SHAPE_CONE_H
