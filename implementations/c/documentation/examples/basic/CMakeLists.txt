cmake_minimum_required(VERSION 3.14)

project(basic_example
  VERSION 1.0
)

get_filename_component(ockam_DIR "../../../" REALPATH BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "ockam_DIR is ${ockam_DIR}")

include(FetchContent)
FetchContent_Declare(ockam
  URL "${ockam_DIR}"
)
FetchContent_Populate(ockam
  SOURCE_DIR "${ockam_DIR}"
)
add_subdirectory(${ockam_SOURCE_DIR} ${ockam_BINARY_DIR})

add_library(basic_example STATIC "example.c")
add_dependencies(basic_example
  ockam::log
  ockam::memory
  ockam::vault::default
)
set_target_properties(basic_example PROPERTIES
  INCLUDE_DIRECTORIES $<TARGET_PROPERTY:ockam::vault::default,INTERFACE_INCLUDE_DIRECTORIES>
)
