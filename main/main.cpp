#include <iostream>
#include "Canvas.h"
#include <glm/ext.hpp>
#include "ExtVec3.h"
#include <glm/gtx/string_cast.hpp>
#include "Ray.h"
#include <string>
#include "Sphere.h"
#include "Light.h"

int main() {
    glm::vec4 ray_origin(0.0f, 0.0f, -5.0f, 1.0f);
    float wall_z = 10.0f;
    float wall_size = 7.0f;
    int canvas_pixels = 500;
    float pixel_size = wall_size / canvas_pixels;
    float half = wall_size / 2;
    Canvas canvas(canvas_pixels, canvas_pixels);
    glm::vec3 color(1.0f, 0.0f, 0.0f);
    Sphere s;
    glm::mat4 scale = glm::transpose(glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.0f, 2.0f, 1.0f)));
    glm::mat4 rotate = glm::rotate(glm::identity<glm::mat4>(), glm::pi<float>() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
    s.setTransform(rotate * scale);
    Material m;
    m.setColor(glm::vec3(1.0f, 0.2f, 1.0f));
    s.setMaterial(m);
    glm::vec4 light_position(-10.0, 10.0f, -10.0f, 1.0f);
    glm::vec3 light_color(1.0f);
    Light light(light_color, light_position);

    for (int i = 0; i < canvas_pixels; i++) {
        auto world_y = half - pixel_size * i;
        for (int j = 0; j < canvas_pixels - 1; j++) {
            auto world_x = -half + pixel_size * j;
            glm::vec4 position_(world_x, world_y, wall_z, 1.0f);
            Ray r(ray_origin, glm::normalize(position_ - ray_origin));
            auto xs = s.intersect(r);
            auto hit = xs.hit();
            if (hit.has_value()) {
                auto point = position(r, hit->getT());
                auto temp_s = hit->getSpherePtr();
                auto normal = temp_s->normal_at(point);
                auto eye = -r.getDirectionVector();
                color = light.lighting(temp_s->getMaterial(), point, eye, normal);
                canvas.writePixel(j, i, color);
                //std::cout << "i: " << i << " j: " << j << "\n";
            }
        }
    }
    canvas.canvas_to_ppm();

    return 0;
}
