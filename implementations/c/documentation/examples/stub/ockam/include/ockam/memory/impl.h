#ifndef OCKAM_MEMORY_IMPL_H_
#define OCKAM_MEMORY_IMPL_H_

typedef struct {
  ockam_error_t (*deinit)(ockam_memory_t* memory);
  ockam_error_t (*alloc)(ockam_memory_t* memory, uint8_t** buffer, size_t buffer_size);
  ockam_error_t (*free)(ockam_memory_t* memory, uint8_t* buffer, size_t buffer_size);
} ockam_memory_dispatch_table_t;

struct ockam_memory_t {
  ockam_memory_dispatch_table_t* dispatch;
  void*                          context;
};

#endif
