# Ockam Vault Default Test

project(test_default C)

message(STATUS "")
message(STATUS "---------------Test Vault Default ----------------")

ockam_cc_test(
   NAME
     full
   SRCS
     "test_default.c"
   DEPS
     ockam::vault::tests::suite
     ockam::vault::default
     ockam::memory
   PUBLIC )
