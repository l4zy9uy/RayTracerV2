//
// Created by l4zy9uy on 2/27/24.
//

#ifndef RAYTRACERV2_EXTVEC3_H
#define RAYTRACERV2_EXTVEC3_H
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
struct Projectile {
    Projectile(const glm::vec3 &position, const glm::vec3 &velocity);

    glm::vec3 position;
    glm::vec3 velocity;
};

struct Environment {
    Environment(const glm::vec3 &gravity, const glm::vec3 &wind);

    glm::vec3 gravity;
    glm::vec3 wind;
};

Projectile tick(const Environment &env, const Projectile &proj);
glm::mat4 view_transform(const glm::vec4 &from, const glm::vec4 &to, const glm::vec4 &up);

#endif //RAYTRACERV2_EXTVEC3_H
