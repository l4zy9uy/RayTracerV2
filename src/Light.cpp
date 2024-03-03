//
// Created by l4zy9uy on 3/1/24.
//

#include "Light.h"
#include <glm/glm.hpp>

Light::Light(const glm::vec3 &intensity, const glm::vec4 &position) : intensity_(intensity), position_(position) {}

const glm::vec3 &Light::getIntensity() const {
  return intensity_;
}

void Light::setIntensity(const glm::vec3 &intensity) {
  Light::intensity_ = intensity;
}

const glm::vec4 &Light::getPosition() const {
  return position_;
}

void Light::setPosition(const glm::vec4 &position) {
  Light::position_ = position;
}

glm::vec3
Light::lighting(const Material &material,
                const glm::vec4 &position,
                const glm::vec4 &eye_vector,
                const glm::vec4 &normal_vector,
                const bool &isInShadow) {
  auto effective_color = material.getColor() * intensity_;
  auto lightv = glm::normalize(position_ - position);
  auto ambient = effective_color * material.getAmbient();
  auto light_dot_normal = glm::dot(lightv, normal_vector);
  glm::vec3 diffuse, specular;
  if (light_dot_normal < 0) {
    diffuse = glm::vec3(0.0f);
    specular = glm::vec3(0.0f);
  } else {
    diffuse = effective_color * material.getDiffuse() * light_dot_normal;
    auto reflectv = glm::reflect(-lightv, normal_vector);
    auto reflect_dot_eye = glm::dot(reflectv, eye_vector);
    if (reflect_dot_eye <= 0)
      specular = glm::vec3(0.0f);
    else {
      auto factor = glm::pow(reflect_dot_eye, material.getShininess());
      specular = intensity_ * material.getSpecular() * factor;
    }
  }
  if(isInShadow) return ambient;
  return ambient + diffuse + specular;
}

Light::Light() = default;
