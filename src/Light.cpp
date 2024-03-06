//
// Created by l4zy9uy on 3/1/24.
//

#include "Light.h"
#include <glm/glm.hpp>

Light::Light(const glm::dvec3 &intensity, const glm::dvec4 &position) : intensity_(intensity), position_(position) {}

const glm::dvec3 &Light::getIntensity() const {
  return intensity_;
}

void Light::setIntensity(const glm::dvec3 &intensity) {
  Light::intensity_ = intensity;
}

const glm::dvec4 &Light::getPosition() const {
  return position_;
}

void Light::setPosition(const glm::dvec4 &position) {
  Light::position_ = position;
}

glm::dvec3
Light::lighting(const Material &material,
                const Shape &shape,
                const glm::dvec4 &eye_vector,
                const glm::dvec4 &normal_vector,
                const bool &isInShadow,
                const glm::dvec4 &position) {
  glm::dvec3 color;
  if(material.hasPattern()) color = material.getPatternPtr()->pattern_at_shape(shape, position);
  else color = material.getColor();
  auto effective_color = color * intensity_;
  auto lightv = glm::normalize(position_ - position);
  auto ambient = effective_color * material.getAmbient();
  auto light_dot_normal = glm::dot(lightv, normal_vector);
  glm::dvec3 diffuse, specular;
  if (light_dot_normal < 0) {
    diffuse = glm::dvec3(0.0);
    specular = glm::dvec3(0.0);
  } else {
    diffuse = effective_color * material.getDiffuse() * light_dot_normal;
    auto reflectv = glm::reflect(-lightv, normal_vector);
    auto reflect_dot_eye = glm::dot(reflectv, eye_vector);
    if (reflect_dot_eye <= 0)
      specular = glm::dvec3(0.0);
    else {
      auto factor = glm::pow(reflect_dot_eye, material.getShininess());
      specular = intensity_ * material.getSpecular() * factor;
    }
  }
  if(isInShadow) return ambient;
  return ambient + diffuse + specular;
}

Light::Light() = default;
