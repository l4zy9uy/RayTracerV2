//
// Created by l4zy9uy on 3/1/24.
//

#include "Material.h"

Material::Material(const glm::vec3 &color, float ambient, float diffuse, float specular, float shininess) : color_(
        color), ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess) {}

Material::Material() : color_(
        glm::vec3(1.0f)), ambient_(0.1f), diffuse_(0.9f), specular_(0.9f), shininess_(200.0f) {}

const glm::vec3 &Material::getColor() const {
    return color_;
}

void Material::setColor(const glm::vec3 &color) {
    color_ = color;
}

float Material::getAmbient() const {
    return ambient_;
}

void Material::setAmbient(float ambient) {
    ambient_ = ambient;
}

float Material::getDiffuse() const {
    return diffuse_;
}

void Material::setDiffuse(float diffuse) {
    diffuse_ = diffuse;
}

float Material::getSpecular() const {
    return specular_;
}

void Material::setSpecular(float specular) {
    specular_ = specular;
}

float Material::getShininess() const {
    return shininess_;
}

void Material::setShininess(float shininess) {
    shininess_ = shininess;
}
