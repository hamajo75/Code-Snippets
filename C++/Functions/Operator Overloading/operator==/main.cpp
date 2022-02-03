#include <iostream>
#include <string>


struct VisibleDevice {
  std::string pairing_status;
};

bool operator==(const VisibleDevice& lhs, const VisibleDevice& rhs) {return false;}

struct GasDetector : public VisibleDevice {
  std::string gas_detector_status;
};

//-------------------------------------------------------------------------------
int main() {
  GasDetector a;
  GasDetector b;

  if (a == b)
    std::cout << "comparison true\n";
  else
    std::cout << "comparison false\n";

  return 0;
}
