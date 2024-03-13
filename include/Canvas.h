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
  [[nodiscard]] const int & getWindowWidth() const;
  void setWindowWidth(const int &windowWidth);
  [[nodiscard]] const int & getWindowHeight() const;
  void setWindowHeight(const int &windowHeight);
public:
  void writePixel(const int &y, const int &x, const glm::dvec3 &color);
  [[nodiscard]] const glm::dvec3 &pixelAt(const int &y, const int &x) const;
  void canvas_to_ppm();
private:
  unsigned int window_width_;
  unsigned int window_height_;
  std::vector<std::vector<glm::dvec3>> image_;
};

#endif //RAYTRACERV2_CANVAS_H
