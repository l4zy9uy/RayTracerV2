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
public:
  [[nodiscard]] const glm::dvec3 &getIntensity() const;

  void setIntensity(const glm::dvec3 &intensity);

  [[nodiscard]] const glm::dvec4 &getPosition() const;

  void setPosition(const glm::dvec4 &position);
  glm::dvec3 lighting(const Material &material,
                     const glm::dvec4 &position,
                     const glm::dvec4 &eye_vector,
                     const glm::dvec4 &normal_vector,
                     const bool &isInShadow);

private:
  glm::dvec4 position_{};

};

#endif //RAYTRACERV2_LIGHT_H
