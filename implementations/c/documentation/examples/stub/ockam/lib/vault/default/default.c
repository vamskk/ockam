
#include <stdlib.h>

#include "ockam/error.h"

#include "ockam/vault.h"
#include "ockam/vault/default.h"

typedef struct {
  uint32_t i;
} ockam_vault_default_context_t;

ockam_error_t ockam_vault_default_deinit(ockam_vault_t* vault);

ockam_error_t ockam_vault_default_random_bytes_generate(ockam_vault_t* vault, uint8_t* buffer, size_t buffer_size);

ockam_error_t ockam_vault_default_sha256(ockam_vault_t* vault,
                                         const uint8_t* input,
                                         size_t         input_length,
                                         uint8_t*       digest,
                                         size_t         digest_size,
                                         size_t*        digest_length);

ockam_error_t ockam_vault_default_secret_generate_random(ockam_vault_t*                   vault,
                                                         ockam_vault_secret_t*            secret,
                                                         ockam_vault_secret_attributes_t* attributes);

ockam_error_t ockam_vault_default_aead_aes_128_gcm_encrypt(ockam_vault_t*       vault,
                                                           ockam_vault_secret_t key,
                                                           uint16_t             nonce,
                                                           const uint8_t*       additional_data,
                                                           size_t               additional_data_length,
                                                           const uint8_t*       plaintext,
                                                           size_t               plaintext_length,
                                                           uint8_t*             ciphertext_and_tag,
                                                           size_t               ciphertext_and_tag_size,
                                                           size_t*              ciphertext_and_tag_length);

ockam_error_t ockam_vault_default_aead_aes_128_gcm_decrypt(ockam_vault_t*       vault,
                                                           ockam_vault_secret_t key,
                                                           uint16_t             nonce,
                                                           const uint8_t*       additional_data,
                                                           size_t               additional_data_length,
                                                           const uint8_t*       ciphertext_and_tag,
                                                           size_t               ciphertext_and_tag_length,
                                                           uint8_t*             plaintext,
                                                           size_t               plaintext_size,
                                                           size_t*              plaintext_length);

ockam_vault_dispatch_table_t ockam_vault_default_dispatch_table = {
  &ockam_vault_default_deinit,
  &ockam_vault_default_random_bytes_generate,
  &ockam_vault_default_sha256,
  &ockam_vault_default_secret_generate_random,
  &ockam_vault_default_aead_aes_128_gcm_encrypt,
  &ockam_vault_default_aead_aes_128_gcm_decrypt,
};

ockam_error_t ockam_vault_default_init(ockam_vault_t* vault, ockam_vault_default_attributes_t* attributes)
{
  ockam_error_t                  error = OCKAM_ERROR_NONE;
  ockam_vault_default_context_t* ctx   = 0;

  if (vault == 0) {
    error = OCKAM_ERROR;
    goto exit;
  }

  if ((attributes == 0) || (attributes->memory == 0)) {
    error = OCKAM_ERROR;
    goto exit;
  }

  ockam_memory_t* memory = attributes->memory;
  error                  = ockam_memory_alloc(memory, (uint8_t**) &ctx, sizeof(ockam_vault_default_context_t));
  if (error != OCKAM_ERROR_NONE) { goto exit; }

  vault->context  = ctx;
  vault->dispatch = &ockam_vault_default_dispatch_table;

exit:
  return error;
}

ockam_error_t ockam_vault_default_deinit(ockam_vault_t* vault)
{
  return OCKAM_ERROR_NONE;
}

ockam_error_t ockam_vault_default_random_bytes_generate(ockam_vault_t* vault, uint8_t* buffer, size_t buffer_size)
{
  ockam_error_t error = OCKAM_ERROR_NONE;

  for (size_t i = 0; i < buffer_size; i++) { *buffer++ = (rand() % 256); }

  return error;
}

ockam_error_t ockam_vault_default_sha256(ockam_vault_t* vault,
                                         const uint8_t* input,
                                         size_t         input_length,
                                         uint8_t*       digest,
                                         size_t         digest_size,
                                         size_t*        digest_length)
{
  ockam_error_t error = OCKAM_ERROR_NONE;

  /* random bytes for now instead of the hash */
  for (size_t i = 0; i < digest_size; i++) { *digest++ = (rand() % 256); }

  return error;
}

ockam_error_t ockam_vault_default_secret_generate_random(ockam_vault_t*                   vault,
                                                         ockam_vault_secret_t*            secret,
                                                         ockam_vault_secret_attributes_t* secret_attributes)
{
  ockam_error_t error = OCKAM_ERROR_NONE;
  return error;
}

ockam_error_t ockam_vault_default_aead_aes_128_gcm_encrypt(ockam_vault_t*       vault,
                                                           ockam_vault_secret_t key,
                                                           uint16_t             nonce,
                                                           const uint8_t*       additional_data,
                                                           size_t               additional_data_length,
                                                           const uint8_t*       plaintext,
                                                           size_t               plaintext_length,
                                                           uint8_t*             ciphertext_and_tag,
                                                           size_t               ciphertext_and_tag_size,
                                                           size_t*              ciphertext_and_tag_length)
{
  ockam_error_t error = OCKAM_ERROR_NONE;
  return error;
}

ockam_error_t ockam_vault_default_aead_aes_128_gcm_decrypt(ockam_vault_t*       vault,
                                                           ockam_vault_secret_t key,
                                                           uint16_t             nonce,
                                                           const uint8_t*       additional_data,
                                                           size_t               additional_data_length,
                                                           const uint8_t*       ciphertext_and_tag,
                                                           size_t               ciphertext_and_tag_length,
                                                           uint8_t*             plaintext,
                                                           size_t               plaintext_size,
                                                           size_t*              plaintext_length)
{
  ockam_error_t error = OCKAM_ERROR_NONE;
  return error;
}
