//
// Created by l4zy9uy on 2/27/24.
//

#ifndef RAYTRACERV2_CANVAS_H
#define RAYTRACERV2_CANVAS_H
#include <glm/vec3.hpp>
#include <vector>

class Canvas {
public:
  Canvas(const unsigned int &windowWidth, const unsigned int &windowHeight);
public:
  [[nodiscard]] const unsigned long & getWindowWidth() const;
  void setWindowWidth(const unsigned long &windowWidth);
  [[nodiscard]] const unsigned long & getWindowHeight() const;
  void setWindowHeight(const unsigned long &windowHeight);
public:
  void writePixel(const unsigned long &y, const unsigned long &x, const glm::dvec3 &color);
  [[nodiscard]] const glm::dvec3 &pixelAt(const int &y, const int &x) const;
  void canvas_to_ppm();
private:
  unsigned long window_width_;
  unsigned long window_height_;
  std::vector<std::vector<glm::dvec3>> image_;
public:
  const std::vector<std::vector<glm::dvec3>> &getImage() const;
  void setImage(const std::vector<std::vector<glm::dvec3>> &Image);
};

#endif //RAYTRACERV2_CANVAS_H
