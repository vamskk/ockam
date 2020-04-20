cmake_minimum_required(VERSION 3.14)
project(random C)

set(CMAKE_C_STANDARD 90)

include_directories(../../stub/ockam/include)
add_executable(random main.c)

target_link_libraries(random ockam_memory ockam_memory_stdlib ockam_vault ockam_vault_default)