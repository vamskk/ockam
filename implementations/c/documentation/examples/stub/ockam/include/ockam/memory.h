#ifndef OCKAM_MEMORY_H_
#define OCKAM_MEMORY_H_

#include "ockam/error.h"

#include <stddef.h>
#include <stdint.h>

struct ockam_memory_t;
typedef struct ockam_memory_t ockam_memory_t;

ockam_error_t ockam_memory_deinit(ockam_memory_t* memory);
ockam_error_t ockam_memory_alloc(ockam_memory_t* memory, uint8_t** buffer, size_t buffer_size);
ockam_error_t ockam_memory_free(ockam_memory_t* memory, uint8_t* buffer, size_t buffer_size);

#endif
