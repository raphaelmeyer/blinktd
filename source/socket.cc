#include "socket.h"

#include <unistd.h>

Socket::Socket() : _sock{-1} {}

Socket::Socket(int s) : _sock{s} {
}

Socket::Socket(Socket && other) {
  _sock = other._sock;
  other._sock = -1;
}

Socket& Socket::operator=(Socket && other) {
  _sock = other._sock;
  other._sock = -1;
  return *this;
}

Socket::~Socket() {
  close();
}

Socket::operator int() const {
  return _sock;
}

void Socket::close() {
  if(_sock >= 0) {
    ::close(_sock);
  }
}
