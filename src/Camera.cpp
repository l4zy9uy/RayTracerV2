//
// Created by l4zy9uy on 3/2/24.
//

#include "Camera.h"
#include <thread>

Camera::Camera(const unsigned int &horizontal_size,
               const unsigned int &vertical_size,
               const double &fieldOfView) :
               horizontal_size_(horizontal_size), vertical_size_(vertical_size), field_of_view_(fieldOfView), image_(horizontal_size, vertical_size) {
  transform_matrix_ = glm::dmat4(1.0);
  double half_view = tan(field_of_view_ / 2);
  double aspect = static_cast<double>(horizontal_size_) / static_cast<double>(vertical_size_);
  if (aspect >= 1) {
    half_width_ = half_view;
    half_height_ = half_view / aspect;
  }
  else {
    half_width_ = half_view * aspect;
    half_height_ = half_view;
  }

  pixel_size_ = half_width_ * 2 / static_cast<double>(horizontal_size_);
}

const unsigned int & Camera::getHorizontalSize() const {
  return horizontal_size_;
}

void Camera::setHorizontalSize(const unsigned int &horizontal_size) {
  horizontal_size_ = horizontal_size;
}

const unsigned int & Camera::getVerticalSize() const {
  return vertical_size_;
}

void Camera::setVerticalSize(const int &vertical_size) {
  vertical_size_ = vertical_size;
}

const double & Camera::getFieldOfView() const {
  return field_of_view_;
}

void Camera::setFieldOfView(const double &fieldOfView) {
  field_of_view_ = fieldOfView;
}

const glm::dmat4 &Camera::getTransformMatrix() const {
  return transform_matrix_;
}

void Camera::setTransformMatrix(const glm::dmat4 &transformMatrix) {
  transform_matrix_ = transformMatrix;
}

const double & Camera::getHalfWidth() const {
  return half_width_;
}

void Camera::setHalfWidth(const double &halfWidth) {
  half_width_ = halfWidth;
}

const double & Camera::getHalfHeight() const {
  return half_height_;
}

void Camera::setHalfHeight(const double &halfHeight) {
  half_height_ = halfHeight;
}

const double & Camera::getPixelSize() const {
  return pixel_size_;
}

void Camera::setPixelSize(const double &pixelSize) {
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

void Camera::render_at_thread(Canvas &image, World &world, const unsigned long &start, const unsigned long &jump) {
  for (auto y = start; y < horizontal_size_; y+=jump) {
    for (auto x = 0; x < vertical_size_; x++) {
      auto ray = ray_for_pixel(static_cast<double>(y), static_cast<double>(x));
      auto color = world.color_at(ray, 5);
        image.writePixel(y, x, color);
    }
  }
}

Canvas & Camera::render(World &world) {
  const unsigned long Num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> thread_vector;
  thread_vector.reserve(Num_threads);
  for(auto i = 0; i < Num_threads; i++) {
    thread_vector.emplace_back(&Camera::render_at_thread,
                               this,
                               std::ref(image_),
                               std::ref(world),
                               i,
                               std::ref(Num_threads));
  }
  for(auto &thread : thread_vector) {
    if(thread.joinable()) thread.join();
  }
  return image_;
}
