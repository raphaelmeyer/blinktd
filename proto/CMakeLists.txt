find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

find_program(PROTOTOOL prototool)

set(PROTO_OUTPUT
  cpp/blinkt_api.grpc.pb.cc
  cpp/blinkt_api.grpc.pb.h
  cpp/blinkt_api.pb.cc
  cpp/blinkt_api.pb.h
  cpp/blinkt_types.grpc.pb.cc
  cpp/blinkt_types.grpc.pb.h
  cpp/blinkt_types.pb.cc
  cpp/blinkt_types.pb.h
)

set(PROTO_BYPRODUCTS
  go/blinkt_api.pb.go
  go/blinkt_types.pb.go
)

set(PROTO_INPUT
  blinkt_api.proto
  blinkt_types.proto
)

if(PROTOTOOL)

  configure_file(prototool.yaml.in prototool.yaml @ONLY)

  add_custom_command(
    OUTPUT ${PROTO_OUTPUT}
    BYPRODUCTS ${PROTO_BYPRODUCTS}
    DEPENDS ${PROTO_INPUT}
    COMMAND
      cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/*.proto ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND
      ${PROTOTOOL} generate ${CMAKE_CURRENT_BINARY_DIR}/blinkt_api.proto
    COMMAND
      ${PROTOTOOL} lint ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generate code for ${PROTO_INPUT}"
  )

else()
  message(WARNING "prototool not found")

  add_custom_command(
    OUTPUT ${PROTO_OUTPUT}
    BYPRODUCTS ${PROTO_BYPRODUCTS}
    DEPENDS ${PROTO_INPUT}
    COMMAND
      ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/cpp
    COMMAND
      protoc -I ${CMAKE_CURRENT_SOURCE_DIR} --grpc_out=${CMAKE_CURRENT_BINARY_DIR}/cpp --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin ${PROTO_INPUT}
    COMMAND
      protoc -I ${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/cpp ${PROTO_INPUT}
    COMMENT "Generate code for ${PROTO_INPUT}"
  )

endif()


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
