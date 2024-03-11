//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_MATERIAL_H
#define RAYTRACERV2_MATERIAL_H

#include <glm/vec3.hpp>
#include "Pattern/Pattern.h"
#include <optional>
#include <memory>

class Material {
public:
  Material(const glm::dvec3 &color, double ambient, double diffuse, double specular, double shininess, double reflective);

  Material();

private:
  glm::dvec3 color_;
  double ambient_;
  double diffuse_;
  double specular_;
  double shininess_;
public:
  double getTransparency() const;
  void setTransparency(double Transparency);
  double getRefractiveIndex() const;
  void setRefractiveIndex(double RefractiveIndex);
private:
  double reflective_;
  double transparency_;
  double refractive_index_;
public:
  double getReflective() const;
  void setReflective(const double &Reflective);
private:
  std::shared_ptr<Pattern> pattern_ptr_;
public:
  [[nodiscard]] const std::shared_ptr<Pattern> &getPatternPtr() const;
  void setPatternPtr(const std::shared_ptr<Pattern> &PatternPtr);
  [[nodiscard]] bool hasPattern() const;
  [[nodiscard]] const glm::dvec3 &getColor() const;
  void setColor(const glm::dvec3 &color);
  [[nodiscard]] double getAmbient() const;
  void setAmbient(double ambient);
  [[nodiscard]] double getDiffuse() const;
  void setDiffuse(double diffuse);
  [[nodiscard]] double getSpecular() const;
  void setSpecular(double specular);
  [[nodiscard]] double getShininess() const;
  void setShininess(double shininess);
};

#endif //RAYTRACERV2_MATERIAL_H
