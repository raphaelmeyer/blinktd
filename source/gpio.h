#pragma once

#include <string>

namespace blinkt {

class Gpio {
public:
  Gpio(std::string const & chip);
  ~Gpio();

  void write(bool bit);

private:
  void set(bool data, bool clk);

  int _chip;
  int _line;

  static int const DATA = 23;
  static int const CLK = 24;
};

} // namespace blinkt
