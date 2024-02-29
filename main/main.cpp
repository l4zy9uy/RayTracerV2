#include <iostream>
#include "../include/Canvas.h"
#include <glm/ext.hpp>
#include "../include/ExtVec3.h"
#include <glm/gtx/string_cast.hpp>
#include "../include/Ray.h"
#include <string>
#include "../include/Sphere.h"
int main() {
    Ray r(glm::vec4(0.0f, 0.0f, -5.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    std::shared_ptr<Sphere> s = std::make_shared<Sphere>();
    s->setTransform(glm::scale(glm::identity<glm::mat4>(), glm::vec3(2.0f)));
    auto xs = s->intersect(r);
    std::cout << xs.getIntersections()[0].getT() << " " << xs.getIntersections()[1].getT() << "\n";
    return 0;
}
