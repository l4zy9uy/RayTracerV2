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

int main() {
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

  world.addShape(std::make_shared<Plane>(myFloor));
  world.addShape(std::make_shared<Plane>(myWall));

  Camera camera(10, 5, glm::pi<double>() / 3);
  camera.setTransformMatrix(view_transform(glm::dvec4(0.0, 1.5, -5.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 0.0)));
  camera.render(world).canvas_to_ppm();
  return 0;
}
/*std::vector<Ray> v;
Cube c;
v.emplace_back(glm::dvec4(5, 0.5, 0, 1), glm::dvec4(-1, 0, 0, 0));
v.emplace_back(glm::dvec4(-5, 0.5, 0, 1), glm::dvec4(1, 0, 0, 0));
v.emplace_back(glm::dvec4(0.5, 5, 0, 1), glm::dvec4(0, -1, 0, 0));
v.emplace_back(glm::dvec4(0.5, -5, 0, 1), glm::dvec4(0, 1, 0, 0));
v.emplace_back(glm::dvec4(0.5, 0, 5, 1), glm::dvec4(0, 0, -1, 0));
v.emplace_back(glm::dvec4(0.5, 0, -5, 1), glm::dvec4(0, 0, 1, 0));
v.emplace_back(glm::dvec4(0, 0.5, 0, 1), glm::dvec4(0, 0, 1, 0));
for(auto &r : v) {
auto xs = c.local_intersect(r);
std::cout << xs.getList()[0].t_ << " " << xs.getList()[1].t_ << "\n";
}*/

/*
std::vector<Ray> v;
Cube c;
v.emplace_back(glm::dvec4(-2, 0.0, 0, 1), glm::dvec4(0.2673, 0.5345, 0.8018, 0));
v.emplace_back(glm::dvec4(0, -2, 0, 1), glm::dvec4(0.8018, 0.2673, 0.5345, 0));
v.emplace_back(glm::dvec4(0, 0, -2, 1), glm::dvec4(0.5345, 0.8018, 0.2673, 0));
v.emplace_back(glm::dvec4(2, 0, 2, 1), glm::dvec4(0, 0, -1, 0));
v.emplace_back(glm::dvec4(0, 2, 2, 1), glm::dvec4(0, -1, 0, 0));
v.emplace_back(glm::dvec4(2, 2, 0, 1), glm::dvec4(-1, 0, 0, 0));
for (auto &r : v) {
auto xs = c.local_intersect(r);
if (xs.getList().empty())
std::cout << "Missed\n";
else
std::cout << "not missed and " << xs.getList()[0].t_ << " " << xs.getList()[1].t_ << "\n";
}*/

/*
std::vector<glm::dvec4> v;
Cube c;
v.emplace_back(1, 0.5, 0.8, 1);
v.emplace_back(-1, -0.2, 0.9, 1);
v.emplace_back(-0.4, 1, -0.1, 1);
v.emplace_back(0.3, -1, -0.7, 1);
v.emplace_back(-0.6, 0.3, 1, 1);
v.emplace_back(0.4, 0.4, -1, 1);
v.emplace_back(1, 1, 1, 1);
v.emplace_back(-1, -1, -1, 1);
for (auto &p : v) {
auto xs = c.local_normal_at(p);
std::cout << glm::to_string(xs) << "\n";
}*/
