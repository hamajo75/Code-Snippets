class Circle {
 private:
  int radius_;
 public:
  explicit Circle(double radius) :
   radius_{radius} {}
};

class Square {
 private:
  int side_;
 public:
  explicit Square(double side)  :
   side_{side} {}
};

/* Circles and Squares are independent types:
- no base class
- no functions handling shapes
*/

struct ShapeConcept {
  virtual ~ShapeConcept(){
  }
  virtual void serialize() const = 0;     // duck typing, we define what we should
  virtual void draw() const = 0;          // be able to do with a shape thingy
};

template<typename T>
struct ShapeModel : ShapeConcept {
  void serialize() const override {
    serialize(object);
  }
  void draw() const override {
    draw(object);
  }

  ShapeModel(T const& value) {

  }
  T object;
};

/* What do we get?
- polymorphism
- free standing functions (not trapped inside a class)
- Single Responsibility Principle
  - functions are alone, classes are alone
*/

// How to use this? (i.e. how to program on abstraction level ShapeConcept?)

void drawAllShapes(std::vector<std::unique_ptr<ShapeConcept>> const& shapes) {
  for (auto const& shape : shapes)
    shapes->draw();
}

Circle circle;
ShapeModel shape{Circle};
std::vector<std::unique_ptr<ShapeConcept>> shapes;
shapes.push_back(shape);

using Shapes = std::vector<std::unique_ptr<ShapeConcept>>;
Shapes shapes;
shapes.emplace_back(std::make_unique<ShapeModel<Circle>{5};
shapes.emplace_back(std::make_unique<ShapeModel<Square>{5};
drawAllShapes(shapes);