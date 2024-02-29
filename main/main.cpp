#include <iostream>
#include "../include/Canvas.h"
#include <glm/ext.hpp>
#include "../include/ExtVec3.h"
#include <glm/gtx/string_cast.hpp>
#include "../include/Ray.h"
#include <string>
#include "../include/Sphere.h"
int main() {
    glm::vec4 ray_origin(0.0f, 0.0f, -5.0f, 1.0f);
    float wall_z = 10.0f;
    float wall_size = 7.0f;
    int canvas_pixels = 100;
    float pixel_size = wall_size / canvas_pixels;
    float half = wall_size / 2;
    Canvas canvas(canvas_pixels, canvas_pixels);
    glm::vec3 color(1.0f, 0.0f, 0.0f);
    Sphere s;
    for(int i = 0; i < canvas_pixels; i++)
    {
        auto world_y = half - pixel_size * i;
        for(int j = 0; j < canvas_pixels - 1; j++)
        {
            auto world_x = -half + pixel_size * j;
            glm::vec4 position(world_x, world_y, wall_z, 1.0f);
            Ray r(ray_origin, glm::normalize(position - ray_origin));
            auto xs = s.intersect(r);
            if(xs.hit().has_value())
            {
                canvas.writePixel(i, j, color);
                std::cout << "i: " << i << " j: " << j << "\n";
            }
        }
    }
    canvas.canvas_to_ppm();
    return 0;
}
