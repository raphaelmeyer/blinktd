find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

find_program(PROTOTOOL prototool)
if(NOT PROTOTOOL)
  message(FATAL_ERROR "prototool not found")
endif()

configure_file(prototool.yaml.in prototool.yaml @ONLY)

add_custom_command(
  OUTPUT
    cpp/blinkt.grpc.pb.cc
    cpp/blinkt.grpc.pb.h
    cpp/blinkt.pb.cc
    cpp/blinkt.pb.h
  BYPRODUCTS
    go/blinkt.pb.go
  DEPENDS blinkt.proto
  COMMAND
    cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/blinkt.proto ${CMAKE_CURRENT_BINARY_DIR}/blinkt.proto
  COMMAND
    ${PROTOTOOL} generate ${CMAKE_CURRENT_BINARY_DIR}/blinkt.proto
  COMMENT "Generate from ${CMAKE_CURRENT_SOURCE_DIR}/blinkt.proto"
)

# blinkt-proto
add_library(blinkt-proto
  ${CMAKE_CURRENT_BINARY_DIR}/cpp/blinkt.pb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/cpp/blinkt.grpc.pb.cc
)
add_library(blinkt::proto ALIAS blinkt-proto)
target_include_directories(blinkt-proto
  PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/cpp
)
target_link_libraries(blinkt-proto
  PUBLIC
    Protobuf::Protobuf
    gRPC::gRPC
    settings
)
