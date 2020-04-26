
#include "ockam/error.h"

#include "ockam/memory.h"
#include "ockam/memory/stdlib.h"

#include "ockam/vault.h"
#include "ockam/vault/default.h"

#include <string.h>

/*
 * This example shows how to encrypt/decrypt with `AEAD_AES_128_GCM`.
 *
 * It demonstrates how to use the default software implementation
 * of the Ockam vault interface (defined in `ockam/vault.h`) for
 * Authenticated Encryption with Additional Data (AEAD).
 *
 * The AEAD operation used in this example is `AEAD_AES_128_GCM`, which is
 * precisely defined in [RFC 5116](https://tools.ietf.org/html/rfc5116).
 */
int main(void)
{
  int exit_code = 0;

  /*
   * All ockam functions return `ockam_error_t`. A function was successful
   * if the return value, `error == OCKAM_ERROR_NONE`
   *
   * This variable is used below to store and check function return values.
   */
  ockam_error_t error;

  /*
   * Before we can initialize a handle to the default vault, we must first
   * initialize a handle to an implementation of the memory interface, which
   * is defined in `ockam/memory.h`.
   *
   * The default vault requires a memory implementation handle at
   * initialization. This approach allows us to plugin the strategy for where
   * and how a vault should allocate memory.
   *
   * We may provide a memory implementation that allocates using
   * stdlib (malloc, free ...) or we may instead provide a an implementation
   * that allocates from a fixed sized buffer.
   *
   * In this example we use the stdlib implementation of the memory interface.
   */

  ockam_memory_t memory;

  error = ockam_memory_stdlib_init(&memory);
  if (error) goto exit;

  /*
   * To initialize a handle to the default vault, we define a variable of the
   * generic type `ockam_vault_t` that will hold a handle to our vault.
   *
   * We also set the initialization attributes in a struct of
   * type `ockam_vault_default_attributes_t`
   *
   * We then pass the address of both these variable to the default
   * implementation specific initialization function.
   */

  ockam_vault_t                    vault;
  ockam_vault_default_attributes_t vault_attributes = { .memory = &memory };

  error = ockam_vault_default_init(&vault, &vault_attributes);
  if (error) goto exit;

  /*
   * We now have an initialized vault handle of type ockam_vault_t, we can
   * call any of the functions defined in `ockam/vault.h` using this handle.
   */

  ockam_vault_secret_t            key;
  ockam_vault_secret_attributes_t key_attributes = {
    .type        = OCKAM_VAULT_SECRET_TYPE_AES128_KEY,
    .persistence = OCKAM_VAULT_SECRET_PERSISTENCE_EPHEMERAL,
  };

  error = ockam_vault_secret_generate(&vault, &key, &key_attributes);
  if (error != OCKAM_ERROR_NONE) { goto exit; }

  uint16_t nonce = 1;

  char*  additional_data        = "some metadata that will be authenticated but not encrypted";
  size_t additional_data_length = strlen(additional_data);

  char*  plaintext        = "some data that will be encrypted";
  size_t plaintext_length = strlen(plaintext);

  size_t   ciphertext_and_tag_size = plaintext_length + OCKAM_VAULT_AEAD_AES_GCM_TAG_LENGTH;
  uint8_t* ciphertext_and_tag;
  size_t   ciphertext_and_tag_length;

  error = ockam_memory_alloc(&memory, &ciphertext_and_tag, ciphertext_and_tag_size);
  if (error) goto exit;

  error = ockam_vault_aead_aes_gcm_encrypt(&vault,
                                           &key,
                                           nonce,
                                           (uint8_t*) additional_data,
                                           additional_data_length,
                                           (uint8_t*) plaintext,
                                           plaintext_length,
                                           ciphertext_and_tag,
                                           ciphertext_and_tag_size,
                                           &ciphertext_and_tag_length);
  if (error) goto exit;

  size_t   decrypted_plaintext_size = plaintext_length;
  uint8_t* decrypted_plaintext;
  size_t   decrypted_plaintext_length;

  error = ockam_memory_alloc(&memory, &decrypted_plaintext, decrypted_plaintext_size);
  if (error) goto exit;

  error = ockam_vault_aead_aes_gcm_decrypt(&vault,
                                           &key,
                                           nonce,
                                           (uint8_t*) additional_data,
                                           additional_data_length,
                                           ciphertext_and_tag,
                                           ciphertext_and_tag_length,
                                           decrypted_plaintext,
                                           decrypted_plaintext_size,
                                           &decrypted_plaintext_length);
  if (error) goto exit;

  error = ockam_memory_free(&memory, ciphertext_and_tag, ciphertext_and_tag_size);
  if (error) goto exit;

  error = ockam_memory_free(&memory, decrypted_plaintext, decrypted_plaintext_size);
  if (error) goto exit;

  /* free resources associated with this handle. */
  error = ockam_vault_deinit(&vault);
  if (error) goto exit;

  /* free resources associated with this handle. */
  error = ockam_memory_deinit(&memory);

exit:
  if (error) exit_code = -1;
  return exit_code;
}
