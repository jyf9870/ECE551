class Point {
 public:
  Point();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);

 private:
  double x;
  double y;
};
