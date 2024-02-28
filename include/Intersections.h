//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTIONS_H
#define RAYTRACERV2_INTERSECTIONS_H
#include <vector>
#include "Intersection.h"
#include "Sphere.h"
class Intersections {
private:
    std::vector<Intersection> intersections_;
public:
    void addIntersection(float &distance, std::shared_ptr<Sphere> &sphere);
    void addIntersections(const Intersections &intersections);
};


#endif //RAYTRACERV2_INTERSECTIONS_H
