#ifndef KEY_AGREEMENT_IMPL_H
#define KEY_AGREEMENT_IMPL_H
#include "ockam/vault.h"

struct ockam_key_t {
  ockam_vault_t*        p_vault;
  ockam_vault_secret_t  encrypt_secret;
  ockam_vault_secret_t  decrypt_secret;
  uint16_t              encrypt_nonce;
  uint16_t              decrypt_nonce;
};

#endif