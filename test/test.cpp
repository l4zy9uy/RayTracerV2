//
// Created by l4zy9uy on 3/8/24.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "Ray.h"
#include "Shape/Sphere.h"
#include <iomanip>
#include "Light.h"
#include "World.h"
#include "Camera.h"
#include "Shape/Plane.h"
#include "Computations.h"
#include "Pattern/StripePtn.h"
#include "Pattern/TestPtn.h"

const double Epsilon = 0.00001;

TEST_CASE("Compute a point from a distance", "[Ray]") {
  Ray r(glm::dvec4(2.0, 3.0, 4.0, 1.0), glm::dvec4(1.0, 0.0, 0.0, 0.0));
  REQUIRE(r.at(0) == glm::dvec4(2.0, 3.0, 4.0, 1.0));
  REQUIRE(r.at(1) == glm::dvec4(3.0, 3.0, 4.0, 1.0));
  REQUIRE(r.at(-1) == glm::dvec4(1.0, 3.0, 4.0, 1.0));
  REQUIRE(r.at(2.5) == glm::dvec4(4.5, 3.0, 4.0, 1.0));
}

TEST_CASE("A ray intersects a sphere at two points", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].t_ == 4.0);
  REQUIRE(xs.getList()[1].t_ == 6.0);
}

TEST_CASE("A ray intersects a sphere at a tangent", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 1.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].t_ == 5.0);
  REQUIRE(xs.getList()[1].t_ == 5.0);
}

TEST_CASE("A ray misses a sphere", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 2.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().empty());
}

TEST_CASE("A ray originates inside a sphere", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, 0.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].t_ == -1.0);
  REQUIRE(xs.getList()[1].t_ == 1.0);
}

TEST_CASE("A sphere is behind a ray", "[Intersect]") {
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

TEST_CASE("Translating a ray", "[transformation]") {
  Ray r(glm::dvec4(1.0, 2.0, 3.0, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  glm::dmat4 m(glm::translate(glm::dmat4(1.0), glm::dvec3(3.0, 4.0, 5.0)));
  auto r2 = r.transform(m);
  REQUIRE(r2.getOriginPoint() == glm::dvec4(4.0, 6.0, 8.0, 1.0));
  REQUIRE(r2.getDirectionVector() == glm::dvec4(0.0, 1.0, 0.0, 0.0));
}

TEST_CASE("Scaling a ray", "[transformation]") {
  Ray r(glm::dvec4(1.0, 2.0, 3.0, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  glm::dmat4 m(glm::scale(glm::dmat4(1.0), glm::dvec3(2.0, 3.0, 4.0)));
  auto r2 = r.transform(m);
  REQUIRE(r2.getOriginPoint() == glm::dvec4(2.0, 6.0, 12.0, 1.0));
  REQUIRE(r2.getDirectionVector() == glm::dvec4(0.0, 3.0, 0.0, 0.0));
}

TEST_CASE("Intersecting a scaled sphere with a ray", "[intersect]") {
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

TEST_CASE("Intersecting a translated sphere with a ray", "[intersect]") {
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

TEST_CASE("Computing the normal on a translated sphere", "[Compute normal]") {
  Sphere s;
  s.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 1.0, 0.0)));
  auto n = s.normal_at(glm::dvec4(0.0, 1.70711, -0.70711, 1.0));
  REQUIRE(n.x == 0.0);
  REQUIRE(fabs(n.y - 0.70711) < 0.00001);
  REQUIRE(fabs(n.z + 0.70711) < 0.00001);
  REQUIRE(n.w == 0.0);
  //REQUIRE(n == glm::dvec4(0.0, 0.70711, -0.70711, 0.0));
}

TEST_CASE("Computing the normal on a transformed sphere", "[Compute normal]") {
  Sphere s;
  s.setTransform(glm::scale(glm::dmat4(1.0), glm::dvec3(1.0, 0.5, 1.0)) *
                  glm::rotate(glm::dmat4(1.0), glm::pi<double>()/5, glm::dvec3(0.0, 0.0, 1.0)));
  auto n = s.normal_at(glm::dvec4(0.0, sqrt(2)/2, -sqrt(2)/2, 1.0));
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

TEST_CASE("Intersect a world with a ray", "[intersect world]") {
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

TEST_CASE("The color when a ray misses", "[color]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 1.0, 0.0, 0.0));
  auto c = w.color_at(r, 5);
  REQUIRE(fabs(c.x - 0.0) < Epsilon);
  REQUIRE(fabs(c.y - 0.0) < Epsilon);
  REQUIRE(fabs(c.z - 0.0) < Epsilon);
}

TEST_CASE("The color when a ray hits", "[color]") {
  World w;
  w.setDefault();
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  auto c = w.color_at(r, 5);
  REQUIRE(fabs(c.x - 0.38066) < Epsilon);
  REQUIRE(fabs(c.y - 0.47583) < Epsilon);
  REQUIRE(fabs(c.z - 0.2855) < Epsilon);
}

TEST_CASE("Constructing a ray through the center of the canvas", "[camera]") {
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

TEST_CASE("Constructing a ray through a corner of the canvas", "[camera]") {
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

TEST_CASE("Constructing a ray when the camera is transformed", "[camera]") {
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

TEST_CASE("A pattern with a pattern transformation", "[pattern]") {
  Sphere shape;
  TestPtn pattern;
  pattern.setTransformationMatrix(glm::scale(glm::dmat4(1.0), glm::dvec3(2.0)));
  auto c = pattern.pattern_at_shape(shape, glm::dvec4(2.0, 3.0, 4.0, 1.0));
  REQUIRE(fabs(c.x - 1.0) < Epsilon);
  REQUIRE(fabs(c.y - 1.5) < Epsilon);
  REQUIRE(fabs(c.z - 2.0) < Epsilon);
}

TEST_CASE("A pattern with both an object and a pattern transformation", "[pattern]") {
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

TEST_CASE("The reflected color for a non-reflective material", "[reflection]") {
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

TEST_CASE("The reflected color for a reflective material", "[reflection]") {
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

TEST_CASE("shade_hit() with a reflective material", "[reflection]") {
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

TEST_CASE("The refracted color with a refracted ray", "[refraction]") {
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

TEST_CASE("shade_hit() with a transparent material", "[refraction]") {
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

TEST_CASE("The Schlick approximation with a perpendicular viewing angle", "[schlick]") {
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

TEST_CASE("shade_hit() with a reflective, transparent material", "[schlick]") {
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