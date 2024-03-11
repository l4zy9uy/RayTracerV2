//
// Created by l4zy9uy on 3/1/24.
//

#include "Material.h"

Material::Material(const glm::dvec3 &color, double ambient, double diffuse, double specular, double shininess, double reflective) : color_(
    color), ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess), reflective_(reflective) {}

/*const glm::dvec3 &Material::getColor() const {
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
double Material::getReflective() const {
  return reflective_;
}
void Material::setReflective(const double &Reflective) {
  reflective_ = Reflective;
}
*//*double Material::getTransparency() const {
  return transparency_;
}*//*
void Material::setTransparency(double Transparency) {
  transparency_ = Transparency;
}
double Material::getRefractiveIndex() const {
  return refractive_index_;
}
void Material::setRefractiveIndex(double RefractiveIndex) {
  refractive_index_ = RefractiveIndex;
}*/
