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

int main() {
    /*glm::vec4 ray_origin(0.0f, 0.0f, -5.0f, 1.0f);
    float wall_z = 10.0f;
    float wall_size = 7.0f;
    int canvas_pixels = 500;
    float pixel_size = wall_size / canvas_pixels;
    float half = wall_size / 2;
    Canvas canvas(canvas_pixels, canvas_pixels);
    glm::vec3 color(1.0f, 0.0f, 0.0f);
    Sphere s;
    glm::mat4 scale = glm::transpose(glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.0f, 2.0f, 1.0f)));
    glm::mat4 rotate = glm::rotate(glm::identity<glm::mat4>(), glm::pi<float>() / 3, glm::vec3(0.0f, 1.0f, 0.0f));
    s.setTransform(rotate * scale);
    Material m;
    m.setColor(glm::vec3(1.0f, 0.2f, 1.0f));
    s.setMaterial(m);
    glm::vec4 light_position(-10.0, 10.0f, -10.0f, 1.0f);
    glm::vec3 light_color(1.0f);
    Light light(light_color, light_position);

    for (int i = 0; i < canvas_pixels; i++) {
        auto world_y = half - pixel_size * i;
        for (int j = 0; j < canvas_pixels - 1; j++) {
            auto world_x = -half + pixel_size * j;
            glm::vec4 position_(world_x, world_y, wall_z, 1.0f);
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
    //world.setLight(Light(glm::vec3(1.0f), glm::vec4(0.0f, 0.25f, 0.0f, 1.0f)));
    //Ray r(glm::vec4(0.0f, 0.0f, 0.75f, 1.0f), glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
    /*Sphere sphere = world.getSpheres()[1];
    Intersection i(0.5, &sphere);
    auto comps = i.prepare_computations(r);
    auto color = world.shade_hit(comps);
    std::cout << glm::to_string(color) << "\n";
    std::cout << comps.getT() << "\n";
    std::cout << glm::to_string(comps.getPoint()) << "\n";
    std::cout << glm::to_string(comps.getEyev()) << "\n";
    std::cout << glm::to_string(comps.getNormalv()) << "\n";
    std::cout << std::boolalpha << comps.isInside() << "\n";*/
    /*Material mat;
    mat.setAmbient(1.0f);
    world.changeSphereMaterial(0, mat);
    std::cout << world.getSpheres()[0].getMaterial().getAmbient() << "\n";
    mat.setColor(glm::vec3(0.23f, 0.34f, 0.45f));
    world.changeSphereMaterial(1, mat);
    auto c = world.color_at(r);
    std::cout << glm::to_string(c) << "\n";*/
    /*glm::vec4 from(0.0f, 0.0f, 8.0f, 1.0f);
    glm::vec4 to(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 up(0.0f, 1.0f, 0.0f, 0.0f);
    auto t = view_transform(from, to, up);
    std::cout << glm::to_string(t) << "\n";*/
    /*Camera camera(201, 101, glm::pi<float>()/2);
    auto mat = glm::rotate(glm::mat4(1.0f), glm::pi<float>()/4, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 5.0f));
    camera.setTransformMatrix(mat);
    Ray r = camera.ray_for_pixel(100, 50);

    std::cout << glm::to_string(r.getOriginPoint()) << "\n";
    std::cout << glm::to_string(r.getDirectionVector()) << "\n";*/
    /*World world;
    world.setDefault();
    Camera c(11, 11, glm::pi<float>()/2);
    glm::vec4 from(0.0f, 0.0f, -5.0f, 1.0f);
    glm::vec4 to(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 up(0.0f, 1.0f, 0.0f, 0.0f);
    c.setTransformMatrix(view_transform(from, to, up));
    auto image = c.render(world);
    std::cout << glm::to_string(image.pixelAt(5, 5));*/
    Sphere floor;
    floor.setTransform(glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 0.01f, 10.0f)));
    Material material1;
    material1.setColor(glm::vec3(1.0f, 0.9f, 0.9f));
    material1.setSpecular(0.0f);
    floor.setMaterial(material1);
    std::cout << glm::to_string(floor.getMaterial().getColor()) << "\n";
    Sphere left_wall;
    left_wall.setTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f)) *
                            glm::rotate(glm::mat4(1.0f), -glm::pi<float>()/4, glm::vec3(0.0f, 1.0f, 0.0f)) *
                            glm::rotate(glm::mat4(1.0f), glm::pi<float>()/2, glm::vec3(1.0f, 0.0f, 0.0f)) *
                            glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 0.01f, 10.0f)));
    left_wall.setMaterial(material1);

    Sphere right_wall;
    right_wall.setTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f)) *
                           glm::rotate(glm::mat4(1.0f), glm::pi<float>()/4, glm::vec3(0.0f, 1.0f, 0.0f)) *
                           glm::rotate(glm::mat4(1.0f), glm::pi<float>()/2, glm::vec3(1.0f, 0.0f, 0.0f)) *
                           glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 0.01f, 10.0f)));
    right_wall.setMaterial(material1);

    Sphere middle;
    middle.setTransform(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 1.0f, 0.5f)));
    Material middle_material;
    middle_material.setColor(glm::vec3(0.1f, 1.0f, 0.5f));
    middle_material.setDiffuse(0.7f);
    middle_material.setSpecular(0.3f);
    middle.setMaterial(middle_material);

    Sphere right;
    right.setTransform(glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.5f, -0.5f)) *
                        glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
    Material right_material;
    right_material.setColor(glm::vec3(0.5f, 1.0f, 0.1f));
    right_material.setDiffuse(0.7f);
    right_material.setSpecular(0.3f);
    right.setMaterial(right_material);

    Sphere left;
    left.setTransform(glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.33f, -0.75f)) *
                        glm::scale(glm::mat4(1.0f), glm::vec3(0.33f)));
    Material left_material;
    left_material.setColor(glm::vec3(1.0f, 0.8f, 0.1f));
    left_material.setDiffuse(0.7f);
    left_material.setSpecular(0.3f);
    left.setMaterial(left_material);

    World world;
    world.setLight(Light(glm::vec3(1.0f), glm::vec4(-10.0f, 10.0f, -10.0f, 1.0f)));
    world.addSphere(floor);
    world.addSphere(left_wall);
    world.addSphere(right_wall);
    world.addSphere(middle);
    world.addSphere(right);
    world.addSphere(left);
    Camera camera(400, 200, glm::pi<float>()/3);
    camera.setTransformMatrix(view_transform(glm::vec4(0.0f, 1.5f, -5.0f, 1.0f),
                                             glm::vec4(0.0f, 1.0f, 0.0f,1.0f),
                                             glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
    Canvas canvas = camera.render(world);
    
    canvas.canvas_to_ppm();
    return 0;
}
