//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_LIGHT_H
#define RAYTRACERV2_LIGHT_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Material.h"
class Light {
public:
    Light();

    Light(const glm::vec3 &intensity, const glm::vec4 &position);

private:
    glm::vec3 intensity_{};
public:
    const glm::vec3 &getIntensity() const;

    void setIntensity(const glm::vec3 &intensity);

    const glm::vec4 &getPosition() const;

    void setPosition(const glm::vec4 &position);
    glm::vec3 lighting(const Material &material, const glm::vec4 &position, const glm::vec4 &eyev, const glm::vec4 &normalv);

private:
    glm::vec4 position_{};

};


#endif //RAYTRACERV2_LIGHT_H
