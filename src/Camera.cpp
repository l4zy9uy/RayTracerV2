//
// Created by l4zy9uy on 3/2/24.
//

#include "Camera.h"

Camera::Camera(int horizontal_size, int vertical_size, double fieldOfView) : horizontal_size_(horizontal_size), vertical_size_(vertical_size), field_of_view_(fieldOfView) {
  transform_matrix_ = glm::dmat4(1.0);
  double half_view = tan(field_of_view_ / 2);
  double aspect = static_cast<double>(horizontal_size_) / static_cast<double>(vertical_size_);
  if (aspect >= 1) {
    half_width_ = half_view;
    half_height_ = half_view / aspect;
  } else {
    half_width_ = half_view * aspect;
    half_height_ = half_view;
  }

  pixel_size_ = half_width_ * 2 / static_cast<double>(horizontal_size_);
}

int Camera::getHorizontalSize() const {
  return horizontal_size_;
}

void Camera::setHorizontalSize(int horizontal_size) {
  horizontal_size_ = horizontal_size;
}

int Camera::getVerticalSize() const {
  return vertical_size_;
}

void Camera::setVerticalSize(int vertical_size) {
  vertical_size_ = vertical_size;
}

double Camera::getFieldOfView() const {
  return field_of_view_;
}

void Camera::setFieldOfView(double fieldOfView) {
  field_of_view_ = fieldOfView;
}

const glm::dmat4 &Camera::getTransformMatrix() const {
  return transform_matrix_;
}

void Camera::setTransformMatrix(const glm::dmat4 &transformMatrix) {
  transform_matrix_ = transformMatrix;
}

double Camera::getHalfWidth() const {
  return half_width_;
}

void Camera::setHalfWidth(double halfWidth) {
  half_width_ = halfWidth;
}

double Camera::getHalfHeight() const {
  return half_height_;
}

void Camera::setHalfHeight(double halfHeight) {
  half_height_ = halfHeight;
}

double Camera::getPixelSize() const {
  return pixel_size_;
}

void Camera::setPixelSize(double pixelSize) {
  pixel_size_ = pixelSize;
}

Ray Camera::ray_for_pixel(const double &px, const double &py) {
  auto xOffset = (px + 0.5f) * pixel_size_;
  auto yOffset = (py + 0.5f) * pixel_size_;
  auto world_x = half_width_ - xOffset;
  auto world_y = half_height_ - yOffset;

  auto pixel = glm::inverse(transform_matrix_) * glm::dvec4(world_x, world_y, -1.0f, 1.0f);
  auto origin = glm::inverse(transform_matrix_) * glm::dvec4(0.0f, 0.0f, 0.0f, 1.0f);
  auto direction = glm::normalize(pixel - origin);
  return {origin, direction};
}

Canvas Camera::render(World &world) {
  Canvas image(horizontal_size_, vertical_size_);
  for (int y = 0; y < horizontal_size_; y++) {
    for (int x = 0; x < vertical_size_; x++) {
      auto ray = ray_for_pixel(static_cast<double>(y), static_cast<double>(x));
      auto color = world.color_at(ray);
      image.writePixel(y, x, color);
    }
  }
  return image;
}
