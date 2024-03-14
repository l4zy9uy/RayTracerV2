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
#include "Pattern/SolidPtn.h"
#include "Pattern/BlendedPtn.h"
#include <limits>
#include <iomanip>
#include "Pattern/TestPtn.h"

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  Sphere middle;
  middle.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(-0.5, 1.0, 0.5)));
  Material middle_material;
  middle_material.color_ = (glm::dvec3(0.1, 1.0, 0.5));
  middle_material.diffuse_ = (0.7);
  middle_material.specular_ = (0.3);
  GradientPtn gradientPtn(glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0));
  gradientPtn.setTransformationMatrix(
      glm::translate(glm::dmat4(1.0), glm::dvec3(1, 0.1, 0.0)) * glm::scale(glm::dmat4(1.0), glm::dvec3(2)));
  middle_material.pattern_ptr_ = (std::make_shared<GradientPtn>(gradientPtn));
  middle.setMaterial(middle_material);

  Sphere right;
  right.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(1.5, 0.5, -0.5)) *
      glm::scale(glm::dmat4(1.0), glm::dvec3(0.5)));
  Material right_material;
  right_material.color_ = (glm::dvec3(0.5, 1.0, 0.1));
  right_material.diffuse_ = (0.7);
  right_material.specular_ = (0.3);
  StripePtn stripePtn(glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(1.0));
  stripePtn.setTransformationMatrix(
      glm::translate(glm::dmat4(1.0), glm::dvec3(1, 0.1, 0.0)) * glm::scale(glm::dmat4(1.0), glm::dvec3(0.1)));
  right_material.pattern_ptr_ = (std::make_shared<StripePtn>(stripePtn));
  right.setMaterial(right_material);

  Sphere left;
  left.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(-1.5, 1.0, -0.75)) *
      glm::scale(glm::dmat4(1.0), glm::dvec3(0.5)));
  Material left_material;
  left_material.color_ = (glm::dvec3(0.0, 0.0, 0.0));
  left_material.diffuse_ = (0.7);
  left_material.specular_ = (0.3);
  left_material.reflective_ = (1.0);
  RingPtn ringPtn(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(1.0, 1.0, 1.0));
  ringPtn.setTransformationMatrix(
      glm::scale(glm::dmat4(1.0), glm::dvec3(1.0)) * glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 2.0)));
  left_material.pattern_ptr_ = (std::make_shared<RingPtn>(ringPtn));
  left.setMaterial(left_material);

  Plane p;
  Material material1;
  material1.reflective_ = (1.0);
  StripePtn checkerPtn(glm::dvec3(1.0), glm::dvec3(0.0));
  StripePtn checkerPtn2(glm::dvec3(0.0), glm::dvec3(1.0, 0.0, 0.0));
  checkerPtn2.setTransformationMatrix(glm::rotate(glm::dmat4(1.0), glm::pi<double>()/2, glm::dvec3(0.0, 0.0, 1.0)));
  BlendedPtn blendedPtn(std::make_shared<StripePtn>(checkerPtn), std::make_shared<StripePtn>(checkerPtn2));
  material1.pattern_ptr_ = (std::make_shared<BlendedPtn>(blendedPtn));
  p.setMaterial(material1);

  World world;
  world.setLight(Light(glm::dvec3(1.0), glm::dvec4(-10.0, 10.0, -10.0, 1.0)));
  world.addShape(std::make_shared<Sphere>(left));
  world.addShape(std::make_shared<Sphere>(right));
  world.addShape(std::make_shared<Sphere>(middle));
  world.addShape(std::make_shared<Plane>(p));

  Camera camera(800, 400, glm::pi<double>() / 3);
  camera.setTransformMatrix(view_transform(glm::dvec4(0.0, 1.5, -5.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 0.0)));
  Canvas canvas = camera.render(world);

  canvas.canvas_to_ppm();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
  return 0;
}
