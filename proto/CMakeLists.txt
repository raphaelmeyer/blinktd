find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

find_program(PROTOTOOL prototool)
if(NOT PROTOTOOL)
  message(FATAL_ERROR "prototool not found")
endif()

configure_file(prototool.yaml.in prototool.yaml @ONLY)

add_custom_command(
  OUTPUT
    cpp/blinkt_api.grpc.pb.cc
    cpp/blinkt_api.grpc.pb.h
    cpp/blinkt_api.pb.cc
    cpp/blinkt_api.pb.h
    cpp/blinkt_types.grpc.pb.cc
    cpp/blinkt_types.grpc.pb.h
    cpp/blinkt_types.pb.cc
    cpp/blinkt_types.pb.h
  BYPRODUCTS
    go/blinkt_api.pb.go
    go/blinkt_types.pb.go
  DEPENDS
    blinkt_api.proto
    blinkt_types.proto
  COMMAND
    cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/*.proto ${CMAKE_CURRENT_BINARY_DIR}/
  COMMAND
    ${PROTOTOOL} generate ${CMAKE_CURRENT_BINARY_DIR}/blinkt_api.proto
  COMMAND
    ${PROTOTOOL} lint ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generate from ${CMAKE_CURRENT_SOURCE_DIR}/blinkt_api.proto"
)

# blinkt-proto
add_library(blinkt-proto
  ${CMAKE_CURRENT_BINARY_DIR}/cpp/blinkt_api.pb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/cpp/blinkt_api.grpc.pb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/cpp/blinkt_types.pb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/cpp/blinkt_types.grpc.pb.cc
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
