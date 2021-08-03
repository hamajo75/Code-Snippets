#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <boost/lexical_cast.hpp>
//-------------------------------------------------------------------------------
enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product {
  std::string name;
  Color color;
  Size size;
};

struct ProductFilter {
  std::vector<Product*> by_color(std::vector<Product*> items, Color color) {
    std::vector<Product*> result;
    for (auto& i : items) {
      if (i->color == color) {
        result.push_back(i);
      }
    }
    return result;
  }
  // std::vector<Product*> by_size(std::vector<Product*> items, Color color) {     // don't do this !
  //   std::vector<Product*> result;                                               // you have to change ProductFilter
  //   for (auto& i : items) {
  //     if (i->size == size) {
  //       result.push_back(i);
  //     }
  //   }
  //   return result;
  // }
};
//-------------------------------------------------------------------------------
// Specification Pattern
template <typename T> struct AndSpecification;
template <typename T> struct Specification {
  virtual bool is_satisfied(T* item) = 0;

  AndSpecification<T> operator&&(Specification<T>&& other) {
    return AndSpecification<T>(*this, other);
  }
};
template <typename T> struct Filter {
  virtual std::vector<T*> filter(std::vector<T*> items,
                                  Specification<T>& spec) = 0;
};
struct BetterFilter : Filter<Product> {
  std::vector<Product* > filter(std::vector<Product *> items,
                                Specification<Product> &spec) override {
    std::vector<Product*> result;
    for (auto& item : items) {
      if (spec.is_satisfied(item)) {
        result.push_back(item);
      }
    }
    return result;
  }
};
struct ColorSpecification : Specification<Product> {
  Color color;
  explicit ColorSpecification(Color color) : color(color) {}

  bool is_satisfied(Product* item) override {
    return item->color == color;
  }
};

// you can now easily add another Spcification for size:
struct SizeSpecification : Specification<Product> {
  Size size;
  explicit SizeSpecification(Size size) : size(size) {}

  bool is_satisfied(Product* item) override {
    return item->size == size;
  }
};
// how to combine two spefications?
template <typename T> struct AndSpecification : Specification<T> {
  Specification<T>& first;
  Specification<T>& second;

  AndSpecification(Specification<T>& first, 
                   Specification<T>& second) :
    first(first), second(second) {}

  bool is_satisfied(Product* item) override {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

//-------------------------------------------------------------------------------
int main() {
  Product apple{ "Apple", Color::green, Size::small };
  Product tree{ "Tree", Color::green, Size::large };
  Product house{ "House", Color::blue, Size::large };

  std::vector<Product*> items {&apple, &tree, &house};

  ProductFilter filter;
  auto results = filter.by_color(items, Color::green);

  for (auto& item : results)
    std::cout << item->name << " is green\n";

  BetterFilter bf;
  ColorSpecification green{Color::green};

  for (auto& item : bf.filter(items, green))
    std::cout << item->name << " is green\n";

  SizeSpecification large{Size::large};
  AndSpecification<Product> green_and_large{green, large};

  // shorter
  auto spec = ColorSpecification(Color::green) && SizeSpecification(Size::large);

  for (auto& item : bf.filter(items, spec))
    std::cout << item->name << " is green and large\n";

  return 0;
}
