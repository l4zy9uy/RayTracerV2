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

  [[nodiscard]] float getFieldOfView() const;

  void setFieldOfView(float fieldOfView);

  [[nodiscard]] const glm::mat4 &getTransformMatrix() const;

  void setTransformMatrix(const glm::mat4 &transformMatrix);

  [[nodiscard]] float getHalfWidth() const;

  void setHalfWidth(float halfWidth);

  [[nodiscard]] float getHalfHeight() const;

  void setHalfHeight(float halfHeight);

  [[nodiscard]] float getPixelSize() const;

  void setPixelSize(float pixelSize);
  Ray ray_for_pixel(const float &px, const float &py);
  Canvas render(World &world);
private:
  glm::mat4 transform_matrix_{};
  float half_width_;
  float half_height_;
  float pixel_size_;
  int horizontal_size_;
  int vertical_size_;
  float field_of_view_;
public:
  Camera(int horizontal_size, int vertical_size, float fieldOfView);
};

#endif //RAYTRACERV2_CAMERA_H
