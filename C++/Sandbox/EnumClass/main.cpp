#include <iostream>
#include <string>

#include <variant>
#include <vector>
#include <tuple>

template <typename T>
class EnumerationClass {
  using EnumMap = std::vector<std::tuple<T, std::vector<std::string>>>;
 private:
  EnumMap mapping_;

  std::string GetIndexedRepresentation(T enum_value, int index) {
    for (auto entry : mapping_)
      if (std::get<0>(entry) == enum_value) {
        auto representations = std::get<1>(entry);
        return representations[index];
      }

    return "";
  }

 public:
  explicit EnumerationClass(EnumMap mapping) :
  mapping_{mapping} {}

  std::string GetRepresentation(T enum_value, int index) {
    return GetIndexedRepresentation(enum_value, index);
  }
};

enum class VideoResolution {kHigh, kLow, kUnknown};
//-------------------------------------------------------------------------------
int main() {
  EnumerationClass<VideoResolution> my_enum { {
      {VideoResolution::kHigh, {"HIGH", "high", "tertium"}},
      {VideoResolution::kLow, {"LOW", "low", "tertium", "tetartum"}},
      {VideoResolution::kUnknown, {"UNKNOWN", "unknown", "tertium"}}}
  };

  std::cout << "representation 0: " << my_enum.GetRepresentation(VideoResolution::kLow, 0) << "\n";
  std::cout << "representation 1: " << my_enum.GetRepresentation(VideoResolution::kLow, 1) << "\n";
  std::cout << "representation 2: " << my_enum.GetRepresentation(VideoResolution::kLow, 2) << "\n";

  return 0;
}
