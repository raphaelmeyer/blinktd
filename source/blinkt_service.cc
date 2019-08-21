#include "blinkt_service.h"

#include "blinkt_api.pb.h"

namespace blinkt {

BlinktService::BlinktService() : _blinkt{} {
}

grpc::Status BlinktService::SetPixel(grpc::ServerContext * context, v1::SetPixelRequest const * request, v1::SetPixelResponse * response) {
  auto const convert_brightness = [](auto brightness) {
    switch(brightness) {
    default:
    case v1::Brightness::BRIGHTNESS_OFF:
      return Brightness::Off;
    case v1::Brightness::BRIGHTNESS_LOW:
      return Brightness::Low;
    case v1::Brightness::BRIGHTNESS_MEDIUM:
      return Brightness::Medium;
    case v1::Brightness::BRIGHTNESS_BRIGHT:
      return Brightness::Bright;
    case v1::Brightness::BRIGHTNESS_MAXIMUM:
      return Brightness::Max;
    }
  };

  auto const brightness = convert_brightness(request->brightness());
  Color const color{
    static_cast<uint8_t>(request->color().r()),
    static_cast<uint8_t>(request->color().g()),
    static_cast<uint8_t>(request->color().b())
  };

  try {
    _blinkt.set(request->index(), brightness, color);
    response->set_result(v1::Result::RESULT_SUCCESS);
  } catch(std::exception const &) {
    response->set_result(v1::Result::RESULT_FAILURE);
  }
  return grpc::Status::OK;
}

grpc::Status BlinktService::Clear(grpc::ServerContext * context, const v1::ClearRequest * request, v1::ClearResponse * response) {
  try {
    _blinkt.clear();
    response->set_result(v1::Result::RESULT_SUCCESS);
  } catch(std::exception const &) {
    response->set_result(v1::Result::RESULT_FAILURE);
  }
  return grpc::Status::OK;
}

grpc::Status BlinktService::Show(grpc::ServerContext * context, const v1::ShowRequest * request, v1::ShowResponse * response) {
  try {
    _blinkt.show();
    response->set_result(v1::Result::RESULT_SUCCESS);
  } catch(std::exception const &) {
    response->set_result(v1::Result::RESULT_FAILURE);
  }
  return grpc::Status::OK;
}

} // namespace blinkt
