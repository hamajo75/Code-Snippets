//helper
std::vector<std::string> split(std::string const& str, char const delim) noexcept {
  std::vector<std::string> res = {};
  std::size_t start {0};
  std::size_t end {0};
  while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
    end = str.find(delim, start);
    res.push_back(str.substr(start, end - start));
  }
  return res;
}
// get("object.value")
nlohmann::json get(nlohmann::json const& root, std::string const& dot_separated_names) {
  std::vector<std::string> const names = split(dot_separated_names, '.');
  nlohmann::json const* leaf = &root;
  for (auto const& name : names) {
    if (leaf->contains(name)) {
      leaf = &leaf->at(name);
    } else {
      // Error handling (e.g. throw error)
      std::cerr << "Name '" << name << "' not found!" << std::endl;
    }
  }
  return *leaf;
}
// set("object.value")
nlohmann::json& set(nlohmann::json& root, std::string const& dot_separated_names) {
  std::vector<std::string> const names = split(dot_separated_names, '.');
  nlohmann::json* leaf = &root;
  for (auto const& name : names) {
    if (leaf->contains(name)) {
      leaf = &leaf->at(name);
    } else {
      // Error handling (e.g. throw error)
      std::cerr << "Name '" << name << "' not found!" << std::endl;
    }
  }
  return *leaf;
}