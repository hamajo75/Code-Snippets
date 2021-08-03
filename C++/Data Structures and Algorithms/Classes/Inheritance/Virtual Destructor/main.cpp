#include <string.h>
#include <iostream>

/******************************************************************************
 * When doing inheritance:
 * C.35: A base class destructor should be either public and virtual, 
 *       or protected and non-virtual, to avoid memory leaks (the 
 *       derived class might have stuff that will not be destroyed).
*******************************************************************************/

class Instrument {
 public:
  Instrument() { std::cout << "Instrument Constructor\n"; }
  virtual ~Instrument() { std::cout << "Instrument Destructor\n"; }
  virtual void makeSound() const { std::cout << "Instrument sound\n"; }
};

class ElectricGuitar : public Instrument {
 public:
  ElectricGuitar() { std::cout << "ElectricGuitar Constructor\n"; }
  ~ElectricGuitar() { std::cout << "ElectricGuitar Destructor\n"; }
  void makeSound() const override { std::cout << "Ratatatata\n"; }
};
//-------------------------------------------------------------------------------
void playInstrument(Instrument* Instrument) { Instrument->makeSound(); }
//-------------------------------------------------------------------------------
void playInstrument(const Instrument& Instrument) { Instrument.makeSound(); }
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  Instrument* instrument = new Instrument{};
  delete instrument;

  // base constructor, then derived constructor is called
  ElectricGuitar* elecGuitar = new ElectricGuitar{};
  // dericed destructor, then base destructor is called
  delete elecGuitar;

  // now we mix things: remove the virtual before the destructor
  Instrument* instrument2 = new ElectricGuitar{};
  // !! only the base constructor is called, if not virtual !!
  delete instrument2;

  std::cout << "\n";
  return 0;
}
