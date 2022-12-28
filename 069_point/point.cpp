#include "point.hpp"

#include <cmath>
#include <cstdio>

Point::Point() : x(0), y(0) {
}

void Point::move(double dx, double dy) {
  this->x += dx;
  this->y += dy;
}

double Point::distanceFrom(const Point & p) {
  return std::sqrt(std::pow(this->x - p.x, 2) + std::pow(this->y - p.y, 2));
}
