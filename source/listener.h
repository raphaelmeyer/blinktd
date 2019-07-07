#pragma once

#include "socket.h"

#include <functional>
#include <future>
#include <string>
#include <thread>

class Listener {
public:
  using Handler = std::function<std::string(std::string)>;

  Listener(std::uint16_t port);
  ~Listener();

  void listen(Handler handler);
  void stop();

private:
  void serve();

  std::uint16_t _port;
  std::thread _thread;
  Socket _sock;
  Handler _handler;
};
