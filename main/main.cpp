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

int main() {
  /*std::ios_base::sync_with_stdio(false);
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

  world.addShape(std::make_shared<Plane>(myFloor));
  world.addShape(std::make_shared<Plane>(myWall));

  Camera camera(1920, 1080, glm::pi<double>() / 3);
  camera.setTransformMatrix(view_transform(glm::dvec4(0.0, 1.5, -5.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 1.0),
                                           glm::dvec4(0.0, 1.0, 0.0, 0.0)));
  camera.render(world).canvas_to_ppm();*/

  Group g1;// = std::make_shared<Group>();
  g1.setTransform(glm::rotate(glm::dmat4(1), glm::pi<double>()/2, {0, 1, 0}));
  Group g2;// = std::make_shared<Group>();
  g2.setTransform(glm::scale(glm::dmat4(1), {1, 2, 3}));
  g1.addChild(&g2);
  Sphere s;// = std::make_shared<Sphere>();
  s.setTransform(glm::translate(glm::dmat4(1), {5, 0, 0}));
  g2.addChild(&s);
  auto n = s.normal_at({1.7321, 1.1547, -5.5774, 1});
  std::cout << glm::to_string(n) << "\n";
  return 0;
}
/*auto g = std::make_shared<Group>();
  auto s = std::make_shared<Sphere>();
  g->addChild(s);
  std::cout << "g: " << g << "\n";
  std::cout << "s: " << s << "\n";
  std::cout << "first child: " << g->getChildVector()[0] << "\n";
  std::cout << "s parent: " << s->getParentPtr() << "\n";*/

/*Group g;
  auto s1 = std::make_shared<Sphere>();
  auto s2 = std::make_shared<Sphere>();
  auto s3 = std::make_shared<Sphere>();
  s2->setTransform(glm::translate(glm::dmat4(1.0), {0, 0, -3}));
  s3->setTransform(glm::translate(glm::dmat4(1.0), {5, 0, 0}));
  g.addChild(s1);
  g.addChild(s2);
  g.addChild(s3);
  Ray r({0, 0, -5, 1}, {0, 0, 1, 0});
  auto xs = g.local_intersect(r);
  std::cout << xs.getList().size() << "\n";
  std::cout << "s1: " << s1 << "\n";
  std::cout << "s2: " << s2 << "\n";
  std::cout << "xs[0]: " << xs.getList()[0].shape_ptr_ << "\n";
  std::cout << "xs[1]: " << xs.getList()[1].shape_ptr_ << "\n";
  std::cout << "xs[2]: " << xs.getList()[2].shape_ptr_ << "\n";
  std::cout << "xs[3]: " << xs.getList()[3].shape_ptr_ << "\n";*/

/*Group g;
  auto s1 = std::make_shared<Sphere>();
  g.setTransform(glm::scale(glm::dmat4(1), {2, 2, 2}));
  s1->setTransform(glm::translate(glm::dmat4(1), {5, 0, 0}));
  g.addChild(s1);
  Ray r({10, 0, -10, 1}, {0, 0, 1, 0});
  auto xs = g.intersect(r);
  std::cout << xs.getList().size() << "\n";*/

/*Group g1;// = std::make_shared<Group>();
  g1.setTransform(glm::rotate(glm::dmat4(1), glm::pi<double>()/2, {0, 1, 0}));
  Group g2;// = std::make_shared<Group>();
  g2.setTransform(glm::scale(glm::dmat4(1), {1, 2, 3}));
  g1.addChild(&g2);
  Sphere s;// = std::make_shared<Sphere>();
  s.setTransform(glm::translate(glm::dmat4(1), {5, 0, 0}));
  g2.addChild(&s);
  auto n = s.normal_to_world({sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, 0});
  std::cout << glm::to_string(n) << "\n";*/