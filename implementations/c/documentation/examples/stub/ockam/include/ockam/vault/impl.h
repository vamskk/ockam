#ifndef OCKAM_VAULT_IMPL_H_
#define OCKAM_VAULT_IMPL_H_

typedef struct {
  ockam_error_t (*deinit)(ockam_vault_t* vault);

  ockam_error_t (*random)(ockam_vault_t* vault, uint8_t* buffer, size_t buffer_size);

  ockam_error_t (*sha256)(ockam_vault_t* vault,
                          const uint8_t* input,
                          size_t         input_length,
                          uint8_t*       digest,
                          size_t         digest_size,
                          size_t*        digest_length);

  ockam_error_t (*secret_generate_random)(ockam_vault_t*                   vault,
                                          ockam_vault_secret_t*            secret,
                                          ockam_vault_secret_type_t        secret_type,
                                          ockam_vault_secret_persistence_t secret_persistence,
                                          uint32_t*                        id);

  ockam_error_t (*secret_import)(ockam_vault_t*                   vault,
                                 const uint8_t*                   input,
                                 size_t                           input_length,
                                 ockam_vault_secret_t*            secret,
                                 ockam_vault_secret_type_t        secret_type,
                                 ockam_vault_secret_persistence_t secret_persistence,
                                 uint32_t*                        id);

  ockam_error_t (*secret_type_set)(ockam_vault_t*             vault,
                                   ockam_vault_secret_t*      secret,
                                   ockam_vault_secret_type_t* secret_type);

  ockam_error_t (*aead_aes_128_gcm_encrypt)(ockam_vault_t*        vault,
                                            ockam_vault_secret_t* key,
                                            uint16_t              nonce,
                                            const uint8_t*        additional_data,
                                            size_t                additional_data_length,
                                            const uint8_t*        plaintext,
                                            size_t                plaintext_length,
                                            uint8_t*              ciphertext_and_tag,
                                            size_t                ciphertext_and_tag_size,
                                            size_t*               ciphertext_and_tag_length);

  ockam_error_t (*aead_aes_128_gcm_decrypt)(ockam_vault_t*        vault,
                                            ockam_vault_secret_t* key,
                                            uint16_t              nonce,
                                            const uint8_t*        additional_data,
                                            size_t                additional_data_length,
                                            const uint8_t*        ciphertext_and_tag,
                                            size_t                ciphertext_and_tag_length,
                                            uint8_t*              plaintext,
                                            size_t                plaintext_size,
                                            size_t*               plaintext_length);
} ockam_vault_dispatch_table_t;

struct ockam_vault {
  ockam_vault_dispatch_table_t* dispatch;
  void*                         context;
};

struct ockam_vault_secret {
  ockam_vault_secret_attributes_t attributes;
  void*                           context;
};

#endif
