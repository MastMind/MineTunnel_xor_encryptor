#ifndef CRYPTO_H
#define CRYPTO_H


#include <stdint.h>

#include "defines.h"



typedef struct key_record_s {
	char* cipher_key;
	uint32_t size_key;
} key_record;

extern "C" __attribute__ ((visibility ("default"))) uint32_t encrypt(void* instance, char* buf, uint32_t size);
extern "C" __attribute__ ((visibility ("default"))) uint32_t decrypt(void* instance, char* buf, uint32_t size);
extern "C" __attribute__ ((visibility ("default"))) encryptor_type_t get_type(void);
extern "C" __attribute__ ((visibility ("default"))) void* create_instance(const char* json_str);
extern "C" __attribute__ ((visibility ("default"))) void destroy_instance(void* instance);


#endif
