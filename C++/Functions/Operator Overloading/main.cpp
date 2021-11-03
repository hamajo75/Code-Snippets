#include <iostream>

namespace my_namespace {
class Point {
 private:
  double m_x{};
  double m_y{};
  double m_z{};

 public:
  explicit Point(double x = 0.0, double y = 0.0, double z = 0.0)
      : m_x{x}, m_y{y}, m_z{z} {}

  friend std::ostream &operator<<(std::ostream &out, const Point &point);
  friend bool operator==(const Point& lhs, const Point& rhs);
};

std::ostream &operator<<(std::ostream &out, const Point &point) {
  out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z
      << ')';  // actual output done here

  return out;  // return std::ostream so we can chain calls to operator<<
}

bool operator==(const Point& lhs, const Point& rhs) {
  return (lhs.m_x == rhs.m_x &&
          lhs.m_x == rhs.m_x &&
          lhs.m_x == rhs.m_x);
}

}

using my_namespace::Point;
using my_namespace::operator<<;

void StreamPoint() {
  const Point point1{2.0, 3.0, 4.0};
  std::cout << point1 << '\n';
}
void ComparePoint() {
  Point point1{2.0, 3.0, 4.0};
  Point point2{2.0, 3.0, 4.0};

  if (point1 == point2)
    std::cout << "equal points\n";
}
int main() {
  StreamPoint();
  ComparePoint();

  return 0;
}