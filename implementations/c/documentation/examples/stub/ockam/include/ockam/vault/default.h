// this header file will eventually live at lib/vault/default/default.h
// but compiled using cmake to be used by external projects
// as `ockam/vault/default.h`

#ifndef OCKAM_VAULT_DEFAULT_H_
#define OCKAM_VAULT_DEFAULT_H_

#include "ockam/error.h"
#include "ockam/memory.h"
#include "ockam/vault.h"
#include "ockam/vault/impl.h"

typedef struct {
  ockam_memory_t* memory;
} ockam_vault_default_attributes_t;

ockam_error_t ockam_vault_default_init(ockam_vault_t* vault, ockam_vault_default_attributes_t* vault_attributes);

#endif
