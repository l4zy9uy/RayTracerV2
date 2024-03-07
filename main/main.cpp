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
#include <limits>
#include <iomanip>
int main() {
  /*auto start = std::chrono::high_resolution_clock::now();

  Sphere middle;
  middle.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(-0.5, 1.0, 0.5)));
  Material middle_material;
  middle_material.setColor(glm::dvec3(0.1, 1.0, 0.5));
  middle_material.setDiffuse(0.7);
  middle_material.setSpecular(0.3);
  GradientPtn gradientPtn(glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0));
  gradientPtn.setTransformationMatrix(
      glm::translate(glm::dmat4(1.0), glm::dvec3(1, 0.1, 0.0)) * glm::scale(glm::dmat4(1.0), glm::dvec3(2)));
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
  stripePtn.setTransformationMatrix(
      glm::translate(glm::dmat4(1.0), glm::dvec3(1, 0.1, 0.0)) * glm::scale(glm::dmat4(1.0), glm::dvec3(0.1)));
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
  ringPtn.setTransformationMatrix(
      glm::scale(glm::dmat4(1.0), glm::dvec3(1.0)) * glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 2.0)));
  left_material.setPatternPtr(std::make_shared<RingPtn>(ringPtn));
  left.setMaterial(left_material);

  Plane p;
  Material material1;
  CheckerPtn checkerPtn(glm::dvec3(1.0), glm::dvec3(0.0));
  checkerPtn.setTransformationMatrix(
      glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, glm::epsilon<double>() * 100.0, 0.0)) * glm::scale(glm::dmat4(1.0), glm::dvec3(1)));
  StripePtn sp1(glm::dvec3(1.0), glm::dvec3(0.0));
  sp1.setTransformationMatrix(glm::rotate(glm::dmat4(1.0), glm::pi<double>() / 4, glm::dvec3(0.0, 1.0, 0.0)));
  StripePtn sp2(glm::dvec3(1.0), glm::dvec3(0.0));
  sp1.setTransformationMatrix(glm::rotate(glm::dmat4(1.0), -glm::pi<double>() / 4, glm::dvec3(0.0, 1.0, 0.0)));
  SolidPtn solidPtn
      (glm::dvec3(1.0), glm::dvec3(1.0, 0.0, 0.0), std::make_shared<StripePtn>(sp1), std::make_shared<StripePtn>(sp2));
  material1.setPatternPtr(std::make_shared<CheckerPtn>(checkerPtn));
  p.setMaterial(material1);

  World world;
  world.setLight(Light(glm::dvec3(1.0), glm::dvec4(-10.0, 10.0, -10.0, 1.0)));
  world.addShape(std::make_shared<Sphere>(left));
  world.addShape(std::make_shared<Sphere>(right));
  world.addShape(std::make_shared<Sphere>(middle));
  world.addShape(std::make_shared<Plane>(p));

  Camera camera(400, 200, glm::pi<double>() / 3);
  camera.setTransformMatrix(view_transform(glm::dvec4(0.0, 1.5, -5.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 0.0)));
  Canvas canvas = camera.render(world);

  canvas.canvas_to_ppm();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;*/

  World w;
  w.setDefault();
  /*Material m;
  m.setAmbient(1.0);
  w.changeShapeMaterial(1,m);
  Intersection i(1, w.getShape(1).get());*/
  Plane p;
  Material m;
  m.setReflective(0.5);
  p.setMaterial(m);
  p.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, -1.0, 0.0)));
  w.addShape(std::make_shared<Plane>(p));
  Ray r(glm::dvec4(0.0, 0.0, -3.0, 1.0), glm::dvec4(0, -sqrt(2)/2.0, sqrt(2)/2.0, 0.0));
  Intersection i(sqrt(2), &p);
  auto comps = i.prepare_computations(r);
  auto color = w.reflected_color(comps);
  //auto color = w.shade_hit(comps);
  std::cout << glm::to_string(color) << "\n";
  std::cout << std::setprecision(10) << color.y << "\n";
 /* w.setLight(Light(glm::dvec3(1.0), glm::dvec4(0.0, 0.0, 0.0, 1.0)));
  Plane lower;
  Material m;
  m.setReflective(1.0);
  lower.setMaterial(m);
  lower.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, -1.0, 0.0)));
  w.addShape(std::make_shared<Plane>(lower));
  Plane upper;
  Material m1;
  m1.setReflective(1.0);
  upper.setMaterial(m1);
  upper.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 1.0, 0.0)));
  w.addShape(std::make_shared<Plane>(upper));
  Ray r(glm::dvec4(0.0, 0.0, 0.0, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  auto color = w.color_at(r);
  std::cout << "Terminate success!" << "\n";*/
  return 0;
}
