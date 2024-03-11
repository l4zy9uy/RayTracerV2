//
// Created by l4zy9uy on 3/11/24.
//

#ifndef RAYTRACERV2_INCLUDE_CONTAINERS_H
#define RAYTRACERV2_INCLUDE_CONTAINERS_H
#include "Shape.h"

class Shape;
class Containers {
private:
  std::vector<Shape*> list_;
public:
  [[nodiscard]] const std::vector<Shape *> &getList() const;
  void setList(const std::vector<Shape *> &List);
};

#endif //RAYTRACERV2_INCLUDE_CONTAINERS_H
