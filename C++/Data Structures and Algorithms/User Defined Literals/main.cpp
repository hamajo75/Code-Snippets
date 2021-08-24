// implement operator""
/* Example:
MyDistance operator"" _km(long double d) { return MyDistance(1000 * d); }
MyDistance d = 1_km;
*/

#include <iostream>
#include <ostream>

class MyDistance {
 public:
  MyDistance(double i) : m(i) {}

  friend MyDistance operator+(const MyDistance& a, const MyDistance& b) {
    return MyDistance(a.m + b.m);
  }
  friend MyDistance operator-(const MyDistance& a, const MyDistance& b) {
    return MyDistance(a.m - b.m);
  }

  friend std::ostream& operator<<(std::ostream& out, const MyDistance& myDist) {
    out << myDist.m << " m";
    return out;
  }

 private:
  double m;
};

MyDistance operator"" _km(long double d) { return MyDistance(1000 * d); }
MyDistance operator"" _m(long double m) { return MyDistance(m); }
MyDistance operator"" _dm(long double d) { return MyDistance(d / 10); }
MyDistance operator"" _cm(long double c) { return MyDistance(c / 100); }
MyDistance operator"" _ft(long double c) { return MyDistance(c * 0.3048); }
MyDistance operator"" _ml(long double c) { return MyDistance(c * 1609.344); }

int main() {
  std::cout << std::endl;

  std::cout << "1.0_km: " << 1.0_km << std::endl;
  std::cout << "1.0_m: " << 1.0_m << std::endl;
  std::cout << "1.0_dm: " << 1.0_dm << std::endl;
  std::cout << "1.0_cm: " << 1.0_cm << std::endl;
  std::cout << "1.0_ft: " << 1.0_ft << std::endl;
  std::cout << "1.0_ml: " << 1.0_ml << std::endl;

  std::cout << std::endl;
  std::cout << "1.0_km + 2.0_dm +  3.0_dm - 4.0_cm: "
            << 1.0_km + 2.0_dm + 3.0_dm - 4.0_cm << std::endl;
  std::cout << std::endl;

}