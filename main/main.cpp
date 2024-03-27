#include <iostream>
#include "Canvas.h"
#include <glm/ext.hpp>
#include "ExtVec3.h"
#include <glm/gtx/string_cast.hpp>
#include "Ray.h"
#include <string>
#include "Shape/Sphere.h"
#include "Light.h"
#include "World.h"
#include "Camera.h"
#include <chrono>
#include "Shape/Shape.h"
#include "Shape/Plane.h"
#include "Pattern/StripePtn.h"
#include "Pattern/GradientPtn.h"
#include "Pattern/RingPtn.h"
#include "Pattern/CheckerPtn.h"
#include "Pattern/SolidPtn.h"
#include "Pattern/BlendedPtn.h"
#include <limits>
#include <iomanip>
#include "Pattern/TestPtn.h"
#include "Shape/Cube.h"
#include "Timer.h"
#include "Shape/Cylinder.h"
#include "Shape/Cone.h"
#include "Shape/Group.h"
#include "Shape/Triangle.h"
#include "Parser.h"
#include "Shape/SmoothTriangle.h"


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Timer timer;
  World world;
  world.setLight(Light(glm::dvec3(1.0), glm::dvec4(-10.0, 10.0, -10.0, 1.0)));
  Plane myFloor;
  Material material1;
  material1.ambient_ = 0.05;
  material1.diffuse_ = 0.5;
  material1.reflective_ = 1.0;
  material1.refractive_index_ = 1.33;
  material1.transparency_ = 1.0;
  material1.specular_ = 1.0;
  material1.shininess_ = 300;
  material1.color_ = glm::dvec3(28, 1, 1) / 255.0;
  CheckerPtn checkerPtn(glm::dvec3(126, 192, 89)/255.0, glm::dvec3(191, 153, 89)/255.0);
  checkerPtn.setTransformationMatrix(glm::scale(glm::dmat4(1.0), glm::dvec3(0.5, 1, 0.5)));
  //material1.pattern_ptr_ = std::make_shared<decltype(checkerPtn)>(checkerPtn);
  myFloor.setMaterial(material1);

  Plane myWall;
  Material material2;
  CheckerPtn checkerPtn2(glm::dvec3(226)/255.0, glm::dvec3(1));
  checkerPtn2.setTransformationMatrix(glm::scale(glm::dmat4(1.0), glm::dvec3(0.25)));
  material2.pattern_ptr_ = std::make_shared<decltype(checkerPtn2)>(checkerPtn2);
  myWall.setMaterial(material2);
  auto wallTransform2 = glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 12.0)) *
      glm::rotate(glm::dmat4(1.0), glm::pi<double>()/2, glm::dvec3(1.0, 0.0, 0.0));
  myWall.setTransform(wallTransform2);

  Cube cube;
  Material mat3;
  cube.setMaterial(mat3);
  cube.setTransform(glm::translate(glm::dmat4(1), {0, 2, 0}) *
                    glm::scale(glm::dmat4(1), {0.5, 0.5, 0.5}));

  Cone cone;
  Material mat4;
  cone.setMaterial(mat4);
  cone.setMaximum(1);
  cone.setMinimum(-1);
  cone.setTransform(glm::translate(glm::dmat4(1), {2, 1, 0}) *
      glm::scale(glm::dmat4(1), {0.5, 0.5, 0.5}));
  world.addShape(std::make_shared<Plane>(myFloor));
  world.addShape(std::make_shared<Plane>(myWall));
  world.addShape(std::make_shared<Cube>(cube));
  world.addShape(std::make_shared<Cone>(cone));

  Camera camera(800, 400, glm::pi<double>() / 3);
  auto camTransform = view_transform(glm::dvec4(2.0, 1.5, -5.0, 1.0),
                                     glm::dvec4(0.0, 1.0, 0.0, 1.0),
                                     glm::dvec4(0.0, 1.0, 0.0, 0.0));
  camera.setTransformMatrix(glm::rotate(camTransform, 0.0, {1, 0, 0}));
  camera.render(world).canvas_to_ppm();


  return 0;
}
/*Cone c;
  auto n = c.local_normal_at({0, 0, 0, 1}, Intersection());
  std::cout << glm::to_string(n) << "\n";
  n = c.local_normal_at({1, 1, 1, 1}, Intersection());
  std::cout << glm::to_string(n) << "\n";
  n = c.local_normal_at({-1, -1, 0, 1}, Intersection());
  std::cout << glm::to_string(n) << "\n";*/
/**/
/*Parser p;
  p.test("../../test.txt");
  std::cout << p.num_line_ignored << "\n";
  for(const auto& vt : p.vertices) {
    std::cout << glm::to_string(vt) << "\n";
  }
  std::cout << "\n" << p.defaultGroup.getChild().size() << "\n";*/
/**/
/*glm::dvec4 p1(0, 1, 0, 1);
  glm::dvec4 p2(-1, 0, 0, 1);
  glm::dvec4 p3(1, 0, 0, 1);
  Triangle t(p1, p2, p3);
  Ray r({0, 0.5, -2, 1}, {0, 0, 1, 0});
  auto xs = t.local_intersect(r);
  std::cout << xs.getList().size() << "\n";
  std::cout << xs.getList()[0].t_ << "\n";*/

/*  Parser p = parse_file_obj("../../test.txt");
  std::cout << p.num_line_ignored << "\n";
  for(const auto& vt : p.vertices) {
    std::cout << glm::to_string(vt) << "\n";
  }
  std::cout << "\n" << p.defaultGroup.getChild().size() << "\n";
*/
/*glm::dvec4 p1(0, 1, 0, 1);
  glm::dvec4 p2(-1, 0, 0, 1);
  glm::dvec4 p3(1, 0, 0, 1);
  glm::dvec4 n1(0, 1, 0, 0);
  glm::dvec4 n2(-1, 0, 0, 0);
  glm::dvec4 n3(1, 0, 0, 0);
  SmoothTriangle tri{p1, p2, p3, n1, n2, n3};
  Ray r({-0.2, 0.3, -2, 1}, {0, 0, 1, 0});
  Intersection i{1, &tri, 0.45, 0.25};
  auto n = tri.normal_at({0, 0, 0, 1}, i);
  Intersections xs{};
  xs.addIntersection(i);
  auto comps = prepare_computations(i, r, xs);
  //std::cout << xs.getList()[0].u << " " << xs.getList()[0].v << "\n";
  std::cout << glm::to_string(comps.normal_vector_) << "\n";*/
