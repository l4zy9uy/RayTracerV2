//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_MATERIAL_H
#define RAYTRACERV2_MATERIAL_H

#include <glm/vec3.hpp>

class Material {
public:
    Material(const glm::vec3 &color, float ambient, float diffuse, float specular, float shininess);

    Material();

private:
    glm::vec3 color_;
    float ambient_;
    float diffuse_;
    float specular_;
public:
    const glm::vec3 &getColor() const;

    void setColor(const glm::vec3 &color);

    float getAmbient() const;

    void setAmbient(float ambient);

    float getDiffuse() const;

    void setDiffuse(float diffuse);

    float getSpecular() const;

    void setSpecular(float specular);

    float getShininess() const;

    void setShininess(float shininess);

private:
    float shininess_;
};


#endif //RAYTRACERV2_MATERIAL_H
