//
// Created by l4zy9uy on 3/2/24.
//

#include "Camera.h"

Camera::Camera(int hsize, int vsize, float fieldOfView) : hsize_(hsize), vsize_(vsize), field_of_view_(fieldOfView) {
    transform_matrix_ = glm::mat4(1.0f);
    auto half_view = tan(field_of_view_ / 2);
    float aspect = static_cast<float>(hsize_) / static_cast<float>(vsize_);
    if(aspect >= 1) {
        half_width_ = half_view;
        half_height_ = half_view / aspect;
    }
    else {
        half_width_ =  half_view * aspect;
        half_height_ = half_view;
    }

    pixel_size_ = half_width_ * 2 / static_cast<float>(hsize_);
}

int Camera::getHsize() const {
    return hsize_;
}

void Camera::setHsize(int hsize) {
    hsize_ = hsize;
}

int Camera::getVsize() const {
    return vsize_;
}

void Camera::setVsize(int vsize) {
    vsize_ = vsize;
}

float Camera::getFieldOfView() const {
    return field_of_view_;
}

void Camera::setFieldOfView(float fieldOfView) {
    field_of_view_ = fieldOfView;
}

const glm::mat4 &Camera::getTransformMatrix() const {
    return transform_matrix_;
}

void Camera::setTransformMatrix(const glm::mat4 &transformMatrix) {
    transform_matrix_ = transformMatrix;
}

float Camera::getHalfWidth() const {
    return half_width_;
}

void Camera::setHalfWidth(float halfWidth) {
    half_width_ = halfWidth;
}

float Camera::getHalfHeight() const {
    return half_height_;
}

void Camera::setHalfHeight(float halfHeight) {
    half_height_ = halfHeight;
}

float Camera::getPixelSize() const {
    return pixel_size_;
}

void Camera::setPixelSize(float pixelSize) {
    pixel_size_ = pixelSize;
}

Ray Camera::ray_for_pixel(const float &px, const float &py) {
    auto xOffset = (px + 0.5f) * pixel_size_;
    auto yOffset = (py + 0.5f) * pixel_size_;
    auto world_x = half_width_ - xOffset;
    auto world_y = half_height_ - yOffset;

    auto pixel = glm::inverse(transform_matrix_) * glm::vec4(world_x, world_y, -1.0f, 1.0f);
    auto origin = glm::inverse(transform_matrix_) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    auto direction = glm::normalize(pixel - origin);
    return {origin, direction};
}

Canvas Camera::render(World &world) {
    Canvas image(hsize_, vsize_);
    for(int y = 0; y < vsize_; y++) {
        for(int x = 0; x < hsize_; x++) {
            auto ray = ray_for_pixel(x, y);
            auto color = world.color_at(ray);
            image.writePixel(y, x, color);
        }
    }
    return image;
}
