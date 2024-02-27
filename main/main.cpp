#include <iostream>
#include "../include/Canvas.h"
#include <glm/ext.hpp>
#include "../include/ExtVec3.h"
#include <glm/gtx/string_cast.hpp>
int main() {

    auto start = glm::vec3(0.0f, 1.0f, 0.0f);
    auto velocity = glm::normalize(glm::vec3(1.0f, 1.8f, 0.0f)) * 11.25f;
    auto p = Projectile(start, velocity);
    glm::vec3 gravity(0.0f, -0.1f, 0.0f);
    glm::vec3 wind(-0.01f, 0.0f, 0.0f);
    auto e = Environment(gravity, wind);
    Canvas c(900, 550);
    while(p.position.y >= 0)
    {
        std::cout << glm::to_string(p.position) << "\n";
        c.writePixel(static_cast<int>(p.position.x), c.getWindowHeight() - static_cast<int>(p.position.y), glm::vec3(1.0f, 0.0f, 0.0f));
        p = tick(e, p);
    }
    c.canvas_to_ppm();
    return 0;
}
