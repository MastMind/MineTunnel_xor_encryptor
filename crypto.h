#ifndef CRYPTO_H
#define CRYPTO_H


#include <stdint.h>

#include "defines.h"




extern "C" void encrypt(char* buf, uint32_t size);
extern "C" void decrypt(char* buf, uint32_t size);
extern "C" encryptor_type_t get_type(void);
extern "C" int set_params(const char* json_str);


#endif
