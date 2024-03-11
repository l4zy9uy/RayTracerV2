//
// Created by l4zy9uy on 3/11/24.
//

#include "Containers.h"
const std::vector<Shape *> &Containers::getList() const {
  return list_;
}
void Containers::setList(const std::vector<Shape *> &List) {
  list_ = List;
}
