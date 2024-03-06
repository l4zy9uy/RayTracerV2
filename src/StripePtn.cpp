//
// Created by l4zy9uy on 3/6/24.
//

#include "Pattern/StripePtn.h"
#include "Shape.h"

StripePtn::StripePtn(const glm::dvec3 &A, const glm::dvec3 &B) : Pattern(A, B){}

/*glm::dvec3 StripePtn::pattern_at_shape(const Shape &shape, const glm::dvec4 &world_position) {
  auto object_point = glm::inverse(shape.getModel()) * world_position;
  auto pattern_point = glm::inverse(transformation_matrix_) * object_point;

  return pattern_at(pattern_point);
}*/

glm::dvec3 StripePtn::pattern_at(const glm::dvec4 &point) const {
  if(static_cast<long>(floor(point.x)) % 2 == 0) return a;
  else return b;
}
/*const glm::dvec3 &StripePtn::getA() const {
  return a;
}
void StripePtn::setA(const glm::dvec3 &A) {
  a = A;
}
const glm::dvec3 &StripePtn::getB() const {
  return b;
}
void StripePtn::setB(const glm::dvec3 &B) {
  b = B;
}*/
