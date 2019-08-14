# Find gRPC
include(FindPackageHandleStandardArgs)

find_path(Protobuf_INCLUDE_DIR
  NAMES "service.h"
  PATH_SUFFIXES "google/protobuf"
)
find_library(Protobuf_LIBRARY
  NAMES "protobuf"
)

find_package_handle_standard_args(Protobuf
  FOUND_VAR Protobuf_FOUND
  REQUIRED_VARS
    Protobuf_LIBRARY
    Protobuf_INCLUDE_DIR
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
