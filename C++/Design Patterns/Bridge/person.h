#pragma once

#include<string>

// pimple idiom
// hide implementation behind PersonImpl

class Person {
 public:
  std::string name;

  class PersonImpl;
  PersonImpl* impl;

  Person();
  ~Person();

  void greet();
}