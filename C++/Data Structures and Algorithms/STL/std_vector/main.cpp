#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "vector_utilities.h"

// template <typename T>
// std::vector<T>& operator +=(std::vector<T>& vector1, const std::vector<T>& vector2) {
//   vector1.insert(vector1.end(), vector2.begin(), vector2.end());
//   return vector1;
// }

// std::vector<Base>& operator +=(std::vector<Base>& vector1, const std::vector<Base>& vector2) {
//   vector1.insert(vector1.end(), vector2.begin(), vector2.end());
//   return vector1;
// }

struct Base {
  std::string base = "base";
};
struct DerivedA : public Base {
  std::string derived = "derived";
};
struct DerivedB : public Base {
  std::string derived = "derived";
};


// void LoopThroughDerivedClassVector() {
//   std::vector<DerivedA> vectorA;
//   vectorA.push_back(DerivedA{});
//   vectorA.push_back(DerivedA{});
//   vectorA.push_back(DerivedA{});

//   std::vector<DerivedB> vectorB;
//   vectorB.push_back(DerivedB{});
//   vectorB.push_back(DerivedB{});
//   vectorB.push_back(DerivedB{});

//   vectorA += vectorB;

//   for (Base b : vectorA)
//     std::cout << "b.base " << b.base << "\n";
// }

class Vertex {
 private:
  float x, y, z;

 public:
  Vertex(float x, float y, float z) : x(x), y(y), z(z) {}

  Vertex(const Vertex& other) : x(other.x), y(other.y), z(other.z) {
    std::cout << "Vertex copied\n";
  }
};

template<typename T>
void LoopThroughVector(const std::vector<T>& v) {
  for (auto e : v) std::cout << e << " ";

  // oldschool
  for (std::vector<int>::iterator it = std::begin(v); it != std::end(v); ++it)
    std::cout << *it << "\n";

  // oldschool with index
  for (std::size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << "\n";
  }
}

void ElementaryOperations() {
  std::vector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  std::cout << "\n";

  v.erase(v.begin() + 1);
  v.clear();

  std::vector<Vertex> vertices;
  vertices.push_back({1, 2, 3});  // 6 copies are created here! not optimal
  vertices.push_back({4, 5, 6});
  vertices.push_back({7, 8, 9});

  std::cout << "optimized\n";
  vertices.clear();
  vertices.reserve(3);
  vertices.push_back({1, 2, 3});  // now only 3 copies are made
  vertices.push_back({4, 5, 6});
  vertices.push_back({7, 8, 9});

  std::cout << "more optimized\n";
  vertices.clear();
  vertices.reserve(3);
  vertices.emplace_back(1, 2, 3);  // create directly in the vector
  vertices.emplace_back(4, 5, 6);
  vertices.emplace_back(7, 8, 9);
}

void FindElements() {
  // find, find_if only finds the first element satisfying the criteria

  std::vector<int> v{1, 2, 3, 4};
  auto result3 = std::find_if(begin(v), end(v), [](int i){ return i%2 == 0; });

  struct MyStruct {
    std::string key;
    int value;
  };
  std::vector<MyStruct> data {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}};

  auto result = std::find_if(std::begin(data), std::end(data), [](MyStruct d){ return d.key == "b"; });
  std::cout << "result: " << (*result).key << ", " << (*result).value << "\n";
}

void EraseElements() {
  std::vector<std::string> request_message_ids_{"hello", "bla", "bla"};

  // be carefull: this will only erase the first element !!
  // request_message_ids_.erase(
  //   std::find_if(request_message_ids_.begin(), request_message_ids_.end(),
  //   [](const auto& request_msg_id) {
  //     return request_msg_id == "bla";
  //   }));

  // the right way to do it is this:
  EraseElements(&request_message_ids_,
    [](const auto& request_msg_id) {
    return request_msg_id == "bla";
  });

  for (const auto& id : request_message_ids_)
    std::cout << "id: " << id << "\n";
}

int main() {
  // ElementaryOperations();
  // FindElements();

  // LoopThroughDerivedClassVector();
  EraseElements();

}