#pragma once

class Socket {
public:
  Socket();
  Socket(int s);

  Socket(Socket const &) = delete;
  Socket& operator=(Socket const &) = delete;

  Socket(Socket && other);
  Socket& operator=(Socket && other);

  ~Socket();

  operator int() const;

  void close();

private:
  int _sock;
};
