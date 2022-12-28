#include "circle.hpp"

#include <math.h>

#include <algorithm>
#include <cmath>
#include <cstdio>

Circle::Circle(Point center, double r) : r(r), center(center) {
}
void Circle::move(double dx, double dy) {
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = this->center.distanceFrom(otherCircle.center);
  double r1 = std::min(this->r, otherCircle.r);  //small one
  double r2 = std::max(this->r, otherCircle.r);  // bigger one
  if (distance >= r1 + r2)
    return 0;

  if (distance <= r2 - r1)
    return M_PI * std::pow(r1, 2);

  double ang1 = acos((r1 * r1 + distance * distance - r2 * r2) / (2 * r1 * distance));
  double ang2 = acos((r2 * r2 + distance * distance - r1 * r1) / (2 * r2 * distance));
  return ang1 * r1 * r1 + ang2 * r2 * r2 - r1 * distance * sin(ang1);
}
