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
#include "Pattern/StripePtn.h"
#include "Pattern/GradientPtn.h"
#include "Pattern/RingPtn.h"
#include "Pattern/CheckerPtn.h"
int main() {
  auto start = std::chrono::high_resolution_clock::now();

  /*Sphere floor;
  floor.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(10.0, 0.01, 10.0)));
  Material material1;
  material1.setColor(glm::dvec3(1.0, 0.9, 0.9));
  material1.setSpecular(0.0);
  CheckerPtn checkerPtn(glm::dvec3(1.0), glm::dvec3(0.0));
  checkerPtn.setTransformationMatrix(glm::scale(glm::dmat4(1.0), glm::dvec3(0.001)));
  material1.setPatternPtr(std::make_shared<CheckerPtn>(checkerPtn));
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
  right_wall.setMaterial(material1);*/

  Sphere middle;
  middle.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(-0.5, 1.0, 0.5)));
  Material middle_material;
  middle_material.setColor(glm::dvec3(0.1, 1.0, 0.5));
  middle_material.setDiffuse(0.7);
  middle_material.setSpecular(0.3);
  GradientPtn gradientPtn(glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0));
  gradientPtn.setTransformationMatrix(glm::translate(glm::dmat4(1.0), glm::dvec3(1, 0.1, 0.0)) * glm::scale(glm::dmat4(1.0), glm::dvec3(2)));
  middle_material.setPatternPtr(std::make_shared<GradientPtn>(gradientPtn));
  middle.setMaterial(middle_material);

  Sphere right;
  right.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(1.5, 0.5, -0.5)) *
      glm::scale(glm::dmat4(1.0), glm::dvec3(0.5)));
  Material right_material;
  right_material.setColor(glm::dvec3(0.5, 1.0, 0.1));
  right_material.setDiffuse(0.7);
  right_material.setSpecular(0.3);
  StripePtn stripePtn(glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(1.0));
  stripePtn.setTransformationMatrix(glm::translate(glm::dmat4(1.0), glm::dvec3(1, 0.1, 0.0)) * glm::scale(glm::dmat4(1.0), glm::dvec3(0.1)));
  right_material.setPatternPtr(std::make_shared<StripePtn>(stripePtn));
  right.setMaterial(right_material);

  Sphere left;
  left.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(-1.5, 1.0, -0.75)) *
      glm::scale(glm::dmat4(1.0), glm::dvec3(0.5)));
  Material left_material;
  left_material.setColor(glm::dvec3(0.0, 0.0, 0.0));
  left_material.setDiffuse(0.7);
  left_material.setSpecular(0.3);
  RingPtn ringPtn(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(1.0, 1.0, 1.0));
  ringPtn.setTransformationMatrix(glm::scale(glm::dmat4(1.0), glm::dvec3(1.0)) * glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 2.0)));
  left_material.setPatternPtr(std::make_shared<RingPtn>(ringPtn));
  left.setMaterial(left_material);

  Plane p;
  Material material1;
  CheckerPtn checkerPtn(glm::dvec3(1.0), glm::dvec3(0.0));
  checkerPtn.setTransformationMatrix(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.1, 0.0)) * glm::scale(glm::dmat4(1.0), glm::dvec3(1)));
  material1.setPatternPtr(std::make_shared<CheckerPtn>(checkerPtn));
  p.setMaterial(material1);
  World world;
  world.setLight(Light(glm::dvec3(1.0), glm::dvec4(-10.0, 10.0, -10.0, 1.0)));
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
  std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
  /*Sphere left;
  left.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(-1.5, 1.0, -0.75)) *
      glm::scale(glm::dmat4(1.0), glm::dvec3(0.5)));
  Material left_material;
  RingPtn ringPtn(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(1.0, 1.0, 1.0));
  ringPtn.setTransformationMatrix(glm::scale(glm::dmat4(1.0), glm::dvec3(0.25)) * glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 0.0)));
  left_material.setPatternPtr(std::make_shared<RingPtn>(ringPtn));
  left.setMaterial(left_material);

  for(auto i = 0.0; i <= 2.1; i+= 0.25) {
    auto c = ringPtn.pattern_at_shape(left, glm::dvec4(i, 0.0, 0.0, 1.0));
    std::cout << glm::to_string(c) << "\n";
  }*/
  return 0;
}
