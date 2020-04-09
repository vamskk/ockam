cmake_minimum_required(VERSION 3.13.1)

# We don't need to build our tests when built as part of another project
set(OCKAM_BUILD_TESTS OFF CACHE BOOL "")

# Make sure our modules take precedence while configuring the project
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(OCKAM_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

# Like our top-level CMakeLists.txt, include all of our helper modules
include(ockam_triples)
include(ockam_platform)

get_target_triple(OCKAM_TARGET_TRIPLE OCKAM_TARGET_ARCHITECTURE OCKAM_TARGET_VENDOR OCKAM_TARGET_OS OCKAM_TARGET_ABI)
get_host_triple(OCKAM_HOST_TRIPLE OCKAM_HOST_ARCHITECTURE OCKAM_HOST_VENDOR OCKAM_HOST_OS OCKAM_HOST_ABI)

include(ockam_macros)
include(ockam_copts)
include(ockam_cc_binary)
include(ockam_cc_library)
include(ockam_cc_test)
include(ockam_cc_alwayslink)
include(ockam_debug)
include(ockam_third_party)

# Add our libraries to the available targets
set_alwayslink_ockam_libs()
add_subdirectory("${CMAKE_BINARY_DIR}/lib")
ockam_complete_binary_link_options()

# Remove our modules from the module path once done
list(REMOVE_ITEM CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
