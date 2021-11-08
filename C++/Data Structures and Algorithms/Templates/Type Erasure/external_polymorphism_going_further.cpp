/* Putting these together we'll get Type Erasure:
   1. Move ShapeConcept & ShapeModel into a class Shape
   2. Bridge Pattern
   3. Prototype Pattern
*/

class Shape {  // 1. move the External Polymorphism stuff inside here
 private:
  struct ShapeConcept {
    virtual ~ShapeConcept(){
    }
    virtual void serialize() const = 0;     // duck typing, we define what we should
    virtual void draw() const = 0;          // be able to do with a shape thingy
    virtual std::unique_ptr<ShapeConcept> clone() const = 0;  // 3. Prototype pattern, T must be
  };                                                          // copyable ! Needed for the copy and
                                                              // assign operators
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
    virtual std::unique_ptr<ShapeConcept> clone() const override {
      return std::make_unique<ShapeModel>(*this);
    }

    T object;
  };

  friend void serialize(Shape const& shape) {
    shape.pimpl->serialize();                       // virtual fct call -> polymorphism happens herer
  }

  friend void draw(Shape const& shape) {
    shape.pimpl->draw();
  }

  std::unique_ptr<ShapeConcept> pimpl;               // 2. Bridge Pattern

 public:
  template<typename T>
  Shape(T const& x) : pimpl{ new ShapeModel<T>{x}} {}

  // special member functions copy, move, assignment, move assignment
  // for this we need the clone function
  Shape(Shape const& s);
  Shape(Shape&& s);
  Shape& operator=(Shape const& s);
  Shape& operator=(Shape&& s);
};

/* What do we get?
- polymorphism
- free standing functions (not trapped inside a class)
- Single Responsibility Principle
  - functions are alone, classes are alone
*/

// How to use this? (i.e. how to program on abstraction level ShapeConcept?)

void drawAllShapes(std::vector<Shape> const& shapes) {
  for (auto const& shape : shapes)
    draw(shape);
}

using Shapes = std::vector<Shape>;    // this looks nicer now
Shapes shapes;
shapes.emplace_back(Circle{5});
shapes.emplace_back(Square{5});
drawAllShapes(shapes);