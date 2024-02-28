//
// Created by l4zy9uy on 2/28/24.
//

#include "../include/Intersections.h"

void Intersections::addIntersection(float &distance, std::shared_ptr<Sphere> &sphere) {
    intersections_.emplace_back(distance, sphere);
}

void Intersections::addIntersections(const Intersections &intersections) {
    for(const auto &intersection : intersections.intersections_)
    {
        intersections_.push_back(intersection);
    }
}
