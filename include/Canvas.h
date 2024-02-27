//
// Created by l4zy9uy on 2/27/24.
//

#ifndef RAYTRACERV2_CANVAS_H
#define RAYTRACERV2_CANVAS_H
#include <glm/vec3.hpp>
#include <vector>

class Canvas {
public:
    Canvas(int windowWidth, int windowHeight);
    void writePixel(const int &y, const int &x, const glm::vec3 &color);
    const glm::vec3 &pixelAt(const int &y, const int &x) const;
    void canvas_to_ppm();
private:
    int window_width_;
public:
    int getWindowWidth() const;

    void setWindowWidth(int windowWidth);

    int getWindowHeight() const;

    void setWindowHeight(int windowHeight);

private:
    int window_height_;
    std::vector<std::vector<glm::vec3>> image_;
};


#endif //RAYTRACERV2_CANVAS_H
