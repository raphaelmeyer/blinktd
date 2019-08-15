cmake_minimum_required(VERSION 3.10)

project(blinktd)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Threads REQUIRED)

add_subdirectory(testing)
add_subdirectory(proto)

# compile options
add_library(settings INTERFACE)
target_compile_features(settings INTERFACE cxx_std_17)
target_compile_options(settings INTERFACE -pedantic -Wall -Werror)

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
