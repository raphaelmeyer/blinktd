#pragma once

#include <cstddef>

namespace blinkt {

class Pixel {
public:
  Pixel() = default;

  Pixel(std::size_t index);
  Pixel & operator=(std::size_t index);

  operator std::size_t() const;

private:
  std::size_t _index;
};

} // namespace blinkt
