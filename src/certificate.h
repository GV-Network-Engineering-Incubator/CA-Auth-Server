/**
 * Copyright 2018-present, Grand Valley State University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdlib.h>
#include <stdint.h>
#include <openssl/x509v3.h> // The crypto algorithm

#define RSA_KEY_BITS 4096

#define REQ_DN_C "US"
#define REQ_DN_ST "MI"
#define REQ_DN_L ""
#define REQ_DN_O "Grand Valley State University"
#define REQ_DN_OU "IT"
#define REQ_DN_CN "www.gvsu.edu"

void cleanup(void);
void crt_to_pem(X509 *crt, uint8_t **crt_bytes, size_t *crt_size);
int generate_key_csr(EVP_PKEY **key, X509_REQ **req);
int generate_set_random_serial(X509 *crt);
int generate_signed_key_pair(EVP_PKEY *ca_key, X509 *ca_crt, EVP_PKEY **key, X509 **crt);
void initialize(void);
void key_to_pem(EVP_PKEY *key, uint8_t **key_bytes, size_t *key_size);
int load_ca(const char *ca_key_path, EVP_PKEY **ca_key, const char *ca_crt_path, X509 **ca_crt);
void print_bytes(uint8_t *data, size_t size);
int validate_certificate(X509* crt, EVP_PKEY** key);
