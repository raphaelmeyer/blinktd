add_custom_command(
  OUTPUT source/blinkt.grpc.pb.cc
  DEPENDS blinkt.proto
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/source
  COMMAND protoc -I ${CMAKE_CURRENT_SOURCE_DIR} --grpc_out=${CMAKE_CURRENT_BINARY_DIR}/source --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin blinkt.proto
  BYPRODUCTS blinkt.grpc.pb.h
)

add_custom_command(
  OUTPUT source/blinkt.pb.cc
  DEPENDS blinkt.proto
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/source
  COMMAND protoc -I ${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/source blinkt.proto
  BYPRODUCTS blinkt.pb.h
)

add_library(blinkt-proto
  ${CMAKE_CURRENT_BINARY_DIR}/source/blinkt.pb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/source/blinkt.grpc.pb.cc
)
add_library(blinkt::proto ALIAS blinkt-proto)
target_include_directories(blinkt-proto
  PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/source
)
target_link_libraries(blinkt-proto
  INTERFACE
    protobuf
    grpc++
)
