//
// Created by l4zy9uy on 2/27/24.
//

#include "Canvas.h"
#include <fstream>
#include <algorithm>
Canvas::Canvas(const unsigned int &windowWidth, const unsigned int &windowHeight) : window_width_(
    windowWidth), window_height_(windowHeight) {
  for (int i = 0; i < windowHeight; i++) {
    std::vector<glm::dvec3> temp_vector(windowWidth, glm::dvec3(0));
    image_.push_back(temp_vector);
  }
}

void Canvas::writePixel(const int &y, const int &x, const glm::dvec3 &color) {
  image_[x][y] = color;
}

const glm::dvec3 &Canvas::pixelAt(const int &y, const int &x) const {
  return image_[x][y];
}

void Canvas::canvas_to_ppm() {
  std::fstream myFile;
  myFile.open("../../image.ppm", std::ios::out);
  myFile << "P3\n" << window_width_ << " " << window_height_ << "\n" << "255" << "\n";
  for (int i = 0; i < window_height_; i++) {
    for (int j = 0; j < window_width_; j++) {
      auto temp = image_[i][j] * 256.0;
      int x = static_cast<int>(std::clamp(temp.x, 0.0, 255.0));
      int y = static_cast<int>(std::clamp(temp.y, 0.0, 255.0));
      int z = static_cast<int>(std::clamp(temp.z, 0.0, 255.0));
      myFile << x << " " << y << " " << z << " ";
    }
    myFile << "\n";
  }
  myFile.close();
}

const int & Canvas::getWindowWidth() const {
  return window_width_;
}

void Canvas::setWindowWidth(const int &windowWidth) {
  Canvas::window_width_ = windowWidth;
}

const int & Canvas::getWindowHeight() const {
  return window_height_;
}

void Canvas::setWindowHeight(const int &windowHeight) {
  Canvas::window_height_ = windowHeight;
}

