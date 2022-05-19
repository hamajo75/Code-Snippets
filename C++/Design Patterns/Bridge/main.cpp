#include <iostream>
#include <string.h>

/* Decouple interface from implementation.
 *
 * Bridge prevents "Cartesian product" complexity explosion:
 * You need a version of a class for Windows, Linux, preemptive or cooperative.
 * Instead of implementing 4 classes
*/

// We have different Shapes - circle, square, etc.
// We also have different Renderers - raster, vector
// we dont want: RasterCircleRenderer, RasterSquareRenderer, VectorCircleRendere, VectorSquareRenderer, ...
//-------------------------------------------------------------------------------
class Renderer {  // this is the Bridge
 public:
  virtual void render_circle(float x, float y, float r) = 0;
};
//-------------------------------------------------------------------------------
class VectorRenderer : public Renderer {
 public:
  void render_circle(float x, float y, float r) override {
    std::cout << "Vector rendering circle\n";
  }
};
//-------------------------------------------------------------------------------
class RasterRenderer : public Renderer {
 public:
  void render_circle(float x, float y, float r) override {
    std::cout << "Raster rendering circle with radius: " << r << "\n";
  }
};
//-------------------------------------------------------------------------------
class Shape {
 protected:
  Renderer& renderer;         // this is the Bridge between concrete Shapes and concrete Renderers
  explicit Shape(Renderer& renderer)
    : renderer{renderer} {}
 public:
  virtual void draw() = 0;
  virtual void resize(float factor) = 0;
};

class Circle : public Shape {
 private:
  float x, y, r;

 public:
  Circle(Renderer& renderer, float x,
  float y, float r)
    : Shape(renderer), x{x}, y{y}, r{r} {}

  void draw() override { renderer.render_circle(x, y, r); }
  void resize(float factor) override {
    r *= factor;
  }
};
//-------------------------------------------------------------------------------
int main() {
  RasterRenderer rr;
  Circle circle(rr, 5, 5, 5);

  circle.draw();
  circle.resize(2);
  circle.draw();

  return 0;
}
