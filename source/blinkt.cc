#include "blinkt.h"

#include "gpio.h"

namespace blinkt {

Blinkt::Blinkt()
: _gpio{"/dev/gpiochip0"}
, _leds{}
{}

void Blinkt::set(Pixel pixel, Brightness brightness, Color color) {
  auto & led = _leds.at(pixel);
   led.brightness = brightness;
   led.color = color;
}

void Blinkt::clear() {
  for(auto & led : _leds) {
    led.brightness = Brightness::Off;
    led.color.r = 0;
    led.color.g = 0;
    led.color.b = 0;
  }
}

void Blinkt::show() {
  for(std::size_t i = 0; i < 32; ++i) {
    _gpio.write(false);
  }

  for(auto const & led : _leds) {
    write_byte(static_cast<std::uint8_t>(led.brightness));
    write_byte(led.color.r);
    write_byte(led.color.g);
    write_byte(led.color.b);
  }

  for(std::size_t i = 0; i < 36; ++i) {
    _gpio.write(false);
  }
}

void Blinkt::write_byte(std::uint8_t value) {
  for(std::size_t i = 0; i < 8; ++i) {
    auto const bit = (value & 0x80) > 0;
    _gpio.write(bit);
    value <<= 1;
  }
}

} // namespace blinkt
