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
private:
    int hsize_;
    int vsize_;
    float field_of_view_;
public:
    int getHsize() const;

    void setHsize(int hsize);

    int getVsize() const;

    void setVsize(int vsize);

    float getFieldOfView() const;

    void setFieldOfView(float fieldOfView);

    const glm::mat4 &getTransformMatrix() const;

    void setTransformMatrix(const glm::mat4 &transformMatrix);

    float getHalfWidth() const;

    void setHalfWidth(float halfWidth);

    float getHalfHeight() const;

    void setHalfHeight(float halfHeight);

    float getPixelSize() const;

    void setPixelSize(float pixelSize);
    Ray ray_for_pixel(const float &px, const float &py);
    Canvas render(World &world);
private:
    glm::mat4 transform_matrix_;
    float half_width_;
    float half_height_;
    float pixel_size_;
public:
    Camera(int hsize, int vsize, float fieldOfView);
};


#endif //RAYTRACERV2_CAMERA_H
