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
#include <limits>
#include <iomanip>
int main() {

  auto start = std::chrono::high_resolution_clock::now();
  /*glm::dvec4 ray_origin(0.0f, 0.0f, -5.0f, 1.0f);
  double wall_z = 10.0f;
  double wall_size = 7.0f;
  int canvas_pixels = 500;
  double pixel_size = wall_size / canvas_pixels;
  double half = wall_size / 2;
  Canvas canvas(canvas_pixels, canvas_pixels);
  glm::dvec3 color(1.0f, 0.0f, 0.0f);
  Sphere s;
  glm::dmat4 scale = glm::transpose(glm::scale(glm::identity<glm::dmat4>(), glm::dvec3(1.0f, 2.0f, 1.0f)));
  glm::dmat4 rotate = glm::rotate(glm::identity<glm::dmat4>(), glm::pi<double>() / 3, glm::dvec3(0.0f, 1.0f, 0.0f));
  s.setTransform(rotate * scale);
  Material m;
  m.setColor(glm::dvec3(1.0f, 0.2f, 1.0f));
  s.setMaterial(m);
  glm::dvec4 light_position(-10.0, 10.0f, -10.0f, 1.0f);
  glm::dvec3 light_color(1.0f);
  Light light(light_color, light_position);

  for (int i = 0; i < canvas_pixels; i++) {
      auto world_y = half - pixel_size * i;
      for (int j = 0; j < canvas_pixels - 1; j++) {
          auto world_x = -half + pixel_size * j;
          glm::dvec4 position_(world_x, world_y, wall_z, 1.0f);
          Ray r(ray_origin, glm::normalize(position_ - ray_origin));
          auto xs = s.intersect(r);
          auto hit = xs.hit();
          if (hit.has_value()) {
              auto point = position(r, hit->getT());
              auto temp_s = hit->getSpherePtr();
              auto normal = temp_s->normal_at(point);
              auto eye = -r.getDirectionVector();
              color = light.lighting(temp_s->getMaterial(), point, eye, normal);
              canvas.writePixel(j, i, color);
              //std::cout << "i: " << i << " j: " << j << "\n";
          }
      }
  }
  canvas.canvas_to_ppm();*/
  //World world;
  //world.setDefault();
  //world.setLight(Light(glm::dvec3(1.0f), glm::dvec4(0.0f, 0.25f, 0.0f, 1.0f)));
  //Ray r(glm::dvec4(0.0f, 0.0f, 0.75f, 1.0f), glm::dvec4(0.0f, 0.0f, -1.0f, 0.0f));
  /*Sphere sphere = world.getSpheres()[1];
  Intersection i(0.5, &sphere);
  auto comps = i.prepare_computations(r);
  auto color = world.shade_hit(comps);
  std::cout << glm::to_string(color) << "\n";
  std::cout << comps.getT() << "\n";
  std::cout << glm::to_string(comps.getPoint()) << "\n";
  std::cout << glm::to_string(comps.getEyeVector()) << "\n";
  std::cout << glm::to_string(comps.getNormalVector()) << "\n";
  std::cout << std::boolalpha << comps.isInside() << "\n";*/
  /*Material mat;
  mat.setAmbient(1.0f);
  world.changeSphereMaterial(0, mat);
  std::cout << world.getSpheres()[0].getMaterial().getAmbient() << "\n";
  mat.setColor(glm::dvec3(0.23f, 0.34f, 0.45f));
  world.changeSphereMaterial(1, mat);
  auto c = world.color_at(r);
  std::cout << glm::to_string(c) << "\n";*/
  /*glm::dvec4 from(0.0f, 0.0f, 8.0f, 1.0f);
  glm::dvec4 to(0.0f, 0.0f, 0.0f, 1.0f);
  glm::dvec4 up(0.0f, 1.0f, 0.0f, 0.0f);
  auto t = view_transform(from, to, up);
  std::cout << glm::to_string(t) << "\n";*/
  /*Camera camera(201, 101, glm::pi<double>()/2);
  auto mat = glm::rotate(glm::dmat4(1.0f), glm::pi<double>()/4, glm::dvec3(0.0f, 1.0f, 0.0f)) *
          glm::translate(glm::dmat4(1.0f), glm::dvec3(0.0f, -2.0f, 5.0f));
  camera.setTransformMatrix(mat);
  Ray r = camera.ray_for_pixel(100, 50);

  std::cout << glm::to_string(r.getOriginPoint()) << "\n";
  std::cout << glm::to_string(r.getDirectionVector()) << "\n";*/
  /*World world;
  world.setDefault();
  Camera c(11, 11, glm::pi<double>()/2);
  glm::dvec4 from(0.0f, 0.0f, -5.0f, 1.0f);
  glm::dvec4 to(0.0f, 0.0f, 0.0f, 1.0f);
  glm::dvec4 up(0.0f, 1.0f, 0.0f, 0.0f);
  c.setTransformMatrix(view_transform(from, to, up));
  auto image = c.render(world);
  std::cout << glm::to_string(image.pixelAt(5, 5));*/
  Sphere floor;
  floor.setTransform(glm::scale(glm::dmat4(1.0f), glm::dvec3(10.0f, 0.01f, 10.0f)));
  Material material1;
  material1.setColor(glm::dvec3(1.0f, 0.9f, 0.9f));
  material1.setSpecular(0.0f);
  floor.setMaterial(material1);
  Sphere left_wall;
  left_wall.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(0.0f, 0.0f, 5.0f)) *
      glm::rotate(glm::dmat4(1.0f), -glm::pi<double>() / 4, glm::dvec3(0.0f, 1.0f, 0.0f)) *
      glm::rotate(glm::dmat4(1.0f), glm::pi<double>() / 2, glm::dvec3(1.0f, 0.0f, 0.0f)) *
      glm::scale(glm::dmat4(1.0f), glm::dvec3(10.0f, 0.01f, 10.0f)));
  left_wall.setMaterial(material1);

  Sphere right_wall;
  right_wall.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(0.0f, 0.0f, 5.0f)) *
      glm::rotate(glm::dmat4(1.0f), glm::pi<double>() / 4, glm::dvec3(0.0f, 1.0f, 0.0f)) *
      glm::rotate(glm::dmat4(1.0f), glm::pi<double>() / 2, glm::dvec3(1.0f, 0.0f, 0.0f)) *
      glm::scale(glm::dmat4(1.0f), glm::dvec3(10.0f, 0.01f, 10.0f)));
  right_wall.setMaterial(material1);

  Sphere middle;
  middle.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(-0.5f, 1.0f, 0.5f)));
  Material middle_material;
  middle_material.setColor(glm::dvec3(0.1f, 1.0f, 0.5f));
  middle_material.setDiffuse(0.7f);
  middle_material.setSpecular(0.3f);
  middle.setMaterial(middle_material);

  Sphere right;
  right.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(1.5f, 0.5f, -0.5f)) *
      glm::scale(glm::dmat4(1.0f), glm::dvec3(0.5f)));
  Material right_material;
  right_material.setColor(glm::dvec3(0.5f, 1.0f, 0.1f));
  right_material.setDiffuse(0.7f);
  right_material.setSpecular(0.3f);
  right.setMaterial(right_material);

  Sphere left;
  left.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(-1.5f, 0.33f, -0.75f)) *
      glm::scale(glm::dmat4(1.0f), glm::dvec3(0.33f)));
  Material left_material;
  left_material.setColor(glm::dvec3(1.0f, 0.8f, 0.1f));
  left_material.setDiffuse(0.7f);
  left_material.setSpecular(0.3f);
  left.setMaterial(left_material);

  World world;
  world.setLight(Light(glm::dvec3(1.0f), glm::dvec4(-10.0f, 10.0f, -10.0f, 1.0f)));
  world.addSphere(floor);
  world.addSphere(left_wall);
  world.addSphere(right_wall);
  world.addSphere(middle);
  world.addSphere(right);
  world.addSphere(left);
  Camera camera(1920, 1080, glm::pi<double>() / 3);
  camera.setTransformMatrix(view_transform(glm::dvec4(0.0f, 1.5f, -5.0f, 1.0f),
                                           glm::dvec4(0.0f, 1.0f, 0.0f, 1.0f),
                                           glm::dvec4(0.0f, 1.0f, 0.0f, 0.0f)));
  Canvas canvas = camera.render(world);

  canvas.canvas_to_ppm();
  /*glm::dvec4 position(0.0f, 0.0f, 0.0f, 1.0f);
  glm::dvec4 eye(0.0f, 0.0f, -1.0f, 0.0f);
  glm::dvec4 normal(0.0f, 0.0f, -1.0f, 0.0f);
  Light light(glm::dvec3(1.0f), glm::dvec4(0.0f, 0.0f, -10.0f, 1.0f));
  Material m;
  bool isInShadow = true;
  auto result = light.lighting(m, position, eye, normal, isInShadow);
  std::cout << glm::to_string(result) << "\n";*/
 /* World w;
  w.setLight(Light(glm::dvec3(1.0f), glm::dvec4(0.0f, 0.0f, -10.0f, 1.0f)));
  Sphere s1, s2;
  s2.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(0.0f, 0.0f, 10.0f)));
  w.addSphere(s1);
  w.addSphere(s2);
  Ray r(glm::dvec4(0.0f, 0.0f, 5.0f, 1.0f), glm::dvec4(0.0f, 0.0f, 1.0f, 0.0f));
  Intersection i(4, &s2);
  auto comps = i.prepare_computations(r);
  auto c = w.shade_hit(comps);
  std::cout << glm::to_string(c) << "\n";*/
  /*Ray r(glm::dvec4(0.0f, 0.0f, -5.0f, 1.0f), glm::dvec4(0.0f, 0.0f, 1.0f, 0.0f));
  Sphere shape;
  shape.setTransform(glm::translate(glm::dmat4(1.0f), glm::dvec3(0.0f, 0.0f, 1.0f)));
  Intersection i(5, &shape);
  auto comps = i.prepare_computations(r);
  std::cout << std::boolalpha << (comps.getOverPoint().z < glm::epsilon<double>()/2) << "\n";
  std::cout << glm::epsilon<double>() << "\n";
  std::cout << std::boolalpha << (comps.getPoint().z > comps.getOverPoint().z) << "\n";*/
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
  return 0;
}
