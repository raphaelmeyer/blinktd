#include "blinkt_service.h"

#include <grpcpp/grpcpp.h>

#include <iostream>

int main() {
  std::string server_address{"0.0.0.0:7023"};
  blinkt::BlinktService service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();

  return 0;
}
