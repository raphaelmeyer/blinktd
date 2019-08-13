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

add_library(blinkt-proto
  cpp/blinkt.pb.cc
  cpp/blinkt.grpc.pb.cc
)
add_library(blinkt::proto ALIAS blinkt-proto)
target_include_directories(blinkt-proto
  PUBLIC
    cpp
)
target_link_libraries(blinkt-proto
  INTERFACE
    protobuf
    grpc++
)
