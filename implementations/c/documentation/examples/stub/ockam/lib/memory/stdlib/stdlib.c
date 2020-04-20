
#include "ockam/error.h"

#include "ockam/memory.h"
#include "ockam/memory/stdlib.h"

#include <stdlib.h>

typedef struct {
  uint32_t max;
} ockam_memory_stdlib_context_t;

ockam_error_t ockam_memory_stdlib_deinit(ockam_memory_t* memory);
ockam_error_t ockam_memory_stdlib_alloc(ockam_memory_t* memory, uint8_t** buffer, size_t buffer_size);
ockam_error_t ockam_memory_stdlib_free(ockam_memory_t* memory, uint8_t* p_buffer, size_t buffer_size);

ockam_memory_dispatch_table_t ockam_memory_stdlib_dispatch_table = {
  &ockam_memory_stdlib_deinit,
  &ockam_memory_stdlib_alloc,
  &ockam_memory_stdlib_free,
};

ockam_error_t ockam_memory_stdlib_init(ockam_memory_t* memory)
{
  ockam_error_t error = OCKAM_ERROR_NONE;

  if (memory == 0) {
    error = OCKAM_ERROR;
    goto exit;
  }

  ockam_memory_stdlib_context_t* c = (ockam_memory_stdlib_context_t*) malloc(sizeof(ockam_memory_stdlib_context_t));
  if (c == 0) {
    error = OCKAM_ERROR;
    goto exit;
  }

  memory->context  = c;
  memory->dispatch = &ockam_memory_stdlib_dispatch_table;

exit:
  return error;
}

ockam_error_t ockam_memory_stdlib_deinit(ockam_memory_t* memory)
{
  ockam_error_t error = OCKAM_ERROR_NONE;

  if (memory == 0) {
    error = OCKAM_ERROR;
    goto exit;
  }

  ockam_memory_stdlib_context_t* context = (ockam_memory_stdlib_context_t*) memory->context;
  if (context != 0) free(context);

exit:
  return error;
}

ockam_error_t ockam_memory_stdlib_alloc(ockam_memory_t* memory, uint8_t** buffer, size_t buffer_size)
{
  ockam_error_t error = OCKAM_ERROR_NONE;
  *buffer             = malloc(buffer_size);

  if (*buffer == 0) { error = OCKAM_ERROR; }

  return error;
}

ockam_error_t ockam_memory_stdlib_free(ockam_memory_t* memory, uint8_t* buffer, size_t buffer_size)
{
  ockam_error_t error = OCKAM_ERROR_NONE;

  if (buffer == 0) {
    error = OCKAM_ERROR;
    goto exit;
  }

  free(buffer);
exit:
  return error;
}
