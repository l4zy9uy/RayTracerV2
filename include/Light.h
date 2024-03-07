//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_LIGHT_H
#define RAYTRACERV2_LIGHT_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Material.h"
class Light {
public:
  Light();
  Light(const glm::dvec3 &intensity, const glm::dvec4 &position);
private:
  glm::dvec3 intensity_{};
  glm::dvec4 position_{};
public:
  [[nodiscard]] const glm::dvec3 &getIntensity() const;
  void setIntensity(const glm::dvec3 &intensity);
  [[nodiscard]] const glm::dvec4 &getPosition() const;
  void setPosition(const glm::dvec4 &position);
public:
  glm::dvec3 lighting(const Material &material,
                      const Shape &shape,
                      const glm::dvec4 &eye_vector,
                      const glm::dvec4 &normal_vector,
                      const bool &isInShadow,
                      const glm::dvec4 &position);
};

#endif //RAYTRACERV2_LIGHT_H
