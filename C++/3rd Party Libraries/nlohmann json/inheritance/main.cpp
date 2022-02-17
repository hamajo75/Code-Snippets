#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <../nlohmann/json.hpp>

struct A {
  std::string a = "a";
  std::string b = "b";
  std::string c = "c";
};

void from_json(const nlohmann::json &j, A& x) {   // NOLINT
  x.a = j["a"];
  x.b = j["b"];
  x.c = j["c"];
}

void to_json(nlohmann::json &j, const A x) {   // NOLINT
  j["a"] = x.a;
  j["b"] = x.b;
  j["c"] = x.c;
}

struct B : public A {
  std::string d = "d";
  std::string e = "e";
};

template<typename T>
T assign(const A& a) {
  T x;
  x.a = a.a;
  x.b = a.b;
  x.c = a.c;
  return x;
}

void from_json(const nlohmann::json &j, B& x) {   // NOLINT
  x = assign<B>(static_cast<A>(j));
  x.d = j["d"];
  x.e = j["e"];
}

void to_json(nlohmann::json &j, const B x) {  // NOLINT
  j = static_cast<A>(x);
  j["d"] = x.d;
  j["e"] = x.e;
}

//-------------------------------------------------------------------------------
int main() {
  B b_out;
  nlohmann::json j = b_out;

  std::ofstream file;
  file.open("tmp_file.txt");
  file << j.dump(4);
  file.close();

  B b_in;
  std::ifstream file_ifs {"tmp_file.txt"};
  std::ostringstream ss;
  ss << file_ifs.rdbuf();
  j = nlohmann::json::parse(ss.str());
  b_in = j;

  std::cout << b_in.a << "\n";
  std::cout << b_in.b << "\n";
  std::cout << b_in.c << "\n";
  std::cout << b_in.d << "\n";
  std::cout << b_in.e << "\n";

  return 0;
}
