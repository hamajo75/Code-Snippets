# Object-Oriented Programming

## Constructing and destructing objects

### Order of construction and destruction with inheritance
 - Inheritance:
   - construction: from base to derived
   - destruction: from derived to base
 - Composition:
   - construction: from parts to whole
   - destruction: from whole to parts
 - Stack:
   - Destruction happens in reversed order of construction.

 Notes:
 - Destructors are always called in reverse order of the constructors.

### Smart pointers

### The rule of zero, three, and five

A. The Rule of Zero:
   - If a class doesn't manage any resources directly, it shouldn't declare any special member functions.
   - Rely on the compiler-generated special member functions.

B. The Rule of Three:
   - If a class manages a resource and needs to define any of the following, it should probably define all three:

     1) Destructor
     2) Copy constructor
     3) Copy assignment operator

C. The Rule of Five:
   - In C++11 and later, if you define any of the following, you should define all five:

     1) Destructor
     2) Copy constructor
     3) Copy assignment operator
     4) Move constructor
     5) Move assignment operator

These rules help ensure proper resource management and prevent issues like memory leaks or undefined behavior when objects are copied, moved, or destroyed.

## Inheritance
### Access Types

When deriving a class from a base class, the access specifier used determines how the members of the base class are accessible in the derived class:

- **Public**: Interface stays the same.
  - Public members of the base class remain public in the derived class.
  - Protected members of the base class remain protected in the derived class.
  - Private members of the base class are not accessible directly from the derived class.

- **Protected**: public becomes protected.
  - Public members of the base class become protected in the derived class.
  - Protected members of the base class remain protected in the derived class.
  - Private members of the base class are not accessible directly from the derived class.

- **Private**: everything becomes private.
  - Public members of the base class become private in the derived class.
  - Protected members of the base class become private in the derived class.
  - Private members of the base class are not accessible directly from the derived class.

These access types control the visibility and accessibility of the base class members in the derived class, influencing how the derived class can interact with the base class.
