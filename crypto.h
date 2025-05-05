#ifndef CRYPTO_H
#define CRYPTO_H


#include <stdint.h>

#include "defines.h"



typedef struct key_record_s {
	char* cipher_key;
	uint32_t size_key;
} key_record;

extern "C" __attribute__ ((visibility ("default"))) uint32_t encrypt(int enc_id, char* buf, uint32_t size);
extern "C" __attribute__ ((visibility ("default"))) uint32_t decrypt(int enc_id, char* buf, uint32_t size);
extern "C" __attribute__ ((visibility ("default"))) encryptor_type_t get_type(void);
extern "C" __attribute__ ((visibility ("default"))) int set_params(const char* json_str);


#endif
