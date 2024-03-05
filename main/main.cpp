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
#include "Plane.h"
#include "Pattern.h"

int main() {
  /*auto start = std::chrono::high_resolution_clock::now();

  *//*Sphere floor;
  floor.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(10.0, 0.01, 10.0)));
  Material material1;
  material1.setColor(glm::dvec3(1.0, 0.9, 0.9));
  material1.setSpecular(0.0);
  floor.setMaterial(material1);
  Sphere left_wall;
  left_wall.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 5.0)) *
      glm::rotate(glm::dmat4(1.0), -glm::pi<double>() / 4, glm::dvec3(0.0, 1.0, 0.0)) *
      glm::rotate(glm::dmat4(1.0), glm::pi<double>() / 2, glm::dvec3(1.0, 0.0, 0.0)) *
      glm::scale(glm::dmat4(1.0), glm::dvec3(10.0, 0.01, 10.0)));
  left_wall.setMaterial(material1);

  Sphere right_wall;
  right_wall.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 5.0)) *
      glm::rotate(glm::dmat4(1.0), glm::pi<double>() / 4, glm::dvec3(0.0, 1.0, 0.0)) *
      glm::rotate(glm::dmat4(1.0), glm::pi<double>() / 2, glm::dvec3(1.0, 0.0, 0.0)) *
      glm::scale(glm::dmat4(1.0), glm::dvec3(10.0, 0.01, 10.0)));
  right_wall.setMaterial(material1);*//*

  Sphere middle;
  middle.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(-0.5, 1.0, 0.5)));
  Material middle_material;
  middle_material.setColor(glm::dvec3(0.1, 1.0, 0.5));
  middle_material.setDiffuse(0.7);
  middle_material.setSpecular(0.3);
  middle.setMaterial(middle_material);

  Sphere right;
  right.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(1.5, 0.5, -0.5)) *
      glm::scale(glm::dmat4(1.0), glm::dvec3(0.5)));
  Material right_material;
  right_material.setColor(glm::dvec3(0.5, 1.0, 0.1));
  right_material.setDiffuse(0.7);
  right_material.setSpecular(0.3);
  right.setMaterial(right_material);

  Sphere left;
  left.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(-1.5, 0.33, -0.75)) *
      glm::scale(glm::dmat4(1.0), glm::dvec3(0.33)));
  Material left_material;
  left_material.setColor(glm::dvec3(1.0, 0.8, 0.1));
  left_material.setDiffuse(0.7);
  left_material.setSpecular(0.3);
  left.setMaterial(left_material);

  Plane p;
  World world;
  world.setLight(Light(glm::dvec3(1.0), glm::dvec4(-10.0, 10.0, -10.0, 1.0)));
  *//*world.addShape(std::make_shared<Sphere>(floor));
  world.addShape(std::make_shared<Sphere>(left_wall));
  world.addShape(std::make_shared<Sphere>(right_wall));*//*
  world.addShape(std::make_shared<Sphere>(left));
  world.addShape(std::make_shared<Sphere>(right));
  world.addShape(std::make_shared<Sphere>(middle));
  world.addShape(std::make_shared<Plane>(p));
  Camera camera(3840, 2160, glm::pi<double>() / 3);
  camera.setTransformMatrix(view_transform(glm::dvec4(0.0, 1.5, -5.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 0.0)));
  Canvas canvas = camera.render(world);

  canvas.canvas_to_ppm();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;*/
  Pattern pattern(glm::vec3(1.0), glm::vec3(0.0));
  Material m;
  m.setPattern(pattern);
  m.setAmbient(1.0);
  m.setDiffuse(0.0);
  m.setSpecular(0.0);
  glm::dvec4 eyev(0.0, 0.0, -1.0, 0.0);
  glm::dvec4 normalv(0.0, 0.0, -1.0, 0.0);
  Light light(glm::dvec3(1.0), glm::dvec4(0.0, 0.0, -10.0, 1.0));
  auto c1 = light.lighting(m, glm::dvec4(0.9, 0.0, 0.0, 1.0), eyev, normalv, false);
  auto c2 = light.lighting(m, glm::dvec4(1.1, 0.0, 0.0, 1.0), eyev, normalv, false);
  std::cout << glm::to_string(c1) << "\n";
  std::cout << glm::to_string(c2) << "\n";


  return 0;
}
