//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTIONS_H
#define RAYTRACERV2_INTERSECTIONS_H
#include <vector>
#include "Intersection.h"
#include <optional>
class Intersection;
class Sphere;

class Intersections {
private:
    std::vector<Intersection> intersections_;
    bool sorted;
public:
    Intersections(const std::vector<Intersection> &intersections, bool sorted);
    Intersections();
    const std::vector<Intersection> &getIntersections() const;

    void setIntersections(const std::vector<Intersection> &intersections);
    std::optional<Intersection> hit();

public:
    void addIntersection(float &distance, Sphere* sphere);
    void addIntersection(const Intersection &intersection);
    void addIntersections(const Intersections &intersections);
    void sort();
};


#endif //RAYTRACERV2_INTERSECTIONS_H
