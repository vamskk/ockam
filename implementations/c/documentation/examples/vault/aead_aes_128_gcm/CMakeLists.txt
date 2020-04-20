cmake_minimum_required(VERSION 3.14)
project(aead_aes_128_gcm C)

set(CMAKE_C_STANDARD 90)

include_directories(../../stub/ockam/include)
add_executable(aead_aes_128_gcm main.c)

target_link_libraries(aead_aes_128_gcm ockam_memory ockam_memory_stdlib ockam_vault ockam_vault_default)