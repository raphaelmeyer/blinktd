#include "pixel.h"

#include <stdexcept>

Pixel::Pixel(std::size_t index)
: _index{index}
{
  if(index > 7) {
    throw std::out_of_range{""};
  }
}

Pixel & Pixel::operator=(std::size_t index) {
  if(index > 7) {
    throw std::out_of_range{""};
  }
  _index = index;
  return *this;
}

Pixel::operator std::size_t() const {
  return _index;
}
