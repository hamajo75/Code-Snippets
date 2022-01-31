#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <variant>

struct Circle {
  void draw() const { std::cout << "drawing Circle" << std::endl; }
};

struct Rectangle {
  void draw() const { std::cout << "drawing Rectangle" << std::endl; }
};

struct Group;
using GraphicObject = std::variant<Circle, Rectangle, Group>;
using GraphicObjects = std::vector<GraphicObject>;

struct Group {
  std::string name;
  explicit Group(const std::string &name) : name{name} {}

  void draw() const {
    std::cout << "Group " << name.c_str() << " contains:" << std::endl;
    for (const auto& object : objects) {
      std::visit([](auto&& object){ object.draw(); }, object);
    }
  }

  GraphicObjects objects;
};

//-------------------------------------------------------------------------------
int main() {
  Circle c;
  Rectangle r;
  c.draw();
  r.draw();

  GraphicObjects graphic_objects;
  graphic_objects.push_back(c);
  graphic_objects.push_back(r);

  Group root {"root"};
  root.objects.push_back(c);

  Group subgroup {"subgroup"};
  subgroup.objects.push_back(r);

  root.objects.push_back(subgroup);

  root.draw();

  return 0;
}
