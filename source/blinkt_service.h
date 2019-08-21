#pragma once

#include "blinkt_api.grpc.pb.h"

#include "blinkt.h"

namespace blinkt {

class BlinktService final : public v1::BlinktAPI::Service {
public:
  BlinktService();

  grpc::Status SetPixel(grpc::ServerContext * context, const v1::SetPixelRequest * request, v1::SetPixelResponse * response) override;
  grpc::Status Clear(grpc::ServerContext * context, const v1::ClearRequest * request, v1::ClearResponse * response) override;
  grpc::Status Show(grpc::ServerContext * context, const v1::ShowRequest * request, v1::ShowResponse * response) override;

private:
  Blinkt _blinkt;
};

} // namespace blinkt
