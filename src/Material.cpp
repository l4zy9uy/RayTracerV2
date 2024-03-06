//
// Created by l4zy9uy on 3/1/24.
//

#include "Material.h"

Material::Material(const glm::dvec3 &color, double ambient, double diffuse, double specular, double shininess) : color_(
    color), ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess) {}

Material::Material() : color_(
    glm::dvec3(1.0)), ambient_(0.1), diffuse_(0.9), specular_(0.9), shininess_(200.0) {}

const glm::dvec3 &Material::getColor() const {
  return color_;
}

void Material::setColor(const glm::dvec3 &color) {
  color_ = color;
}

double Material::getAmbient() const {
  return ambient_;
}

void Material::setAmbient(double ambient) {
  ambient_ = ambient;
}

double Material::getDiffuse() const {
  return diffuse_;
}

void Material::setDiffuse(double diffuse) {
  diffuse_ = diffuse;
}

double Material::getSpecular() const {
  return specular_;
}

void Material::setSpecular(double specular) {
  specular_ = specular;
}

double Material::getShininess() const {
  return shininess_;
}

void Material::setShininess(double shininess) {
  shininess_ = shininess;
}

bool Material::hasPattern() const {
  if(pattern_ptr_ != nullptr) return true;
  return false;
}
const std::shared_ptr<Pattern> &Material::getPatternPtr() const {
  return pattern_ptr_;
}
void Material::setPatternPtr(const std::shared_ptr<Pattern> &PatternPtr) {
  pattern_ptr_ = PatternPtr;
}
