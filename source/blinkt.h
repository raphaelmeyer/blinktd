#pragma once

#include "gpio.h"
#include "pixel.h"

#include <array>

namespace blinkt {

struct Color {
  std::uint8_t r;
  std::uint8_t g;
  std::uint8_t b;
};

enum class Brightness : std::uint8_t {
  Off     = 224 + 0,
  Low     = 224 + 3,
  Medium  = 224 + 7,
  Bright  = 224 + 15,
  Max     = 224 + 31
};

class Blinkt {
public:
  static constexpr std::size_t NumPixels = 8;

  Blinkt();

  void set(Pixel pixel, Brightness brightness, Color color);
  void clear();
  void show();

private:
  void write_byte(std::uint8_t value);

  struct Led {
    Brightness brightness;
    Color color;
  };

  Gpio _gpio;
  std::array<Led, NumPixels> _leds;
};

} // namespace blinkt
