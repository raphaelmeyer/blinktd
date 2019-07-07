#include "blinkt.grpc.pb.h"

#include <grpcpp/grpcpp.h>

#include <iostream>

class BlinktImpl final : public Blinkt::Service {
public:
  grpc::Status Show(grpc::ServerContext* context, const google::protobuf::Empty* request, Response* response) override {

    // _blinkt.show();

    response->set_result(Response::Success);
    return grpc::Status::OK;
  }

};

int main() {
  std::string server_address{"0.0.0.0:7023"};
  BlinktImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();

  return 0;
}
