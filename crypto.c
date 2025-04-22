#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "crypto.h"
#include "json.h"




static char* cipher_key = NULL;
static uint32_t size_key = 0;

static void xor_bytes(char* buf, uint32_t size);

void encrypt(char* buf, uint32_t size) {
    xor_bytes(buf, size);
}

void decrypt(char* buf, uint32_t size) {
    xor_bytes(buf, size);
}

encryptor_type_t get_type(void) {
    return ENCRYPTOR_SYMMETRIC;
}

int set_params(const char* json_str) {
    json_value_t json_root = json_from_string(json_str);
    if (!json_root) {
        return -1;
    }

    json_object_t json_root_msg = (json_object_t)(json_root->value);
    if (!json_root_msg) {
        free(json_root);
        return -1;
    }

    json_value_t element = json_object_get_element(json_root_msg, "key_length");
    char* value = NULL;
    if (!element) {
        goto err;
    }

    if (element->type != STRING) {
        goto err;
    }

    //parse key length
    value = (char*)(element->value);
    if (sscanf(value, "%u", &size_key) != 1) {
        goto err;
    }

    cipher_key = (char*)malloc(sizeof(char) * size_key);

    if (!cipher_key) {
        goto err;
    }

    element = json_object_get_element(json_root_msg, "key");
    if (!element) {
        goto err;
    }

    if (element->type != STRING) {
        goto err;
    }

    memcpy(cipher_key, element->value, sizeof(char) * size_key);

    return 0;

err:
    json_object_clear(json_root_msg);
    free(json_root);
    return -1;
}

static void xor_bytes(char* buf, uint32_t size) {
    uint32_t count = size / size_key;
    uint32_t left = size % size_key;
    uint32_t index = 0;

    //main part
    for (uint32_t i = 0; i < count; ++i) {
        for (uint32_t j = 0; j < size_key; ++j) {
            //xor bytes
            buf[index] ^= cipher_key[j];
            ++index;
        }
    }

    //left part
    for (uint32_t j = 0; j < left; ++j) {
        //xor bytes
        buf[index] ^= cipher_key[j];
        ++index;
    }
}
