//
// Created by l4zy9uy on 3/2/24.
//

#ifndef RAYTRACERV2_CAMERA_H
#define RAYTRACERV2_CAMERA_H
#include <glm/glm.hpp>
#include "Ray.h"
#include "World.h"
#include "Canvas.h"

class Camera {
public:
  [[nodiscard]] int getHorizontalSize() const;

  void setHorizontalSize(int horizontal_size);

  [[nodiscard]] int getVerticalSize() const;

  void setVerticalSize(int vertical_size);

  [[nodiscard]] double getFieldOfView() const;

  void setFieldOfView(double fieldOfView);

  [[nodiscard]] const glm::dmat4 &getTransformMatrix() const;

  void setTransformMatrix(const glm::dmat4 &transformMatrix);

  [[nodiscard]] double getHalfWidth() const;

  void setHalfWidth(double halfWidth);

  [[nodiscard]] double getHalfHeight() const;

  void setHalfHeight(double halfHeight);

  [[nodiscard]] double getPixelSize() const;

  void setPixelSize(double pixelSize);
  Ray ray_for_pixel(const double &px, const double &py);
  Canvas render(World &world);
private:
  glm::dmat4 transform_matrix_{};
  double half_width_;
  double half_height_;
  double pixel_size_;
  int horizontal_size_;
  int vertical_size_;
  double field_of_view_;
public:
  Camera(int horizontal_size, int vertical_size, double fieldOfView);
};

#endif //RAYTRACERV2_CAMERA_H
