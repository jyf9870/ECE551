#include "point.hpp"

class Circle {
 private:
  const double r;
  Point center;

 public:
  Circle(Point center, double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
