#ifndef OCKAM_VAULT_H_
#define OCKAM_VAULT_H_

#include "ockam/error.h"

#include <stddef.h>
#include <stdint.h>

#define OCKAM_VAULT_SHA256_DIGEST_LENGTH 32

#define OCKAM_VAULT_AEAD_AES_128_GCM_KEY_LENGTH 16
#define OCKAM_VAULT_AEAD_AES_128_GCM_TAG_LENGTH 16

struct ockam_vault_t;
typedef struct ockam_vault_t ockam_vault_t;

typedef enum {
  OCKAM_VAULT_SECRET_EPHEMERAL = 0,
  OCKAM_VAULT_SECRET_PERSISTENT,
} ockam_vault_secret_persistence_t;

typedef void* ockam_vault_secret_t;

typedef struct {
  uint16_t                         length;
  ockam_vault_secret_persistence_t persistence;
} ockam_vault_secret_attributes_t;

ockam_error_t ockam_vault_deinit(ockam_vault_t* vault);

ockam_error_t ockam_vault_random_bytes_generate(ockam_vault_t* vault, uint8_t* buffer, size_t buffer_size);

ockam_error_t ockam_vault_sha256(ockam_vault_t* vault,
                                 const uint8_t* input,
                                 size_t         input_length,
                                 uint8_t*       digest,
                                 size_t         digest_size,
                                 size_t*        digest_length);

ockam_error_t ockam_vault_secret_generate_random(ockam_vault_t*                   vault,
                                                 ockam_vault_secret_t*            secret,
                                                 ockam_vault_secret_attributes_t* secret_attributes);

ockam_error_t ockam_vault_aead_aes_128_gcm_encrypt(ockam_vault_t*       vault,
                                                   ockam_vault_secret_t key,
                                                   uint16_t             nonce,
                                                   const uint8_t*       additional_data,
                                                   size_t               additional_data_length,
                                                   const uint8_t*       plaintext,
                                                   size_t               plaintext_length,
                                                   uint8_t*             ciphertext_and_tag,
                                                   size_t               ciphertext_and_tag_size,
                                                   size_t*              ciphertext_and_tag_length);

ockam_error_t ockam_vault_aead_aes_128_gcm_decrypt(ockam_vault_t*       vault,
                                                   ockam_vault_secret_t key,
                                                   uint16_t             nonce,
                                                   const uint8_t*       additional_data,
                                                   size_t               additional_data_length,
                                                   const uint8_t*       ciphertext_and_tag,
                                                   size_t               ciphertext_and_tag_length,
                                                   uint8_t*             plaintext,
                                                   size_t               plaintext_size,
                                                   size_t*              plaintext_length);

#endif
