#ifndef STRING_H

#include <iostream>
#include <cstring>

class MyString {
public:
  // Default constructor
  MyString() : m_data(nullptr), m_size(0) {
    std::cout << "Default constructor\n";
  }

  // Constructor with char array argument
  MyString(const char* str) : m_data(nullptr), m_size(0) {
    std::cout << "Constructor with char array argument\n";
    m_size = strlen(str);
    m_data = new char[m_size + 1];
    strcpy(m_data, str);
  }

  // Copy constructor
  MyString(const MyString& other) : m_data(nullptr), m_size(0) {
    std::cout << "Copy constructor\n";
    m_size = other.m_size;
    m_data = new char[m_size + 1];
    strcpy(m_data, other.m_data);
  }

  // Move constructor
  MyString(MyString&& other) : m_data(nullptr), m_size(0) {
    std::cout << "Move constructor\n";
    m_size = other.m_size;
    m_data = other.m_data;
    other.m_size = 0;
    other.m_data = nullptr;
  }

  // Copy assignment operator
  MyString& operator=(const MyString& other) {
    std::cout << "Copy assignment operator\n";
    if (this != &other) {
      delete[] m_data;
      m_size = other.m_size;
      m_data = new char[m_size + 1];
      strcpy(m_data, other.m_data);
    }
    return *this;
  }

  // Move assignment operator
  MyString& operator=(MyString&& other) {
    std::cout << "Move assignment operator\n";
    if (this != &other) {
      delete[] m_data;
      m_size = other.m_size;
      m_data = other.m_data;
      other.m_size = 0;
      other.m_data = nullptr;
    }
    return *this;
  }

  // Destructor
  ~MyString() {
    std::cout << "Destructor\n";
    delete[] m_data;
  }

  // Getter for size
  size_t size() const {
    return m_size;
  }

  // Getter for data
  const char* data() const {
    return m_data;
  }

private:
  char* m_data;
  size_t m_size;
};

#endif  // STRING_H