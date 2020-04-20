cmake_minimum_required(VERSION 3.14)
project(lib_ockam_vault)

include_directories(../../include)
add_library(ockam_vault vault.c)