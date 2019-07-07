#include "gpio.h"

#include <fcntl.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <stdexcept>
#include <cstring>
#include <thread>
#include <chrono>

Gpio::Gpio(std::string const & chip) {
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

Gpio::~Gpio() {
  ::close(_chip);
}

void Gpio::write(bool bit) {
  const auto time = std::chrono::microseconds{5};
  set(bit, true);
  std::this_thread::sleep_for(time);
  set(bit, false);
  std::this_thread::sleep_for(time);
}

void Gpio::set(bool data, bool clk) {
  gpiohandle_data v;
  v.values[0] = data ? 1 : 0;
  v.values[1] = clk ? 1 : 0;

  if(ioctl(_line, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &v) < 0) {
    throw std::runtime_error(std::strerror(errno));
  }
}
