
#include "ockam/error.h"
#include "ockam/memory.h"
#include "ockam/memory/impl.h"

ockam_error_t ockam_memory_deinit(ockam_memory_t* memory)
{
  return memory->dispatch->deinit(memory);
}

ockam_error_t ockam_memory_alloc(ockam_memory_t* memory, uint8_t** buffer, size_t buffer_size)
{
  return memory->dispatch->alloc(memory, buffer, buffer_size);
}

ockam_error_t ockam_memory_free(ockam_memory_t* memory, uint8_t* buffer, size_t buffer_size)
{
  return memory->dispatch->free(memory, buffer, buffer_size);
}
