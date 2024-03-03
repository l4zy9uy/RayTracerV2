//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_MATERIAL_H
#define RAYTRACERV2_MATERIAL_H

#include <glm/vec3.hpp>

class Material {
public:
  Material(const glm::vec3 &color, float ambient, float diffuse, float specular, float shininess);

  Material();

private:
  glm::vec3 color_;
  float ambient_;
  float diffuse_;
  float specular_;
  float shininess_;
public:
  [[nodiscard]] const glm::vec3 &getColor() const;

  void setColor(const glm::vec3 &color);

  [[nodiscard]] float getAmbient() const;

  void setAmbient(float ambient);

  [[nodiscard]] float getDiffuse() const;

  void setDiffuse(float diffuse);

  [[nodiscard]] float getSpecular() const;

  void setSpecular(float specular);

  [[nodiscard]] float getShininess() const;

  void setShininess(float shininess);
};

#endif //RAYTRACERV2_MATERIAL_H
