#include <iostream>
#include <string>

#include <variant>
#include <vector>
#include <tuple>

enum class VideoResolution {kHigh, kLow, kUnknown};

template <typename T, typename ... R>
class EnumerationClass {
  using EnumMap = std::vector<std::tuple<T, R ...>>;
 private:
  EnumMap mapping_;

  std::string GetIndexedRepresentation(T enum_value, int index) {
    for (auto entry : mapping_)
      if (std::get<0>(entry) == enum_value)
        return std::get<1>(entry);

    return "";
  }

 public:
  explicit EnumerationClass(EnumMap mapping) :
  mapping_{mapping} {}

  std::string GetRepresentation(T enum_value, int index) {
    return GetIndexedRepresentation(enum_value, index);
  }
};

//-------------------------------------------------------------------------------
int main() {
  EnumerationClass<VideoResolution, std::string, std::string, std::string> my_enum { {
      {VideoResolution::kHigh, "HIGH", "high", ""},
      {VideoResolution::kLow, "LOW", "low", ""},
      {VideoResolution::kUnknown, "UNKNOWN", "unknown", ""}}
  };

  std::cout << "representation 1" << my_enum.GetRepresentation(VideoResolution::kLow, 1) << "\n";
  std::cout << "representation 2" << my_enum.GetRepresentation(VideoResolution::kLow, 2) << "\n";

  return 0;
}
