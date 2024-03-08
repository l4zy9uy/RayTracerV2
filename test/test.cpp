//
// Created by l4zy9uy on 3/8/24.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "Ray.h"
#include "Sphere.h"


TEST_CASE("Compute a point from a distance", "[Ray]") {
  Ray r(glm::dvec4(2.0, 3.0, 4.0, 1.0), glm::dvec4(1.0, 0.0, 0.0, 0.0));
  REQUIRE(position(r, 0) == glm::dvec4(2.0, 3.0, 4.0, 1.0));
  REQUIRE(position(r, 1) == glm::dvec4(3.0, 3.0, 4.0, 1.0));
  REQUIRE(position(r, -1) == glm::dvec4(1.0, 3.0, 4.0, 1.0));
  REQUIRE(position(r, 2.5) == glm::dvec4(4.5, 3.0, 4.0, 1.0));
}

TEST_CASE("A ray intersects a sphere at two points", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].getT() == 4.0);
  REQUIRE(xs.getList()[1].getT() == 6.0);
}

TEST_CASE("A ray intersects a sphere at a tangent", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 1.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].getT() == 5.0);
  REQUIRE(xs.getList()[1].getT() == 5.0);
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
  REQUIRE(xs.getList()[0].getT() == -1.0);
  REQUIRE(xs.getList()[1].getT() == 1.0);
}

TEST_CASE("A sphere is behind a ray", "[Intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, 5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  auto xs = s.intersect(r);
  REQUIRE(xs.getList().size() == 2);
  REQUIRE(xs.getList()[0].getT() == -6.0);
  REQUIRE(xs.getList()[1].getT() == -4.0);
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
    REQUIRE(i->getT() == i1.getT());
    REQUIRE(i->getShapePtr() == i1.getShapePtr());
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
    REQUIRE(i->getT() == i2.getT());
    REQUIRE(i->getShapePtr() == i2.getShapePtr());
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
    REQUIRE(i->getT() == i2.getT());
    REQUIRE(i->getShapePtr() == i2.getShapePtr());
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
    REQUIRE(i->getT() == i4.getT());
    REQUIRE(i->getShapePtr() == i4.getShapePtr());
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
    REQUIRE(xs.getList()[0].getT() == 3.0);
    REQUIRE(xs.getList()[1].getT() == 7.0);
  }
}

TEST_CASE("Intersecting a translated sphere with a ray", "[intersect]") {
  Ray r(glm::dvec4(0.0, 0.0, -5.0, 1.0), glm::dvec4(0.0, 0.0, 1.0, 0.0));
  Sphere s;
  s.setTransform(glm::translate(glm::dmat4(1.0), glm::dvec3(5.0, 0.0, 0.0)));
  auto xs = s.intersect(r);
  if(!xs.getList().empty()) {
    REQUIRE(xs.getList().size() == 2);
    REQUIRE(xs.getList()[0].getT() == 3.0);
    REQUIRE(xs.getList()[1].getT() == 7.0);
  }
}