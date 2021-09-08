#include <pimpl.h>

template<typename T>
pimpl<T>::pimpl()
  : impl{new T} {}

// forwarding constructor
template<typename T>
template<typename... Args>
pimpl<T>::pimpl(Args &&... args)
  : impl{new T{std::forward<Args>(args)... }} {}

template<typename T>
pimpl<T>::~pimpl() {}

template<typename T>
T *pimpl<T>::operator->() {
  return impl.get();
}

template<typename T>
T &pimpl<T>::operator*() {
  return *impl.get();
}

class Foo {
  class impl;
  pimpl<impl> impl;
};

// this is the actual implementation
class Foo::impl {

};
