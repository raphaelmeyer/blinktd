add_custom_command(
  OUTPUT
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/blinkt.grpc.pb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/blinkt.grpc.pb.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/blinkt.pb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/blinkt.pb.h
    ${CMAKE_CURRENT_SOURCE_DIR}/go/blinkt.pb.go
  DEPENDS blinkt.proto
  COMMAND prototool generate ${CMAKE_CURRENT_SOURCE_DIR}
)
