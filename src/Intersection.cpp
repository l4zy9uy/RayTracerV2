//
// Created by l4zy9uy on 2/28/24.
//


#include "Intersection.h"

// Constructor
Intersection::Intersection(double t, Shape* shapePtr) : t_(t), shape_ptr_(shapePtr) {}

// Copy constructor
Intersection::Intersection(const Intersection& other)  = default;

// Copy assignment operator
Intersection& Intersection::operator=(const Intersection& other) {
  if (this != &other) {
    t_ = other.t_;
    shape_ptr_ = other.shape_ptr_;
  }
  return *this;
}

// Move constructor
Intersection::Intersection(Intersection&& other) noexcept : t_(other.t_), shape_ptr_(other.shape_ptr_) {
  other.shape_ptr_ = nullptr;
}

// Move assignment operator
Intersection& Intersection::operator=(Intersection&& other) noexcept {
  if (this != &other) {
    t_ = other.t_;
    shape_ptr_ = other.shape_ptr_;
    other.shape_ptr_ = nullptr;
  }
  return *this;
}

bool Intersection::operator==(const Intersection &rhs) const {
  return fabs(t_ - rhs.t_) < 0.00001 && shape_ptr_ == rhs.shape_ptr_;
}

