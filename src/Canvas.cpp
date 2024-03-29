//
// Created by l4zy9uy on 2/27/24.
//

#include "Canvas.h"
#include <fstream>
#include <algorithm>
#include <sstream>

Canvas::Canvas(const unsigned int &windowWidth, const unsigned int &windowHeight) : window_width_(
    windowWidth), window_height_(windowHeight) {
  for (int i = 0; i < windowHeight; i++) {
    std::vector<glm::dvec3> temp_vector(windowWidth, glm::dvec3(0));
    image_.push_back(temp_vector);
  }
}

void Canvas::writePixel(const unsigned long &y, const unsigned long &x, const glm::dvec3 &color) {
  image_[x][y] = color;
}

const glm::dvec3 &Canvas::pixelAt(const int &y, const int &x) const {
  return image_[x][y];
}

void Canvas::canvas_to_ppm() {
  std::stringstream ss;
  std::fstream myFile;
  myFile.open("../../image.ppm", std::ios::out);
  myFile << "P3\n" << window_width_ << " " << window_height_ << "\n" << "255" << "\n";
  for (const auto& row : image_) {
    for (const auto& pixel : row) {
      auto r = static_cast<unsigned short>(std::clamp(pixel.r * 255.0, 0.0, 255.0));
      auto g = static_cast<unsigned short>(std::clamp(pixel.g * 255.0, 0.0, 255.0));
      auto b = static_cast<unsigned short >(std::clamp(pixel.b * 255.0, 0.0, 255.0));
      ss << r << " " << g << " " << b << " ";
    }
    ss << "\n";
  }
  myFile << ss.str();
  myFile.close();
}



const unsigned long & Canvas::getWindowWidth() const {
  return window_width_;
}

void Canvas::setWindowWidth(const unsigned long &windowWidth) {
  Canvas::window_width_ = windowWidth;
}

const unsigned long & Canvas::getWindowHeight() const {
  return window_height_;
}

void Canvas::setWindowHeight(const unsigned long &windowHeight) {
  Canvas::window_height_ = windowHeight;
}
const std::vector<std::vector<glm::dvec3>> &Canvas::getImage() const {
  return image_;
}
void Canvas::setImage(const std::vector<std::vector<glm::dvec3>> &Image) {
  image_ = Image;
}



