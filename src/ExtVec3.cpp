//
// Created by l4zy9uy on 2/27/24.
//

#include "ExtVec3.h"

Projectile tick(const Environment &env, const Projectile &proj) {
    auto position = proj.position + proj.velocity;
    auto velocity = proj.velocity + env.gravity + env.wind;
    return Projectile(position, velocity);
}

Projectile::Projectile(const glm::vec3 &position, const glm::vec3 &velocity) : position(position), velocity(velocity) {}

Environment::Environment(const glm::vec3 &gravity, const glm::vec3 &wind) : gravity(gravity), wind(wind) {}
