#include <iostream>
#include "Canvas.h"
#include <glm/ext.hpp>
#include "ExtVec3.h"
#include <glm/gtx/string_cast.hpp>
#include "Ray.h"
#include <string>
#include "Sphere.h"
#include "Light.h"
#include "World.h"
#include "Camera.h"
#include <chrono>
#include "Shape.h"
int main() {

  auto start = std::chrono::high_resolution_clock::now();

  /*Sphere floor;
  floor.setTransform(glm::scale(glm::dmat4(1.0f), glm::dvec3(10.0f, 0.01f, 10.0f)));
  Material material1;
  material1.setColor(glm::dvec3(1.0f, 0.9f, 0.9f));
  material1.setSpecular(0.0f);
  floor.setMaterial(material1);
  Sphere left_wall;
  left_wall.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(0.0f, 0.0f, 5.0f)) *
      glm::rotate(glm::dmat4(1.0f), -glm::pi<double>() / 4, glm::dvec3(0.0f, 1.0f, 0.0f)) *
      glm::rotate(glm::dmat4(1.0f), glm::pi<double>() / 2, glm::dvec3(1.0f, 0.0f, 0.0f)) *
      glm::scale(glm::dmat4(1.0f), glm::dvec3(10.0f, 0.01f, 10.0f)));
  left_wall.setMaterial(material1);

  Sphere right_wall;
  right_wall.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(0.0f, 0.0f, 5.0f)) *
      glm::rotate(glm::dmat4(1.0f), glm::pi<double>() / 4, glm::dvec3(0.0f, 1.0f, 0.0f)) *
      glm::rotate(glm::dmat4(1.0f), glm::pi<double>() / 2, glm::dvec3(1.0f, 0.0f, 0.0f)) *
      glm::scale(glm::dmat4(1.0f), glm::dvec3(10.0f, 0.01f, 10.0f)));
  right_wall.setMaterial(material1);

  Sphere middle;
  middle.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(-0.5f, 1.0f, 0.5f)));
  Material middle_material;
  middle_material.setColor(glm::dvec3(0.1f, 1.0f, 0.5f));
  middle_material.setDiffuse(0.7f);
  middle_material.setSpecular(0.3f);
  middle.setMaterial(middle_material);

  Sphere right;
  right.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(1.5f, 0.5f, -0.5f)) *
      glm::scale(glm::dmat4(1.0f), glm::dvec3(0.5f)));
  Material right_material;
  right_material.setColor(glm::dvec3(0.5f, 1.0f, 0.1f));
  right_material.setDiffuse(0.7f);
  right_material.setSpecular(0.3f);
  right.setMaterial(right_material);

  Sphere left;
  left.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(-1.5f, 0.33f, -0.75f)) *
      glm::scale(glm::dmat4(1.0f), glm::dvec3(0.33f)));
  Material left_material;
  left_material.setColor(glm::dvec3(1.0f, 0.8f, 0.1f));
  left_material.setDiffuse(0.7f);
  left_material.setSpecular(0.3f);
  left.setMaterial(left_material);

  World world;
  world.setLight(Light(glm::dvec3(1.0f), glm::dvec4(-10.0f, 10.0f, -10.0f, 1.0f)));
  world.addSphere(floor);
  world.addSphere(left_wall);
  world.addSphere(right_wall);
  world.addSphere(middle);
  world.addSphere(right);
  world.addShapes(left);
  Camera camera(1920, 1080, glm::pi<double>() / 3);
  camera.setTransformMatrix(view_transform(glm::dvec4(0.0f, 1.5f, -5.0f, 1.0f),
                                           glm::dvec4(0.0f, 1.0f, 0.0f, 1.0f),
                                           glm::dvec4(0.0f, 1.0f, 0.0f, 0.0f)));
  Canvas canvas = camera.render(world);

  canvas.canvas_to_ppm();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;*/
  return 0;
}
