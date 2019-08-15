find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

find_program(PROTOTOOL prototool)
if(NOT PROTOTOOL)
  message(FATAL_ERROR "prototool not found")
endif()

add_custom_command(
  OUTPUT
    ${CMAKE_CURRENT_SOURCE_DIR}/_gen/cpp/blinkt.grpc.pb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/_gen/cpp/blinkt.grpc.pb.h
    ${CMAKE_CURRENT_SOURCE_DIR}/_gen/cpp/blinkt.pb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/_gen/cpp/blinkt.pb.h
  BYPRODUCTS
    ${CMAKE_CURRENT_SOURCE_DIR}/_gen/go/blinkt.pb.go
  DEPENDS blinkt.proto
  COMMAND ${PROTOTOOL} generate ${CMAKE_CURRENT_SOURCE_DIR}/blinkt.proto
  COMMENT "Generate ${CMAKE_CURRENT_SOURCE_DIR}/blinkt.proto"
)

# blinkt-proto
add_library(blinkt-proto
  _gen/cpp/blinkt.pb.cc
  _gen/cpp/blinkt.grpc.pb.cc
)
add_library(blinkt::proto ALIAS blinkt-proto)
target_include_directories(blinkt-proto
  PUBLIC
    _gen/cpp
)
target_link_libraries(blinkt-proto
  PUBLIC
    Protobuf::Protobuf
    gRPC::gRPC
    settings
)
