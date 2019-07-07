cmake_minimum_required(VERSION 3.10)

project(Template)

find_package(Threads REQUIRED)

add_subdirectory(testing)

add_library(settings INTERFACE)
target_compile_features(settings INTERFACE cxx_std_17)
target_compile_options(settings INTERFACE -pedantic -Wall -Werror)

add_executable(blinktd
  source/blinktd.cc
  source/blinkt.cc
  source/gpio.cc
  source/pixel.cc
  source/listener.cc
  source/socket.cc
)
target_link_libraries(blinktd PRIVATE settings Threads::Threads)
