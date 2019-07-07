#include "blinkt.h"

#include <chrono>
#include <thread>

int main() {

  Blinkt blinkt;

  for(std::size_t i = 0; i < 10; ++i) {
    blinkt.clear();
    blinkt.set(0, Brightness::Low, {31, 31, 31});
    blinkt.set(2, Brightness::Low, {31, 31, 31});
    blinkt.set(4, Brightness::Low, {31, 31, 31});
    blinkt.set(6, Brightness::Low, {31, 31, 31});
    blinkt.show();
    std::this_thread::sleep_for(std::chrono::milliseconds{500});

    blinkt.clear();
    blinkt.set(1, Brightness::Low, {31, 31, 31});
    blinkt.set(3, Brightness::Low, {31, 31, 31});
    blinkt.set(5, Brightness::Low, {31, 31, 31});
    blinkt.set(7, Brightness::Low, {31, 31, 31});
    blinkt.show();
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
  }

  blinkt.clear();
  blinkt.show();

  return 0;
}
