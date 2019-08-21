# Find gRPC
include(FindPackageHandleStandardArgs)

find_path(Protobuf_INCLUDE_DIR
  NAMES "service.h"
  PATH_SUFFIXES "google/protobuf"
)
find_library(Protobuf_LIBRARY
  NAMES "protobuf"
)

find_program(Protobuf_protoc_EXECUTABLE
  NAMES protoc
)

if(Protobuf_protoc_EXECUTABLE)
  execute_process(
    COMMAND ${Protobuf_protoc_EXECUTABLE} --version
    RESULT_VARIABLE version_result
    OUTPUT_VARIABLE version_output
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(version_result)
    message(FATAL_ERROR "Could not run protoc --version")
  else()
    if(version_output MATCHES "libprotoc ([0-9]+\.[0-9]+\.[0-9]+)")
      set(Protobuf_VERSION "${CMAKE_MATCH_1}")
    else()
      message(FATAL_ERROR "Could not get version from ${version_output}")
    endif()
  endif()
else()
  message(FATAL_ERROR "Could not find protoc")
endif()

find_package_handle_standard_args(Protobuf
  FOUND_VAR Protobuf_FOUND
  REQUIRED_VARS
    Protobuf_LIBRARY
    Protobuf_INCLUDE_DIR
  VERSION_VAR Protobuf_VERSION
)

if(Protobuf_FOUND)
  set(Protobuf_LIBRARIES ${Protobuf_LIBRARY})
  set(Protobuf_INCLUDE_DIRS ${Protobuf_INCLUDE_DIR})
endif()

if(Protobuf_FOUND AND NOT TARGET Protobuf::Protobuf)
  add_library(Protobuf::Protobuf UNKNOWN IMPORTED)
  set_target_properties(Protobuf::Protobuf PROPERTIES
    IMPORTED_LOCATION "${Protobuf_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${Protobuf_INCLUDE_DIR}"
  )
endif()

mark_as_advanced(
  Protobuf_INCLUDE_DIR
  Protobuf_LIBRARY
)
