#pragma once

#include "blinkt.grpc.pb.h"

#include "blinkt.h"

class BlinktService final : public Blinkt::Service {
public:
  BlinktService();

  grpc::Status SetPixel(grpc::ServerContext* context, const Pixel* request, Response* response) override;
  grpc::Status Clear(grpc::ServerContext* context, const google::protobuf::Empty* request, Response* response) override;
  grpc::Status Show(grpc::ServerContext* context, const google::protobuf::Empty* request, Response* response) override;

private:
  blinkt::Blinkt _blinkt;
};
