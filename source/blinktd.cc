#include "blinkt.h"
#include "listener.h"

#include <atomic>
#include <chrono>
#include <csignal>
#include <thread>

#include <iostream>

namespace {
std::atomic<bool> done = false;

void signal_handler(int signal)
{
  done = true;
}

} // namespace

int main() {

  Listener server{7023};

  server.listen([](std::string cmd){
    std::cout << "handle command: \'" << cmd << "\'" << std::endl;
    return std::string{};
  });

  std::signal(SIGINT, signal_handler);
  std::signal(SIGTERM, signal_handler);

  while(not done) {
    std::this_thread::sleep_for(std::chrono::seconds{1});
  }

  server.stop();

/*
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

*/

  return 0;
}
