cmake_minimum_required(VERSION 3.10)

project(blinktd)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Threads REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

add_subdirectory(testing)
add_subdirectory(proto)

# compile options
add_library(settings INTERFACE)
target_compile_features(settings INTERFACE cxx_std_17)
target_compile_options(settings INTERFACE -pedantic -Wall -Werror)

# blinkt-proto
add_library(blinkt-proto
  proto/cpp/blinkt.pb.cc
  proto/cpp/blinkt.grpc.pb.cc
)
add_library(blinkt::proto ALIAS blinkt-proto)
target_include_directories(blinkt-proto
  PUBLIC
    proto/cpp
)
target_link_libraries(blinkt-proto
  INTERFACE
    Protobuf::Protobuf
    gRPC::gRPC
)

# blinktd
add_executable(blinktd
  source/blinktd.cc
  source/blinkt.cc
  source/gpio.cc
  source/pixel.cc
  source/blinkt_service.cc
)
target_link_libraries(blinktd
  PRIVATE
    blinkt-proto
    settings
    Threads::Threads
)
