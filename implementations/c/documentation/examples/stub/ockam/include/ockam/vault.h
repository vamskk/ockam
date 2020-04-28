#ifndef OCKAM_VAULT_H_
#define OCKAM_VAULT_H_

#include "ockam/error.h"

#include <stddef.h>
#include <stdint.h>

#define OCKAM_VAULT_SHA256_DIGEST_LENGTH 32

#define OCKAM_VAULT_AES128_KEY_LENGTH 16

#define OCKAM_VAULT_AES256_KEY_LENGTH 32

#define OCKAM_VAULT_AEAD_AES_GCM_TAG_LENGTH 16

#define OCKAM_VAULT_CURVE25519_PUBLICKEY_LENGTH 32

#define OCKAM_VAULT_P256_PUBLICKEY_LENGTH 33

struct ockam_vault;
typedef struct ockam_vault ockam_vault_t;

struct ockam_vault_secret;
typedef struct ockam_vault_secret ockam_vault_secret_t;

typedef enum {
  OCKAM_VAULT_SECRET_TYPE_UNSPECIFIED = 0,
  OCKAM_VAULT_SECRET_TYPE_AES128_KEY,
  OCKAM_VAULT_SECRET_TYPE_AES256_KEY,
  OCKAM_VAULT_SECRET_TYPE_CURVE25519_PRIVATEKEY,
  OCKAM_VAULT_SECRET_TYPE_P256_PRIVATEKEY,
} ockam_vault_secret_type_t;

typedef enum {
  OCKAM_VAULT_SECRET_PERSISTENCE_EPHEMERAL = 0,
  OCKAM_VAULT_SECRET_PERSISTENCE_PERSISTENT,
} ockam_vault_secret_persistence_t;

typedef enum {
  OCKAM_VAULT_SECRET_PURPOSE_KEY_AGREEMENT = 0,
} ockam_vault_secret_purpose_t;

typedef struct {
  uint32_t                         id;
  uint16_t                         length;
  ockam_vault_secret_type_t        type;
  ockam_vault_secret_purpose_t     purpose;
  ockam_vault_secret_persistence_t persistence;
} ockam_vault_secret_attributes_t;

ockam_error_t ockam_vault_deinit(ockam_vault_t* vault);

ockam_error_t
ockam_vault_random_bytes_generate(ockam_vault_t* vault, uint8_t* output_buffer, size_t output_buffer_size);

ockam_error_t ockam_vault_secret_handle_get(const ockam_vault_t* vault, uint32_t id, ockam_vault_secret_t* secret);

ockam_error_t ockam_vault_secret_generate(ockam_vault_t*                   vault,
                                          ockam_vault_secret_t*            secret,
                                          ockam_vault_secret_type_t        secret_type,
                                          ockam_vault_secret_persistence_t secret_persistence,
                                          uint32_t*                        id);


ockam_error_t ockam_vault_secret_import(ockam_vault_t*                   vault,
                                        const uint8_t*                   input,
                                        size_t                           input_length,
                                        ockam_vault_secret_t*            secret,
                                        ockam_vault_secret_type_t        secret_type,
                                        ockam_vault_secret_persistence_t secret_persistence,
                                        uint32_t*                        id);

ockam_error_t ockam_vault_secret_export(const ockam_vault_t*        vault,
                                        const ockam_vault_secret_t* secret,
                                        uint8_t*                    output_buffer,
                                        size_t                      output_buffer_size,
                                        size_t*                     output_buffer_length);

ockam_error_t ockam_vault_secret_publickey_get(const ockam_vault_t*        vault,
                                               const ockam_vault_secret_t* secret,
                                               uint8_t*                    output_buffer,
                                               size_t                      output_buffer_size,
                                               size_t*                     output_buffer_length);

ockam_error_t ockam_vault_secret_attributes_get(const ockam_vault_t*             vault,
                                                const ockam_vault_secret_t*      secret,
                                                ockam_vault_secret_attributes_t* secret_attributes);

ockam_error_t ockam_vault_secret_type_set(ockam_vault_t*             vault,
                                          ockam_vault_secret_t*      secret,
                                          ockam_vault_secret_type_t* secret_type);

ockam_error_t ockam_vault_secret_destroy(ockam_vault_t* vault, ockam_vault_secret_t* secret);

ockam_error_t ockam_vault_secret_handle_close(ockam_vault_t* vault, ockam_vault_secret_t* secret);

ockam_error_t ockam_vault_hkdf_sha256(ockam_vault_t*              vault,
                                      const ockam_vault_secret_t* salt,
                                      const ockam_vault_secret_t* input_key_material,
                                      uint8_t                     derived_outputs_count,
                                      ockam_vault_secret_t*       derived_outputs[]);

ockam_error_t ockam_vault_ecdh(ockam_vault_t*              vault,
                               const ockam_vault_secret_t* privatekey,
                               const uint8_t*              peer_publickey,
                               size_t                      peer_publickey_length,
                               ockam_vault_secret_t*       shared_secret);

ockam_error_t ockam_vault_sha256(ockam_vault_t* vault,
                                 const uint8_t* input,
                                 size_t         input_length,
                                 uint8_t*       digest,
                                 size_t         digest_size,
                                 size_t*        digest_length);

ockam_error_t ockam_vault_aead_aes_128_gcm_encrypt(ockam_vault_t*        vault,
                                                   ockam_vault_secret_t* key,
                                                   uint16_t              nonce,
                                                   const uint8_t*        additional_data,
                                                   size_t                additional_data_length,
                                                   const uint8_t*        plaintext,
                                                   size_t                plaintext_length,
                                                   uint8_t*              ciphertext_and_tag,
                                                   size_t                ciphertext_and_tag_size,
                                                   size_t*               ciphertext_and_tag_length);

ockam_error_t ockam_vault_aead_aes_128_gcm_decrypt(ockam_vault_t*        vault,
                                                   ockam_vault_secret_t* key,
                                                   uint16_t              nonce,
                                                   const uint8_t*        additional_data,
                                                   size_t                additional_data_length,
                                                   const uint8_t*        ciphertext_and_tag,
                                                   size_t                ciphertext_and_tag_length,
                                                   uint8_t*              plaintext,
                                                   size_t                plaintext_size,
                                                   size_t*               plaintext_length);

ockam_error_t ockam_vault_aead_aes_256_gcm_encrypt(ockam_vault_t*        vault,
                                                   ockam_vault_secret_t* key,
                                                   uint16_t              nonce,
                                                   const uint8_t*        additional_data,
                                                   size_t                additional_data_length,
                                                   const uint8_t*        plaintext,
                                                   size_t                plaintext_length,
                                                   uint8_t*              ciphertext_and_tag,
                                                   size_t                ciphertext_and_tag_size,
                                                   size_t*               ciphertext_and_tag_length);

ockam_error_t ockam_vault_aead_aes_256_gcm_decrypt(ockam_vault_t*        vault,
                                                   ockam_vault_secret_t* key,
                                                   uint16_t              nonce,
                                                   const uint8_t*        additional_data,
                                                   size_t                additional_data_length,
                                                   const uint8_t*        ciphertext_and_tag,
                                                   size_t                ciphertext_and_tag_length,
                                                   uint8_t*              plaintext,
                                                   size_t                plaintext_size,
                                                   size_t*               plaintext_length);

#endif
