# Find gRPC
include(FindPackageHandleStandardArgs)

find_path(gRPC_INCLUDE_DIR
  NAMES "grpc++.h"
  PATH_SUFFIXES "grpc++"
)
find_library(gRPC_LIBRARY
  NAMES "grpc++"
)

find_package_handle_standard_args(gRPC
  FOUND_VAR gRPC_FOUND
  REQUIRED_VARS
    gRPC_LIBRARY
    gRPC_INCLUDE_DIR
)

if(gRPC_FOUND)
  set(gRPC_LIBRARIES ${gRPC_LIBRARY})
  set(gRPC_INCLUDE_DIRS ${gRPC_INCLUDE_DIR})
endif()

if(gRPC_FOUND AND NOT TARGET gRPC::gRPC)
  add_library(gRPC::gRPC UNKNOWN IMPORTED)
  set_target_properties(gRPC::gRPC PROPERTIES
    IMPORTED_LOCATION "${gRPC_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${gRPC_INCLUDE_DIR}"
  )
endif()

mark_as_advanced(
  gRPC_INCLUDE_DIR
  gRPC_LIBRARY
)
