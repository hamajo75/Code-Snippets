//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Coordinate data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include <optional>

namespace nlohmann {
template <typename T> struct adl_serializer<std::optional<T>> {
  static void to_json(json &j, const std::optional<T> &opt) {
    if (!opt)
      j = nullptr;
    else
      j = *opt;
  }

  static std::optional<T> from_json(const json &j) {
    if (j.is_null())
      return std::nullopt;
    else
      return j.get<T>();
  }
};
}

namespace wplc {
using nlohmann::json;

/**
 * A geographical coordinate
 */
struct Coordinate {
  std::optional<std::string> latitude;
};
}

namespace nlohmann {
void from_json(const json &j, std::string &x) {

}
void to_json(json &j, const std::string &x) {

}


inline void from_json(const json &j, wplc::Coordinate &x) {
  x.latitude = j.get<std::optional<std::string>>("latitude");
}

inline void to_json(json &j, const wplc::Coordinate &x) {
  j = json::object();
  j["latitude"] = x.latitude;
}
}  // namespace nlohmann
