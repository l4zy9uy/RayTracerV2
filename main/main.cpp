#include <iostream>
#include "../include/Canvas.h"
#include <glm/ext.hpp>
#include "../include/ExtVec3.h"
#include <glm/gtx/string_cast.hpp>
#include "../include/Ray.h"
#include <string>
int main() {

    int window_width = 500;
    int window_height = 500;
    Canvas c(window_width, window_height);
    float rotation = 0;
    float radius = 200;
    int center_y = window_height/2;
    int center_x = window_width/2;
    auto pos = glm::vec4(-radius, 0.0f, 0.0f, 1.0f);
    while(rotation < 360)
    {
        auto transform = pos *
                         glm::transpose(glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))) *
                         glm::transpose(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))) *
                         glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
        auto pixel = transform + glm::vec4(center_x, center_y, 0.0f, 0.0f);
        std::cout << glm::to_string(pixel) << "\n";
        c.writePixel(static_cast<int>(pixel.x), static_cast<int>(pixel.y), glm::vec3(1.0f));
        rotation += 30;
    }
    Ray r(glm::vec4(2.0f, 3.0f, 4.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    std::cout << glm::to_string(position(r, 0)) << "\n";
    std::cout << glm::to_string(position(r, 1)) << "\n";
    std::cout << glm::to_string(position(r, -1)) << "\n";
    std::cout << glm::to_string(position(r, 2.5)) << "\n";
    c.canvas_to_ppm();

    return 0;
}
