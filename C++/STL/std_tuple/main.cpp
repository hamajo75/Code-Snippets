#include <iostream>
#include <string>

#include <tuple>
#include <vector>

enum class VideoResolution {kHigh, kLow, kUnknown};

//-------------------------------------------------------------------------------
int main() {

  std::tuple<VideoResolution, std::string, std::string> my_tuple = {VideoResolution::kHigh, "HIGH", "high"};

  std::cout << "get Value 1: " << std::get<1>(my_tuple) << "\n";
  std::cout << "get Value 2: " << std::get<2>(my_tuple) << "\n";

  std::vector<std::tuple<VideoResolution, std::string, std::string>> map {
      {VideoResolution::kHigh, "HIGH", "high"},
      {VideoResolution::kLow, "LOW", "low"},
      {VideoResolution::kUnknown, "UNKNOWN", "unknown"}
  };

  return 0;
}
