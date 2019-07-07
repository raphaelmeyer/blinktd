#include "blinkt_service.h"

BlinktService::BlinktService()
: _blinkt{}
{
}

grpc::Status BlinktService::SetPixel(grpc::ServerContext* context, const Pixel* request, Response* response) {
  auto const convert_brightness = [](auto brightness){
    switch(brightness) {
      default:
      case Pixel::Off:
        return blinkt::Brightness::Off;
      case Pixel::Low:
        return blinkt::Brightness::Low;
      case Pixel::Medium:
        return blinkt::Brightness::Medium;
      case Pixel::Bright:
        return blinkt::Brightness::Bright;
      case Pixel::Maximum:
        return blinkt::Brightness::Max;
    }
  };

  auto const brightness = convert_brightness(request->brightness());
  blinkt::Color const color{
    static_cast<uint8_t>(request->color().r()),
    static_cast<uint8_t>(request->color().g()),
    static_cast<uint8_t>(request->color().b())
  };

  try {
    _blinkt.set(request->index(), brightness, color);
    response->set_result(Response::Success);
  } catch(std::exception const&) {
    response->set_result(Response::Failure);
  }
  return grpc::Status::OK;
}

grpc::Status BlinktService::Clear(grpc::ServerContext* context, const google::protobuf::Empty* request, Response* response) {
  try {
    _blinkt.clear();
    response->set_result(Response::Success);
  } catch(std::exception const&) {
    response->set_result(Response::Failure);
  }
  return grpc::Status::OK;
}

grpc::Status BlinktService::Show(grpc::ServerContext* context, const google::protobuf::Empty* request, Response* response) {
  try {
    _blinkt.show();
    response->set_result(Response::Success);
  } catch(std::exception const&) {
    response->set_result(Response::Failure);
  }
  return grpc::Status::OK;
}
