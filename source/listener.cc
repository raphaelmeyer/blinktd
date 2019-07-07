#include "listener.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cstring>
#include <optional>

namespace {

std::optional<std::string> readline(Socket & socket) {
  std::string line{};
  for(;;) {
    char ch;
    auto n = ::read(socket, &ch, 1);
    if(n < 0) {
      return {};
    }
    if(n == 0) {
      return line;
    }
    if(ch == '\n') {
      return line;
    }
    if(ch != '\r') {
      line.push_back(ch);
    }
  }
}

} // namespace

Listener::Listener(std::uint16_t port)
: _port{port}
, _thread{}
, _sock{}
{}

Listener::~Listener() {
  if(_thread.joinable()) {
    _thread.join();
  }
}

void Listener::listen(Handler handler) {
  _sock = ::socket(AF_INET, SOCK_STREAM, 0);
  if(_sock < 0) {
    throw std::runtime_error{std::strerror(errno)};
  }

  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = ::htons(_port);

  if(::bind(_sock, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
        throw std::runtime_error{std::strerror(errno)};
  }

  if(::listen(_sock, 5) < 0) {
    throw std::runtime_error{std::strerror(errno)};
  }

  _handler = handler;
  _thread = std::thread{
    [this]{
      serve();
    }
  };
}

void Listener::serve() {
  for(;;) {
    sockaddr_in client{};
    socklen_t len = sizeof(client);
    Socket accept_sock = ::accept(_sock, reinterpret_cast<sockaddr*>(&client), &len);
    if(accept_sock < 0) {
      return;
    }

    for(;;) {
      auto const line = readline(accept_sock);
      if(not line) {
        break;
      }

      if(line.value().empty()) {
        break;
      }

      if(_handler) {
        auto response = _handler(line.value());
        if(::write(accept_sock, response.c_str(), response.length()) < 0) {
          break;
        }
      }
    }
  }
}

void Listener::stop() {
  ::shutdown(_sock, SHUT_RD);
  ::close(_sock);
  _sock = -1;
}
