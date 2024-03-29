//
// Created by l4zy9uy on 3/8/24.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "Ray.h"
#include "Shape/Sphere.h"
#include <iomanip>
#include <glm/gtx/string_cast.hpp>
#include "Light.h"
#include "World.h"
#include "Camera.h"
#include "Shape/Plane.h"
#include "Computations.h"
#include "Pattern/StripePtn.h"
#include "Pattern/TestPtn.h"
#include "Shape/Cube.h"
#include "Shape/Cylinder.h"
#include "Shape/Group.h"
#include "Shape/Cone.h"
#include <iomanip>
#include <catch2/catch_approx.hpp>
//const double Epsilon = 0.00001;

TEST_CASE("Compute a_ point from a_ distance", "[Ray]") {
  Ray r(glm::dvec4(2.0, 3.0, 4.0, 1.0), glm::dvec4(1.0, 0.0, 0.0, 0.0));
  REQUIRE(r.at(0) == glm::dvec4(2.0, 3.0, 4.0, 1.0));
  REQUIRE(r.at(1) == glm::dvec4(3.0, 3.0, 4.0, 1.0));
  REQUIRE(r.at(-1) == glm::dvec4(1.0, 3.0, 4.0, 1.0));
  REQUIRE(r.at(2.5) == glm::dvec4(4.5, 3.0, 4.0, 1.0));
}

TEST_CASE("A ray intersects a_ sphere at two points", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].t_ == 4.0);
  REQUIRE(xs.getList()[1].t_ == 6.0);
}

TEST_CASE("A ray intersects a_ sphere at a_ tangent", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 1.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].t_ == 5.0);
  REQUIRE(xs.getList()[1].t_ == 5.0);
}

TEST_CASE("A ray misses a_ sphere", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 2.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().empty());
}

TEST_CASE("A ray originates inside a_ sphere", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, 0.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].t_ == -1.0);
  REQUIRE(xs.getList()[1].t_ == 1.0);
}

TEST_CASE("A sphere is behind a_ ray", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, 5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].t_ == -6.0);
  REQUIRE(xs.getList()[1].t_ == -4.0);
}

TEST_CASE("The hit, when all intersections have positive t", "[hit]") {
  Sphere s;
  Intersection i1(1, &s);
  Intersection i2(2, &s);
  Intersections xs;
  xs.addIntersection(i1);
  xs.addIntersection(i2);
  auto i = xs.hit();
  if(i.has_value()) {
    REQUIRE(i->t_ == i1.t_);
    REQUIRE(i->shape_ptr_ == i1.shape_ptr_);
  }
  else
    REQUIRE(i == std::nullopt);
}

TEST_CASE("The hit, when some intersections have negative t", "[hit]") {
  Sphere s;
  Intersection i1(-1, &s);
  Intersection i2(1, &s);
  Intersections xs;
  xs.addIntersection(i1);
  xs.addIntersection(i2);
  auto i = xs.hit();
  if(i.has_value()) {
    REQUIRE(i->t_ == i2.t_);
    REQUIRE(i->shape_ptr_ == i2.shape_ptr_);
  }
  else
    REQUIRE(i == std::nullopt);
}

TEST_CASE("The hit, when all intersections have negative t", "[hit]") {
  Sphere s;
  Intersection i1(-1, &s);
  Intersection i2(1, &s);
  Intersections xs;
  xs.addIntersection(i1);
  xs.addIntersection(i2);
  auto i = xs.hit();
  if(i.has_value()) {
    REQUIRE(i->t_ == i2.t_);
    REQUIRE(i->shape_ptr_ == i2.shape_ptr_);
  }
  else
    REQUIRE(i == std::nullopt);
}

TEST_CASE("The hit, hit is always the lowest non-negative intersection", "[hit]") {
  Sphere s;
  Intersection i1(5, &s);
  Intersection i2(7, &s);
  Intersection i3(-3, &s);
  Intersection i4(2, &s);
  Intersections xs;
  xs.addIntersection(i1);
  xs.addIntersection(i2);
  xs.addIntersection(i3);
  xs.addIntersection(i4);
  auto i = xs.hit();
  if(i.has_value()) {
    REQUIRE(i->t_ == i4.t_);
    REQUIRE(i->shape_ptr_ == i4.shape_ptr_);
  }
  else
    REQUIRE(i == std::nullopt);
}

TEST_CASE("Translating a_ ray", "[transformation]") {
  Ray r(glm::dvec4(1.0, 2.0, 3.0, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  glm::dmat4 m(glm::translate(glm::dmat4(1.0), glm::dvec3(3.0, 4.0, 5.0)));
  auto r2 = r.transform(m);
  REQUIRE(r2.getOriginPoint() == glm::dvec4(4.0, 6.0, 8.0, 1.0));
  REQUIRE(r2.getDirectionVector() == glm::dvec4(0.0, 1.0, 0.0, 0.0));
}

TEST_CASE("Scaling a_ ray", "[transformation]") {
  Ray r(glm::dvec4(1.0, 2.0, 3.0, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  glm::dmat4 m(glm::scale(glm::dmat4(1.0), glm::dvec3(2.0, 3.0, 4.0)));
  auto r2 = r.transform(m);
  REQUIRE(r2.getOriginPoint() == glm::dvec4(2.0, 6.0, 12.0, 1.0));
  REQUIRE(r2.getDirectionVector() == glm::dvec4(0.0, 3.0, 0.0, 0.0));
}

TEST_CASE("Intersecting a_ scaled sphere with a_ ray", "[intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  s.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(2.0)));
  auto xs = s.intersect(r);
  if(!xs.getList().empty()) {
    REQUIRE(xs.getList().size() == 2);
    REQUIRE(xs.getList()[0].t_ == 3.0);
    REQUIRE(xs.getList()[1].t_ == 7.0);
  }
}

TEST_CASE("Intersecting a_ translated sphere with a_ ray", "[intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  s.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(5.0, 0.0, 0.0)));
  auto xs = s.intersect(r);
  if(!xs.getList().empty()) {
    REQUIRE(xs.getList().size() == 2);
    REQUIRE(xs.getList()[0].t_ == 3.0);
    REQUIRE(xs.getList()[1].t_ == 7.0);
  }
}

TEST_CASE("Computing the normal on a_ translated sphere", "[Compute normal]") {
  Sphere s;
  s.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 1.0, 0.0)));
  auto n = s.normal_at(glm::dvec4(0.0, 1.70711, -0.70711, 1.0), Intersection());
  REQUIRE(n.x == 0.0);
  REQUIRE(fabs(n.y - 0.70711) < 0.00001);
  REQUIRE(fabs(n.z + 0.70711) < 0.00001);
  REQUIRE(n.w == 0.0);
  //REQUIRE(n == glm::dvec4(0.0, 0.70711, -0.70711, 0.0));
}

TEST_CASE("Computing the normal on a_ transformed sphere", "[Compute normal]") {
  Sphere s;
  s.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(1.0, 0.5, 1.0)) *
                  glm::rotate(glm::dmat4(1.0), glm::pi<double>()/5, glm::dvec3(0.0, 0.0, 1.0)));
  auto n = s.normal_at(glm::dvec4(0.0, sqrt(2) / 2, -sqrt(2) / 2, 1.0), Intersection());
  REQUIRE(n.x == 0.0);
  REQUIRE(fabs(n.y - 0.97014) < 0.00001);
  REQUIRE(fabs(n.z + 0.24254) < 0.00001);
  REQUIRE(n.w == 0.0);
  //REQUIRE(n == glm::dvec4(0.0, 0.97014, -0.24254, 0.0));
}

TEST_CASE("Lighting with the eye between the light and the surface", "[lighting]") {
  Material m;
  glm::dvec4 position(0.0, 0.0, 0.0, 1.0);
  glm::dvec4 eyev(0.0, 0.0, -1.0, 0.0);
  glm::dvec4 normalv(0.0, 0.0, -1.0, 0.0);
  Sphere s;
  Light light(glm::dvec3(1.0), glm::dvec4(0.0, 0.0, -10.0, 1.0));
  auto result = light.lighting(m, s, eyev, normalv, false, position);
  REQUIRE(result.x == 1.9);
  REQUIRE(fabs(result.y - 1.9) < Epsilon);
  REQUIRE(fabs(result.z - 1.9) < Epsilon);
}

TEST_CASE("Lighting with the eye between the light and the surface, eye offset 45 degree", "[lighting]") {
  Material m;
  glm::dvec4 position(0.0, 0.0, 0.0, 1.0);
  Sphere s;

  glm::dvec4 eyev(0.0, sqrt(2)/2, -sqrt(2)/2, 0.0);
  glm::dvec4 normalv(0.0, 0.0, -1.0, 0.0);
  Light light(glm::dvec3(1.0), glm::dvec4(0.0, 0.0, -10.0, 1.0));
  auto result = light.lighting(m, s, eyev, normalv, false, position);
  REQUIRE(fabs(result.x - 1.0) < Epsilon);
  REQUIRE(fabs(result.y - 1.0) < Epsilon);
  REQUIRE(fabs(result.z - 1.0) < Epsilon);
}

TEST_CASE("Lighting with eye opposite surface, light offset 45°", "[lighting]") {
  Material m;
  glm::dvec4 position(0.0, 0.0, 0.0, 1.0);
  Sphere s;

  glm::dvec4 eyev(0.0, 0.0, -1.0, 0.0);
  glm::dvec4 normalv(0.0, 0.0, -1.0, 0.0);
  Light light(glm::dvec3(1.0), glm::dvec4(0.0, 10.0, -10.0, 1.0));
  auto result = light.lighting(m, s, eyev, normalv, false, position);
  REQUIRE(fabs(result.x - 0.7364) < Epsilon);
  REQUIRE(fabs(result.y - 0.7364) < Epsilon);
  REQUIRE(fabs(result.z - 0.7364) < Epsilon);
}

TEST_CASE("Lighting with eye in the path of the reflection vector °", "[lighting]") {
  Material m;
  glm::dvec4 position(0.0, 0.0, 0.0, 1.0);
  Sphere s;

  glm::dvec4 eyev(0.0, -sqrt(2)/2, -sqrt(2)/2, 0.0);
  glm::dvec4 normalv(0.0, 0.0, -1.0, 0.0);
  Light light(glm::dvec3(1.0), glm::dvec4(0.0, 10.0, -10.0, 1.0));
  auto result = light.lighting(m, s, eyev, normalv, false, position);
  REQUIRE(fabs(result.x - 1.6364) < Epsilon);
  REQUIRE(fabs(result.y - 1.6364) < Epsilon);
  REQUIRE(fabs(result.z - 1.6364) < Epsilon);
}

TEST_CASE("Lighting with the light behind the surface", "[lighting]") {
  Material m;
  glm::dvec4 position(0.0, 0.0, 0.0, 1.0);
  Sphere s;

  glm::dvec4 eyev(0.0, 0.0, -1.0, 0.0);
  glm::dvec4 normalv(0.0, 0.0, -1.0, 0.0);
  Light light(glm::dvec3(1.0), glm::dvec4(0.0, 0.0, 10.0, 1.0));
  auto result = light.lighting(m, s, eyev, normalv, false, position);
  REQUIRE(fabs(result.x - 0.1) < Epsilon);
  REQUIRE(fabs(result.y - 0.1) < Epsilon);
  REQUIRE(fabs(result.z - 0.1) < Epsilon);
}

TEST_CASE("Intersect a_ world with a_ ray", "[intersect world]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  auto xs = w.intersect_world(r);
  REQUIRE(xs.getList().size() == 4);
  REQUIRE(fabs(xs.getList().at(0).t_ - 4) < Epsilon);
  REQUIRE(fabs(xs.getList().at(1).t_ - 4.5) < Epsilon);
  REQUIRE(fabs(xs.getList().at(2).t_ - 5.5) < Epsilon);
  REQUIRE(fabs(xs.getList().at(3).t_ - 6) < Epsilon);
}

TEST_CASE("Shading an intersection", "[shading]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  auto shape = w.getShape(0);
  Intersection i(4, shape.get());
  auto comps = prepare_computations(i, r);
  auto c = w.shade_hit(comps, 5);
  REQUIRE(fabs(c.x - 0.38066) < Epsilon);
  REQUIRE(fabs(c.y - 0.47583) < Epsilon);
  REQUIRE(fabs(c.z - 0.2855) < Epsilon);
}

TEST_CASE("Shading an intersection from the inside", "[shading]") {
  World w;
  w.setDefault();
  w.setLight(Light(glm::dvec3(1.0), glm::dvec4(0.0, 0.25, 0.0, 1.0)));
  Ray r(glm::dvec4(0.0, 0.0, 0.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  auto shape = w.getShape(1);
  Intersection i(0.5, shape.get());
  auto comps = prepare_computations(i, r);
  auto c = w.shade_hit(comps, 5);
  REQUIRE(fabs(c.x - 0.90498) < Epsilon);
  REQUIRE(fabs(c.y - 0.90498) < Epsilon);
  REQUIRE(fabs(c.z - 0.90498) < Epsilon);
}

TEST_CASE("The color when a_ ray misses", "[color]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  auto c = w.color_at(r, 5);
  REQUIRE(fabs(c.x - 0.0) < Epsilon);
  REQUIRE(fabs(c.y - 0.0) < Epsilon);
  REQUIRE(fabs(c.z - 0.0) < Epsilon);
}

TEST_CASE("The color when a_ ray hits", "[color]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  auto c = w.color_at(r, 5);
  REQUIRE(fabs(c.x - 0.38066) < Epsilon);
  REQUIRE(fabs(c.y - 0.47583) < Epsilon);
  REQUIRE(fabs(c.z - 0.2855) < Epsilon);
}

TEST_CASE("Constructing a_ ray through the center of the canvas", "[camera]") {
  Camera c(201, 101, glm::pi<double>()/2);
  auto r = c.ray_for_pixel(100, 50);
  REQUIRE(fabs(r.getOriginPoint().x - 0.0) < Epsilon);
  REQUIRE(fabs(r.getOriginPoint().y - 0.0) < Epsilon);
  REQUIRE(fabs(r.getOriginPoint().z - 0.0) < Epsilon);
  REQUIRE(fabs(r.getOriginPoint().w - 1.0) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().x - 0.0) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().y - 0.0) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().z + 1.0) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().w - 0.0) < Epsilon);
}

TEST_CASE("Constructing a_ ray through a_ corner of the canvas", "[camera]") {
  Camera c(201, 101, glm::pi<double>()/2);
  auto r = c.ray_for_pixel(0, 0);
  REQUIRE(fabs(r.getOriginPoint().x - 0.0) < Epsilon);
  REQUIRE(fabs(r.getOriginPoint().y - 0.0) < Epsilon);
  REQUIRE(fabs(r.getOriginPoint().z - 0.0) < Epsilon);
  REQUIRE(fabs(r.getOriginPoint().w - 1.0) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().x - 0.66519) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().y - 0.33259) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().z + 0.66851) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().w - 0.0) < Epsilon);
}

TEST_CASE("Constructing a_ ray when the camera is transformed", "[camera]") {
  Camera c(201, 101, glm::pi<double>()/2);
  c.setTransformMatrix(glm::rotate(glm::dmat4(1.0), glm::pi<double>()/4, glm::dvec3(0.0, 1.0, 0.0)) *
                        glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, -2.0, 5.0)));
  auto r = c.ray_for_pixel(100, 50);
  REQUIRE(fabs(r.getOriginPoint().x - 0.0) < Epsilon);
  REQUIRE(fabs(r.getOriginPoint().y - 2.0) < Epsilon);
  REQUIRE(fabs(r.getOriginPoint().z + 5.0) < Epsilon);
  REQUIRE(fabs(r.getOriginPoint().w - 1.0) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().x - sqrt(2)/2) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().y - 0.0) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().z + sqrt(2)/2) < Epsilon);
  REQUIRE(fabs(r.getDirectionVector().w - 0.0) < Epsilon);
}

TEST_CASE("Lighting with the surface in shadow", "[light]") {
  Material m;
  Sphere s;
  glm::dvec4 position(0.0, 0.0, 0.0, 1.0);
  glm::dvec4 eyev(0.0, 0.0, -1.0, 0.0);
  glm::dvec4 normalv(0.0, 0.0, -1.0, 0.0);
  Light light(glm::dvec3(1.0), glm::dvec4(0.0, 0.0, -10.0, 1.0));
  auto result = light.lighting(m, s, eyev, normalv, true, position);
  REQUIRE(fabs(result.x - 0.1) < Epsilon);
  REQUIRE(fabs(result.y - 0.1) < Epsilon);
  REQUIRE(fabs(result.z - 0.1) < Epsilon);
}

TEST_CASE("The shadow when an object is between the point and the light", "[shadow]") {
  World w;
  glm::dvec4 p(10.0, -10.0, 10.0, 1.0);
  w.setDefault();
  REQUIRE(w.isShadowed(p) == true);
}

TEST_CASE("There is no shadow when an object is behind the light", "[shadow]") {
  World w;
  glm::dvec4 p(-20.0, 20.0, -20.0, 1.0);
  w.setDefault();
  REQUIRE(w.isShadowed(p) == false);
}

TEST_CASE("There is no shadow when an object is behind the point", "[shadow]") {
  World w;
  glm::dvec4 p(-2.0, 2.0, -2.0, 1.0);
  w.setDefault();
  REQUIRE(w.isShadowed(p) == false);
}

TEST_CASE("shade_hit() is given an intersection in shadow", "[shadow]") {
  World world;
  world.setLight(Light(glm::dvec3(1.0), glm::dvec4(0.0, 0.0, -10.0, 1.0)));
  Sphere s1, s2;
  world.addShape(std::make_shared<Sphere>(s1));
  s2.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 10.0)));
  world.addShape(std::make_shared<Sphere>(s2));
  Ray r(glm::dvec4(0.0, 0.0, 5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Intersection i(4, &s2);
  auto comps = prepare_computations(i, r);
  auto c = world.shade_hit(comps, 5);
  REQUIRE(fabs(c.x - 0.1) < Epsilon);
  REQUIRE(fabs(c.y - 0.1) < Epsilon);
  REQUIRE(fabs(c.z - 0.1) < Epsilon);
}

TEST_CASE("The hit should offset the point", "[hit]") {
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere shape;
  shape.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 1.0)));
  Intersection i(5, &shape);
  auto comps = prepare_computations(i, r);
  REQUIRE(comps.over_point_.z < -Epsilon/2);
  REQUIRE(comps.point_.z > comps.over_point_.z);
}

TEST_CASE("A pattern with an object transformation", "[pattern]") {
  Sphere shape;
  TestPtn pattern;
  shape.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(2.0)));
  auto c = pattern.pattern_at_shape(shape, glm::dvec4(2.0, 3.0, 4.0, 1.0));
  REQUIRE(fabs(c.x - 1.0) < Epsilon);
  REQUIRE(fabs(c.y - 1.5) < Epsilon);
  REQUIRE(fabs(c.z - 2.0) < Epsilon);
}

TEST_CASE("A pattern with a_ pattern transformation", "[pattern]") {
  Sphere shape;
  TestPtn pattern;
  pattern.setTransformationMatrix(glm::scale(glm::dmat4(1.0), glm::dvec3(2.0)));
  auto c = pattern.pattern_at_shape(shape, glm::dvec4(2.0, 3.0, 4.0, 1.0));
  REQUIRE(fabs(c.x - 1.0) < Epsilon);
  REQUIRE(fabs(c.y - 1.5) < Epsilon);
  REQUIRE(fabs(c.z - 2.0) < Epsilon);
}

TEST_CASE("A pattern with both an object and a_ pattern transformation", "[pattern]") {
  Sphere shape;
  TestPtn pattern;
  shape.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(2.0)));
  pattern.setTransformationMatrix(glm::translate(glm::dmat4(1.0), glm::dvec3(0.5, 1.0, 1.5)));
  auto c = pattern.pattern_at_shape(shape, glm::dvec4(2.5, 3.0, 3.5, 1.0));
  REQUIRE(fabs(c.x - 0.75) < Epsilon);
  REQUIRE(fabs(c.y - 0.5) < Epsilon);
  REQUIRE(fabs(c.z - 0.25) < Epsilon);
}

TEST_CASE("Precomputing the reflection vector", "[reflection]") {
  Plane shape;
  Ray r(glm::dvec4(0.0, 1.0, -1.0, 1.0), glm::dvec4(0.0, -sqrt(2)/2, sqrt(2)/2, 0.0));
  Intersection i(sqrt(2), &shape);
  auto comps = prepare_computations(i, r);
  REQUIRE(fabs(comps.reflect_vector_.x - 0.0) < Epsilon);
  REQUIRE(fabs(comps.reflect_vector_.y - sqrt(2)/2) < Epsilon);
  REQUIRE(fabs(comps.reflect_vector_.z - sqrt(2)/2) < Epsilon);
  REQUIRE(fabs(comps.reflect_vector_.w - 0.0) < Epsilon);
}

TEST_CASE("The reflected color for a_ non-reflective material", "[reflection]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, 0.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Material m;
  m.ambient_ = 1.0;
  w.getShape(1)->setMaterial(m);
  Intersection i(1, w.getShape(1).get());
  auto comps = prepare_computations(i, r);
  auto color = w.reflected_color(comps, 5);
  REQUIRE(fabs(color.x - 0.0) < Epsilon);
  REQUIRE(fabs(color.y - 0.0) < Epsilon);
  REQUIRE(fabs(color.z - 0.0) < Epsilon);
}

TEST_CASE("The reflected color for a_ reflective material", "[reflection]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, -3.0, 1.0), glm::dvec4(0.0, -sqrt(2)/2, sqrt(2)/2, 0.0));
  Plane shape;
  Material m;
  m.reflective_ = 0.5;
  shape.setMaterial(m);
  shape.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, -1.0, 0.0)));
  w.addShape(std::make_shared<Plane>(shape));
  Intersection i(sqrt(2), &shape);
  auto comps = prepare_computations(i, r);
  auto color = w.reflected_color(comps, 3);
  REQUIRE(fabs(color.x - 0.19032) < Epsilon*10);
  REQUIRE(fabs(color.y - 0.2379) < Epsilon*10);
  REQUIRE(fabs(color.z - 0.14274) < Epsilon*10);
}

TEST_CASE("shade_hit() with a_ reflective material", "[reflection]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, -3.0, 1.0), glm::dvec4(0.0, -sqrt(2)/2, sqrt(2)/2, 0.0));
  Plane shape;
  Material m;
  m.reflective_ = 0.5;
  shape.setMaterial(m);
  shape.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, -1.0, 0.0)));
  w.addShape(std::make_shared<Plane>(shape));
  Intersection i(sqrt(2), &shape);
  auto comps = prepare_computations(i, r);
  auto color = w.shade_hit(comps, 5);
  REQUIRE(fabs(color.x - 0.87677) < Epsilon*10);
  REQUIRE(fabs(color.y - 0.92436) < Epsilon*10);
  REQUIRE(fabs(color.z - 0.82918) < Epsilon*10);
}

TEST_CASE("Finding n1 and n2 at various intersections", "[normals]") {
  Sphere A, B, C;
  A.make_glassy();
  B.make_glassy();
  C.make_glassy();
  Material m;

  A.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(2.0)));
  m.refractive_index_ = 1.5;
  A.setMaterial(m);

  B.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, -0.25)));
  m.refractive_index_ = 2.0;
  B.setMaterial(m);

  C.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 0.25)));
  m.refractive_index_ = 2.5;
  C.setMaterial(m);

  Ray r(glm::dvec4(0.0, 0.0, -4.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Intersections xs;
  xs.addIntersection(2, &A);
  xs.addIntersection(2.75, &B);
  xs.addIntersection(3.25, &C);
  xs.addIntersection(4.75, &B);
  xs.addIntersection(5.25, &C);
  xs.addIntersection(6, &A);

  auto i = xs.getList().at(0);
  auto comps = prepare_computations(i, r, xs);
  REQUIRE(fabs(comps.n1_ - 1.0) < Epsilon);
  REQUIRE(fabs(comps.n2_ - 1.5) < Epsilon);

  i = xs.getList().at(1);
  comps = prepare_computations(i, r, xs);
  REQUIRE(fabs(comps.n1_ - 1.5) < Epsilon);
  REQUIRE(fabs(comps.n2_ - 2.0) < Epsilon);

  i = xs.getList().at(2);
  comps = prepare_computations(i, r, xs);
  REQUIRE(fabs(comps.n1_ - 2.0) < Epsilon);
  REQUIRE(fabs(comps.n2_ - 2.5) < Epsilon);

  i = xs.getList().at(3);
  comps = prepare_computations(i, r, xs);
  REQUIRE(fabs(comps.n1_ - 2.5) < Epsilon);
  REQUIRE(fabs(comps.n2_ - 2.5) < Epsilon);

  i = xs.getList().at(4);
  comps = prepare_computations(i, r, xs);
  REQUIRE(fabs(comps.n1_ - 2.5) < Epsilon);
  REQUIRE(fabs(comps.n2_ - 1.5) < Epsilon);

  i = xs.getList().at(5);
  comps = prepare_computations(i, r, xs);
  REQUIRE(fabs(comps.n1_ - 1.5) < Epsilon);
  REQUIRE(fabs(comps.n2_ - 1.0) < Epsilon);
}

TEST_CASE("The under point is offset below the surface", "[hit]") {
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere shape;
  shape.make_glassy();
  shape.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 1.0)));
  Intersection i(5, &shape);
  Intersections xs;
  xs.addIntersection(i);
  auto comps = prepare_computations(i, r, xs);
  REQUIRE(comps.under_point_.z > Epsilon/2);
  REQUIRE(comps.point_.z < comps.under_point_.z);
}

TEST_CASE("The refracted color with an opaque surface", "[refraction]") {
  World w;
  w.setDefault();
  Material m;
  m.transparency_ = 1.0;
  m.refractive_index_ = 1.5;
  w.getShape(0)->setMaterial(m);
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Intersections xs;
  xs.addIntersection(4, w.getShape(0).get());
  xs.addIntersection(6, w.getShape(0).get());
  auto comps = prepare_computations(xs.getList()[0], r, xs);
  auto c = w.refracted_color(comps, 0);

  REQUIRE(fabs(c.x - 0.0) < Epsilon);
  REQUIRE(fabs(c.y - 0.0) < Epsilon);
  REQUIRE(fabs(c.z - 0.0) < Epsilon);
}

TEST_CASE("The refracted color under total internal reflection", "[refraction]") {
  World w;
  w.setDefault();
  Material m;
  m.transparency_ = 1.0;
  m.refractive_index_ = 1.5;
  w.getShape(0)->setMaterial(m);
  Ray r(glm::dvec4(0.0, 0.0, sqrt(2)/2, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  Intersections xs;
  xs.addIntersection(-sqrt(2)/2, w.getShape(0).get());
  xs.addIntersection(sqrt(2)/2, w.getShape(0).get());
  auto comps = prepare_computations(xs.getList()[1], r, xs);
  auto c = w.refracted_color(comps, 5);

  REQUIRE(fabs(c.x - 0.0) < Epsilon);
  REQUIRE(fabs(c.y - 0.0) < Epsilon);
  REQUIRE(fabs(c.z - 0.0) < Epsilon);
}

TEST_CASE("The refracted color with a_ refracted ray", "[refraction]") {
  World w;
  w.setDefault();
  Material m;
  m.ambient_ = 1.0;
  m.pattern_ptr_ = std::make_shared<TestPtn>();
  w.getShape(0)->setMaterial(m);
  Material m2;
  m2.transparency_ = 1.0;
  m2.refractive_index_ = 1.5;
  w.getShape(1)->setMaterial(m2);
  Ray r(glm::dvec4(0.0, 0.0, 0.1, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  Intersections xs;
  xs.addIntersection(-0.9899, w.getShape(0).get());
  xs.addIntersection(-0.4899, w.getShape(1).get());
  xs.addIntersection(0.4899, w.getShape(1).get());
  xs.addIntersection(0.9899, w.getShape(0).get());
  auto comps = prepare_computations(xs.getList()[2], r, xs);
  auto c = w.refracted_color(comps, 5);

  REQUIRE(fabs(c.x - 0.0) < Epsilon);
  REQUIRE(fabs(c.y - 0.99888) < Epsilon);
  REQUIRE(fabs(c.z - 0.04725) < Epsilon*10);
}

TEST_CASE("shade_hit() with a_ transparent material", "[refraction]") {
  World w;
  w.setDefault();
  Plane floor;
  floor.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, -1.0, 0.0)));
  Material m;
  m.transparency_ = 0.5;
  m.refractive_index_ = 1.5;
  floor.setMaterial(m);
  w.addShape(std::make_shared<Plane>(floor));
  Sphere ball;
  Material m2;
  m2.color_ = glm::dvec3(1.0, 0.0, 0.0);
  m2.ambient_ = 0.5;
  ball.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, -3.5, -0.5)));
  ball.setMaterial(m2);
  w.addShape(std::make_shared<Sphere>(ball));
  Ray r(glm::dvec4(0.0, 0.0, -3.0, 1.0), glm::dvec4(0.0, -sqrt(2)/2, sqrt(2)/2, 0.0));
  Intersections xs;
  xs.addIntersection(sqrt(2), w.getShape(2).get());
  auto comps = prepare_computations(xs.getList()[0], r, xs);
  auto c = w.shade_hit(comps, 5);

  REQUIRE(fabs(c.x - 0.93642) < Epsilon);
  REQUIRE(fabs(c.y - 0.68642) < Epsilon);
  REQUIRE(fabs(c.z - 0.68642) < Epsilon*10);
}

TEST_CASE("The Schlick approximation under total internal reflection", "[schlick]") {
  Sphere sphere;
  sphere.make_glassy();
  Ray r(glm::dvec4(0.0, 0.0, sqrt(2)/2, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  Intersections xs;
  xs.addIntersection(-sqrt(2)/2, &sphere);
  xs.addIntersection(sqrt(2)/2, &sphere);
  auto comps = prepare_computations(xs.getList()[1], r, xs);
  auto reflectance = schlick(comps);
  REQUIRE(fabs(reflectance - 1.0) < Epsilon);
}

TEST_CASE("The Schlick approximation with a_ perpendicular viewing angle", "[schlick]") {
  Sphere sphere;
  sphere.make_glassy();
  Ray r(glm::dvec4(0.0, 0.0, 0.0, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  Intersections xs;
  xs.addIntersection(-1, &sphere);
  xs.addIntersection(1, &sphere);
  auto comps = prepare_computations(xs.getList()[1], r, xs);
  auto reflectance = schlick(comps);
  REQUIRE(fabs(reflectance - 0.04) < Epsilon);
}

TEST_CASE("The Schlick approximation with small angle and n2 > n1", "[schlick]") {
  Sphere sphere;
  sphere.make_glassy();
  Ray r(glm::dvec4(0.0, 0.99, -2.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Intersections xs;
  xs.addIntersection(1.8589, &sphere);
  //xs.addIntersection(1, &sphere);
  auto comps = prepare_computations(xs.getList()[0], r, xs);
  auto reflectance = schlick(comps);
  REQUIRE(fabs(reflectance - 0.48873) < Epsilon);
}

TEST_CASE("shade_hit() with a_ reflective, transparent material", "[schlick]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, -3.0, 1.0), glm::dvec4(0.0, -sqrt(2)/2, sqrt(2)/2, 0.0));
  Plane floor;
  floor.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, -1.0, 0.0)));
  Material m;
  m.reflective_ = 0.5;
  m.transparency_ = 0.5;
  m.refractive_index_ = 1.5;
  floor.setMaterial(m);
  w.addShape(std::make_shared<Plane>(floor));
  Sphere ball;
  Material m2;
  m2.color_ = glm::dvec3(1.0, 0.0, 0.0);
  m2.ambient_ = 0.5;
  ball.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, -3.5, -0.5)));
  ball.setMaterial(m2);
  w.addShape(std::make_shared<Sphere>(ball));
  Intersections xs;
  xs.addIntersection(sqrt(2), w.getShape(2).get());
  auto comps = prepare_computations(xs.getList()[0], r, xs);
  auto c = w.shade_hit(comps, 5);
  REQUIRE(fabs(c.r - 0.93391) < Epsilon);
  REQUIRE(fabs(c.g - 0.69643) < Epsilon);
  REQUIRE(fabs(c.b - 0.69243) < Epsilon);
}

TEST_CASE("The normal on the surface of a_ cube", "[cube]") {
  std::vector<glm::dvec4> v;
  Cube c;
  std::vector<glm::dvec3> cv;
  v.emplace_back(1, 0.5, 0.8, 1);
  v.emplace_back(-1, -0.2, 0.9, 1);
  v.emplace_back(-0.4, 1, -0.1, 1);
  v.emplace_back(0.3, -1, -0.7, 1);
  v.emplace_back(-0.6, 0.3, 1, 1);
  v.emplace_back(0.4, 0.4, -1, 1);
  v.emplace_back(1, 1, 1, 1);
  v.emplace_back(-1, -1, -1, 1);
  cv.reserve(v.size());
for (auto &p : v) {
    cv.emplace_back(c.local_normal_at(p, Intersection()));
  }

  REQUIRE(fabs(cv[0].r - 1) < Epsilon);
  REQUIRE(fabs(cv[0].g - 0) < Epsilon);
  REQUIRE(fabs(cv[0].b - 0) < Epsilon);

  REQUIRE(fabs(cv[1].r + 1) < Epsilon);
  REQUIRE(fabs(cv[1].g - 0) < Epsilon);
  REQUIRE(fabs(cv[1].b - 0) < Epsilon);

  REQUIRE(fabs(cv[2].r - 0) < Epsilon);
  REQUIRE(fabs(cv[2].g - 1) < Epsilon);
  REQUIRE(fabs(cv[2].b - 0) < Epsilon);

  REQUIRE(fabs(cv[3].r - 0) < Epsilon);
  REQUIRE(fabs(cv[3].g + 1) < Epsilon);
  REQUIRE(fabs(cv[3].b - 0) < Epsilon);

  REQUIRE(fabs(cv[4].r - 0) < Epsilon);
  REQUIRE(fabs(cv[4].g - 0) < Epsilon);
  REQUIRE(fabs(cv[4].b - 1) < Epsilon);

  REQUIRE(fabs(cv[5].r - 0) < Epsilon);
  REQUIRE(fabs(cv[5].g - 0) < Epsilon);
  REQUIRE(fabs(cv[5].b + 1) < Epsilon);

  REQUIRE(fabs(cv[6].r - 1) < Epsilon);
  REQUIRE(fabs(cv[6].g - 0) < Epsilon);
  REQUIRE(fabs(cv[6].b - 0) < Epsilon);

  REQUIRE(fabs(cv[7].r + 1) < Epsilon);
  REQUIRE(fabs(cv[7].g - 0) < Epsilon);
  REQUIRE(fabs(cv[7].b - 0) < Epsilon);
}

TEST_CASE("A ray misses a_ cube", "[cube]") {
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
    REQUIRE(xs.getList().empty());
  }
}

TEST_CASE("A ray intersects a_ cube", "[cube]") {
  std::vector<Ray> v;
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
    if(r != v.back()) {
      REQUIRE(fabs(xs.getList()[0].t_ - 4) < Epsilon);
      REQUIRE(fabs(xs.getList()[1].t_ - 6) < Epsilon);
    }
    else {
      REQUIRE(fabs(xs.getList()[0].t_ + 1) < Epsilon);
      REQUIRE(fabs(xs.getList()[1].t_ - 1) < Epsilon);
    }
  }
}

TEST_CASE("A ray misses a_ cylinder", "[cylinder]") {
  Cylinder cyl;
  std::vector<Ray> vr;
  vr.emplace_back(glm::dvec4(1, 0, 0, 1), glm::normalize(glm::dvec4(0, 1, 0, 0)));
  vr.emplace_back(glm::dvec4(0, 0, 0, 1), glm::normalize(glm::dvec4(0, 1, 0, 0)));
  vr.emplace_back(glm::dvec4(0, 0, -5, 1), glm::normalize(glm::dvec4(1, 1, 1, 0)));
  for(auto &r : vr) {
    auto xs = cyl.local_intersect(r);
    REQUIRE(xs.getList().empty());
  }
}

TEST_CASE("A ray strikes a_ cylinder", "[cylinder]") {
  Cylinder cyl;
  std::vector<Ray> vr;
  vr.emplace_back(glm::dvec4(1, 0, -5, 1), glm::normalize(glm::dvec4(0, 0, 1, 0)));
  vr.emplace_back(glm::dvec4(0, 0, -5, 1), glm::normalize(glm::dvec4(0, 0, 1, 0)));
  vr.emplace_back(glm::dvec4(0.5, 0, -5, 1), glm::normalize(glm::dvec4(0.1, 1, 1, 0)));
  std::vector<Intersections> its;
  for(auto &r : vr) {
    auto xs = cyl.local_intersect(r);
    its.push_back(xs);
  }
  REQUIRE(fabs(its[0].getList().at(0).t_ - 5) < Epsilon);
  REQUIRE(fabs(its[0].getList().at(1).t_ - 5) < Epsilon);
  REQUIRE(fabs(its[1].getList().at(0).t_ - 4) < Epsilon);
  REQUIRE(fabs(its[1].getList().at(1).t_ - 6) < Epsilon);
  REQUIRE(fabs(its[2].getList().at(0).t_ - 6.80798) < Epsilon);
  REQUIRE(fabs(its[2].getList().at(1).t_ - 7.08872) < Epsilon);
}

TEST_CASE("Normal vector on a_ cylinder", "[cylinder]") {
  Cylinder cyl;
  std::vector<std::pair<glm::dvec4, glm::dvec4>> test_data = {
      {glm::dvec4(1, 0, 0, 1), glm::dvec4(1, 0, 0, 0)},
      {glm::dvec4(0, 5, -1, 1), glm::dvec4(0, 0, -1, 0)},
      {glm::dvec4(0, -2, 1, 1), glm::dvec4(0, 0, 1, 0)},
      {glm::dvec4(-1, 1, 0, 1), glm::dvec4(-1, 0, 0, 0)}
  };

  for (auto &[point, expected_normal] : test_data) {
    glm::dvec4 computed_normal = cyl.local_normal_at(point, Intersection());
    REQUIRE(glm::to_string(computed_normal) == glm::to_string(expected_normal));
  }
}

TEST_CASE("Intersecting a_ constrained cylinder", "[Cylinder]") {
  Cylinder cyl;
  cyl.setMinimum(1);
  cyl.setMaximum(2);
  std::vector<Ray> vr = {
      Ray(glm::dvec4(0, 1.5, 0, 1), glm::normalize(glm::dvec4(0.1, 1, 0, 0))),
      Ray(glm::dvec4(0, 3, -5, 1), glm::normalize(glm::dvec4(0, 0, 1, 0))),
      Ray(glm::dvec4(0, 0, -5, 1), glm::normalize(glm::dvec4(0, 0, 1, 0))),
      Ray(glm::dvec4(0, 2, -5, 1), glm::normalize(glm::dvec4(0, 0, 1, 0))),
      Ray(glm::dvec4(0, 1, -5, 1), glm::normalize(glm::dvec4(0, 0, 1, 0))),
      Ray(glm::dvec4(0, 1.5, -2, 1), glm::normalize(glm::dvec4(0, 0, 1, 0)))
  };
  std::vector<size_t> expected_intersections = {
      0, // For Ray 1
      0, // For Ray 2
      0, // For Ray 3
      0, // For Ray 4
      0, // For Ray 5
      2  // For Ray 6, intersects the cylinder twice
  };

  for (size_t i = 0; i < vr.size(); ++i) {
    auto xs = cyl.local_intersect(vr[i]);
    REQUIRE(xs.getList().size() == expected_intersections[i]);
  }
}

TEST_CASE("Intersecting the caps of a_ closed cylinder", "[Cylinder]") {
  Cylinder cyl;
  cyl.setMinimum(1);
  cyl.setMaximum(2);
  cyl.setClose(true); // Assuming this method is meant to indicate the cylinder has caps
  std::vector<Ray> vr = {
      Ray(glm::dvec4(0, 3, 0, 1), glm::normalize(glm::dvec4(0, -1, 0, 0))),
      Ray(glm::dvec4(0, 3, -2, 1), glm::normalize(glm::dvec4(0, -1, 2, 0))),
      Ray(glm::dvec4(0, 4, -2, 1), glm::normalize(glm::dvec4(0, -1, 1, 0))),
      Ray(glm::dvec4(0, 0, -2, 1), glm::normalize(glm::dvec4(0, 1, 2, 0))),
      Ray(glm::dvec4(0, -1, -2, 1), glm::normalize(glm::dvec4(0, 1, 1, 0)))
  };
  std::vector<size_t> expected_intersections = {
      2, // For Ray 1
      2, // For Ray 2
      2, // For Ray 3
      2, // For Ray 4
      2  // For Ray 5
  };

  for (size_t i = 0; i < vr.size(); ++i) {
    auto xs = cyl.local_intersect(vr[i]);
    REQUIRE(xs.getList().size() == expected_intersections[i]);
  }
}

TEST_CASE("The normal vector on a_ cylinder's end caps", "[Cylinder]") {
  Cylinder cyl;
  cyl.setMinimum(1);
  cyl.setMaximum(2);
  cyl.setClose(true);

  std::vector<glm::dvec4> points = {
      glm::dvec4(0, 1, 0, 1),    // Bottom cap center
      glm::dvec4(0.5, 1, 0, 1),  // Bottom cap edge
      glm::dvec4(0, 1, 0.5, 1),  // Bottom cap edge
      glm::dvec4(0, 2, 0, 1),    // Top cap center
      glm::dvec4(0.5, 2, 0, 1),  // Top cap edge
      glm::dvec4(0, 2, 0.5, 1)   // Top cap edge
  };

  std::vector<glm::dvec4> expected_normals = {
      glm::dvec4(0.000000, -1.000000, 0.000000, 0.000000), // Bottom cap
      glm::dvec4(0.000000, -1.000000, 0.000000, 0.000000), // Bottom cap edge
      glm::dvec4(0.000000, -1.000000, 0.000000, 0.000000), // Bottom cap edge
      glm::dvec4(0.000000, 1.000000, 0.000000, 0.000000),  // Top cap
      glm::dvec4(0.000000, 1.000000, 0.000000, 0.000000),  // Top cap edge
      glm::dvec4(0.000000, 1.000000, 0.000000, 0.000000)   // Top cap edge
  };

  for (size_t i = 0; i < points.size(); ++i) {
    auto n = cyl.local_normal_at(points[i], Intersection());
    REQUIRE(glm::to_string(n) == glm::to_string(expected_normals[i]));
  }
}

TEST_CASE("Intersecting a_ cone with a_ ray", "[Cone]") {
  Cone shape;
  std::vector<Ray> vr = {
      Ray(glm::dvec4(0, 0, -5, 1), glm::normalize(glm::dvec4(0, 0, 1, 0))),
      Ray(glm::dvec4(0, 0, -5, 1), glm::normalize(glm::dvec4(1, 1, 1, 0))),
      Ray(glm::dvec4(1, 1, -5, 1), glm::normalize(glm::dvec4(-0.5, -1, 1, 0)))
  };

  std::vector<std::vector<double>> expected_results = {
      {5.0, 5.0},
      {8.66025, 8.66025},
      {4.55006, 49.4499}
  };

  for (size_t i = 0; i < vr.size(); ++i) {
    auto xs = shape.local_intersect(vr[i]);
    if(xs.getList().empty()) {
      REQUIRE(false); // Fail the test if no intersections are found
    } else {
      // Assuming there are at least two intersections, otherwise adjust as needed
      REQUIRE(xs.getList().at(0).t_ == Catch::Approx(expected_results[i][0]).epsilon(Epsilon));
      REQUIRE(xs.getList().at(1).t_ == Catch::Approx(expected_results[i][1]).epsilon(Epsilon));
    }
  }
}


TEST_CASE("Intersecting a_ cone with a_ ray parallel to one of its halves", "[Cone]") {
  Cone shape;
  std::vector<Ray> vr = {
      Ray(glm::dvec4(0, 0, -1, 1), glm::normalize(glm::dvec4(0, 1, 1, 0)))
  };

  SECTION("Intersection at a_ single point") {
    auto xs = shape.local_intersect(vr[0]);
    REQUIRE_FALSE(xs.getList().empty());
    REQUIRE(xs.getList().at(0).t_ == Catch::Approx(0.353553).epsilon(Epsilon));
  }
}


TEST_CASE("Intersecting a_ cone's end caps", "[Cone]") {
  Cone shape;
  shape.setMinimum(-0.5);
  shape.setMaximum(0.5);
  shape.setClose(true);

  std::vector<Ray> vr = {
      Ray(glm::dvec4(0, 0, -5, 1), glm::normalize(glm::dvec4(0, 1, 0, 0))),
      Ray(glm::dvec4(0, 0, -0.25, 1), glm::normalize(glm::dvec4(0, 1, 1, 0))),
      Ray(glm::dvec4(0, 0, -0.25, 1), glm::normalize(glm::dvec4(0, 1, 0, 0)))
  };

  std::vector<std::size_t> expected_results = {0, 2, 4};

  for (size_t i = 0; i < vr.size(); ++i) {
    auto xs = shape.local_intersect(vr[i]);
    REQUIRE(xs.getList().size() == expected_results[i]);
  }
}

TEST_CASE("Creating a_ new group", "[group]") {
  auto g = std::make_unique<Group>();
  auto s = std::make_unique<Sphere>();
  auto s_ptr = s.get();
  g->addChild(std::move(s));
  REQUIRE(g->getChild()[0].get() == s_ptr);
}

TEST_CASE("Intersecting a_ ray with a_ nonempty group", "[Group]") {
  Group g;
  auto s1 = std::make_unique<Sphere>();
  auto s2 = std::make_unique<Sphere>();
  auto s3 = std::make_unique<Sphere>();
  auto s1_ptr = s1.get();
  auto s2_ptr = s2.get();
  auto s3_ptr = s3.get();

  s2->setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0, 0, -3)));
  s3->setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(5, 0, 0)));

  g.addChild(std::move(s1));
  g.addChild(std::move(s2));
  g.addChild(std::move(s3));

  Ray r(glm::dvec4(0, 0, -5, 1), glm::dvec4(0, 0, 1, 0));
  auto xs = g.local_intersect(r);

  REQUIRE(xs.getList().size() == 4);
  REQUIRE(xs.getList()[0].shape_ptr_ == s2_ptr);
  REQUIRE(xs.getList()[1].shape_ptr_ == s2_ptr);
  REQUIRE(xs.getList()[2].shape_ptr_ == s1_ptr);
  REQUIRE(xs.getList()[3].shape_ptr_ == s1_ptr);
}

TEST_CASE("Intersecting a_ transformed group", "[Group][Sphere][Ray]") {
  Group g;
  auto s1 = std::make_unique<Sphere>();
  // Applying scale transformation to the group
  g.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(2, 2, 2)));
  // Moving the sphere within the group
  s1->setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(5, 0, 0)));
  g.addChild(std::move(s1));

  // Defining a_ ray that will intersect with the transformed sphere within the group
  Ray r(glm::dvec4(10, 0, -10, 1), glm::dvec4(0, 0, 1, 0));
  auto xs = g.intersect(r);

  // Checking the number of intersections
  REQUIRE(xs.getList().size() == 2);
}


TEST_CASE("Converting a_ normal from object to world space", "[Group]") {
  auto g1 = std::make_unique<Group>();
  auto g1_ptr = g1.get();
  g1->setTransform(glm::rotate(glm::dmat4(1), glm::pi<double>()/2, {0, 1, 0}));
  auto g2 = std::make_unique<Group>();
  auto g2_ptr = g2.get();
  g2->setTransform(glm::scale(glm::dmat4(1), {1, 2, 3}));
  g1->addChild(std::move(g2));
  auto s = std::make_unique<Sphere>();
  auto s_ptr = s.get();
  s->setTransform(glm::translate(glm::dmat4(1), {5, 0, 0}));
  g2_ptr->addChild(std::move(s));
  auto n = s_ptr->normal_to_world({sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, 0});

  glm::dvec4 expected_normal = glm::dvec4(0.285714, 0.428571, -0.857143, 0.000000);
  REQUIRE(glm::length(n - expected_normal) < Epsilon);
}

TEST_CASE("Finding the normal on a_ child object", "[group]") {
  auto g1 = std::make_unique<Group>();
  auto g1_ptr = g1.get();
  g1->setTransform(glm::rotate(glm::dmat4(1), glm::pi<double>()/2, {0, 1, 0}));
  auto g2 = std::make_unique<Group>();
  auto g2_ptr = g2.get();
  g2->setTransform(glm::scale(glm::dmat4(1), {1, 2, 3}));
  g1->addChild(std::move(g2));
  auto s = std::make_unique<Sphere>();
  auto s_ptr = s.get();
  s->setTransform(glm::translate(glm::dmat4(1), {5, 0, 0}));
  g2_ptr->addChild(std::move(s));
  auto n = s_ptr->normal_at({1.7321, 1.1547, -5.5774, 1}, Intersection());
  glm::dvec4 expected_res{0.285704, 0.428543, -0.857161, 0.000000};
  REQUIRE(glm::to_string(n) == glm::to_string(expected_res));
}