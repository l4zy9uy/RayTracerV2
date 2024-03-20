//
// Created by l4zy9uy on 3/2/24.
//

#ifndef RAYTRACERV2_CAMERA_H
#define RAYTRACERV2_CAMERA_H
#include <glm/glm.hpp>
#include "Ray.h"
#include "World.h"
#include "Canvas.h"
#include <mutex>

class Camera {
public:
  Camera(const unsigned int &horizontal_size,
         const unsigned int &vertical_size,
         const double &fieldOfView);
public:
  [[nodiscard]] const unsigned int & getHorizontalSize() const;
  void setHorizontalSize(const unsigned int &horizontal_size);
  [[nodiscard]] const unsigned int & getVerticalSize() const;
  void setVerticalSize(const int &vertical_size);
  [[nodiscard]] const double & getFieldOfView() const;
  void setFieldOfView(const double &fieldOfView);
  [[nodiscard]] const glm::dmat4 &getTransformMatrix() const;
  [[nodiscard]] const double & getHalfWidth() const;
  void setHalfWidth(const double &halfWidth);
  [[nodiscard]] const double & getHalfHeight() const;
  void setHalfHeight(const double &halfHeight);
  [[nodiscard]] const double & getPixelSize() const;
  void setPixelSize(const double &pixelSize);
  void setTransformMatrix(const glm::dmat4 &transformMatrix);
public:
  Ray ray_for_pixel(const double &px, const double &py);
  Canvas & render(World &world);
  void render_at_thread(Canvas &image, World &world, const unsigned long &start, const unsigned long &jump);
private:
  glm::dmat4 transform_matrix_{};
  double half_width_;
  double half_height_;
  double pixel_size_;
  unsigned int horizontal_size_;
  unsigned int vertical_size_;
  double field_of_view_;
  Canvas image_;
};

#endif //RAYTRACERV2_CAMERA_H
