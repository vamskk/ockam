
#include "ockam/error.h"
#include "ockam/vault.h"
#include "ockam/vault/impl.h"

ockam_error_t ockam_vault_deinit(ockam_vault_t* vault)
{
  return vault->dispatch->deinit(vault);
}

ockam_error_t ockam_vault_random_bytes_generate(ockam_vault_t* vault, uint8_t* buffer, size_t buffer_size)
{
  return vault->dispatch->random(vault, buffer, buffer_size);
}

ockam_error_t ockam_vault_sha256(ockam_vault_t* vault,
                                 const uint8_t* input,
                                 size_t         input_length,
                                 uint8_t*       digest,
                                 size_t         digest_size,
                                 size_t*        digest_length)
{
  return vault->dispatch->sha256(vault, input, input_length, digest, digest_size, digest_length);
}

ockam_error_t ockam_vault_secret_generate_random(ockam_vault_t*                   vault,
                                                 ockam_vault_secret_t*            secret,
                                                 ockam_vault_secret_type_t        secret_type,
                                                 ockam_vault_secret_persistence_t secret_persistence,
                                                 uint32_t*                        id)
{
  return vault->dispatch->secret_generate_random(vault, secret, secret_type, secret_persistence, id);
}



ockam_error_t ockam_vault_secret_import(ockam_vault_t*                   vault,
                                        const uint8_t*                   input,
                                        size_t                           input_length,
                                        ockam_vault_secret_t*            secret,
                                        ockam_vault_secret_type_t        secret_type,
                                        ockam_vault_secret_persistence_t secret_persistence,
                                        uint32_t*                        id)
{
  return vault->dispatch->secret_import(vault, input, input_length, secret, secret_type, secret_persistence, id);
}

ockam_error_t ockam_vault_secret_type_set(ockam_vault_t*             vault,
                                          ockam_vault_secret_t*      secret,
                                          ockam_vault_secret_type_t* secret_type)
{
  return vault->dispatch->secret_type_set(vault, secret, secret_type);
}


ockam_error_t ockam_vault_aead_aes_128_gcm_encrypt(ockam_vault_t*        vault,
                                                   ockam_vault_secret_t* key,
                                                   uint16_t              nonce,
                                                   const uint8_t*        additional_data,
                                                   size_t                additional_data_length,
                                                   const uint8_t*        plaintext,
                                                   size_t                plaintext_length,
                                                   uint8_t*              ciphertext_and_tag,
                                                   size_t                ciphertext_and_tag_size,
                                                   size_t*               ciphertext_and_tag_length)
{
  return vault->dispatch->aead_aes_128_gcm_encrypt(vault,
                                                   key,
                                                   nonce,
                                                   additional_data,
                                                   additional_data_length,
                                                   plaintext,
                                                   plaintext_length,
                                                   ciphertext_and_tag,
                                                   ciphertext_and_tag_size,
                                                   ciphertext_and_tag_length);
}

ockam_error_t ockam_vault_aead_aes_128_gcm_decrypt(ockam_vault_t*        vault,
                                                   ockam_vault_secret_t* key,
                                                   uint16_t              nonce,
                                                   const uint8_t*        additional_data,
                                                   size_t                additional_data_length,
                                                   const uint8_t*        ciphertext_and_tag,
                                                   size_t                ciphertext_and_tag_length,
                                                   uint8_t*              plaintext,
                                                   size_t                plaintext_size,
                                                   size_t*               plaintext_length)
{
  return vault->dispatch->aead_aes_128_gcm_decrypt(vault,
                                                   key,
                                                   nonce,
                                                   additional_data,
                                                   additional_data_length,
                                                   ciphertext_and_tag,
                                                   ciphertext_and_tag_length,
                                                   plaintext,
                                                   plaintext_size,
                                                   plaintext_length);
}
