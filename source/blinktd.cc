#include <fcntl.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <array>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <thread>
#include <chrono>

enum class Pixel { _0, _1, _2, _3, _4, _5, _6, _7 };

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

struct Led {
  Brightness brightness;
  Color color;
};

class Gpio {
public:
  Gpio(std::string const & chip) {
    _chip = ::open(chip.c_str(), O_RDWR);
    if(_chip < 0) {
      throw std::runtime_error("could not open device");
    }

    gpiohandle_request request{};
    request.flags |= GPIOHANDLE_REQUEST_OUTPUT;
    request.lines = 2;
    request.lineoffsets[0] = DATA;
    request.lineoffsets[1] = CLK;
    request.default_values[0] = 0;
    request.default_values[1] = 0;
    std::strcpy(request.consumer_label, "blinkt");

    if(::ioctl(_chip, GPIO_GET_LINEHANDLE_IOCTL, &request) < 0) {
      throw std::runtime_error(std::strerror(errno));
    }

    _line = request.fd;
  }

  ~Gpio() {
    ::close(_chip);
  }

  void write(bool bit) {
    const auto time = std::chrono::microseconds{5};
    set(bit, true);
    std::this_thread::sleep_for(time);
    set(bit, false);
    std::this_thread::sleep_for(time);
  }

private:
  void set(bool data, bool clk) {
    gpiohandle_data v;
    v.values[0] = data ? 1 : 0;
    v.values[1] = clk ? 1 : 0;

    if(ioctl(_line, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &v) < 0) {
      throw std::runtime_error(std::strerror(errno));
    }
  }

  int _chip;
  int _line;

  static int const DATA = 23;
  static int const CLK = 24;
};

class Blinkt {
public:

  Blinkt()
  : _gpio{"/dev/gpiochip0"}
  , _leds{}
  {}

  void set(Pixel pixel, Brightness brightness, Color color) {
    auto & led = _leds.at(static_cast<std::size_t>(pixel));
    led.brightness = brightness;
    led.color = color;
  }

  void clear() {
    for(auto & led : _leds) {
      led.brightness = Brightness::Off;
      led.color.r = 0;
      led.color.g = 0;
      led.color.b = 0;
    }
  }

  void show() {
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

private:
  void write_byte(std::uint8_t value) {
    for(std::size_t i = 0; i < 8; ++i) {
      auto const bit = (value & 0x80) > 0;
      _gpio.write(bit);
      value <<= 1;
    }
  }

  Gpio _gpio;
  std::array<Led, 8> _leds;
};

int main() {

  Blinkt blinkt;

  for(std::size_t i = 0; i < 10; ++i) {
    blinkt.clear();
    blinkt.set(Pixel::_0, Brightness::Low, {31, 31, 31});
    blinkt.set(Pixel::_2, Brightness::Low, {31, 31, 31});
    blinkt.set(Pixel::_4, Brightness::Low, {31, 31, 31});
    blinkt.set(Pixel::_6, Brightness::Low, {31, 31, 31});
    blinkt.show();
    std::this_thread::sleep_for(std::chrono::milliseconds{500});

    blinkt.clear();
    blinkt.set(Pixel::_1, Brightness::Low, {31, 31, 31});
    blinkt.set(Pixel::_3, Brightness::Low, {31, 31, 31});
    blinkt.set(Pixel::_5, Brightness::Low, {31, 31, 31});
    blinkt.set(Pixel::_7, Brightness::Low, {31, 31, 31});
    blinkt.show();
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
  }

  blinkt.clear();
  blinkt.show();

  return 0;
}
