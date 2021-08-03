#pragma once

#include <string>

/* Hide implemntation details.
*/
#include <memory>

// pimple template
template <typename T>
class pimpl
{
 private:
  std::unique_ptr<T> impl;
 public:
  pimpl();
  ~pimpl();

  template <typename ...Args> pimpl
    (Args&& ...args);
  T* operator->();
  T& operator*();
};