#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "crypto.h"
#include "json.h"




static key_record* keys = NULL;
static uint32_t key_count = 0;

static void xor_bytes(char* cipher_key, uint32_t cipher_size, char* buf, uint32_t size);

uint32_t encrypt(int enc_id, char* buf, uint32_t size) {
    key_record* key = keys + enc_id;
    xor_bytes(key->cipher_key, key->size_key, buf, size);
    return size;
}

uint32_t decrypt(int enc_id, char* buf, uint32_t size) {
    key_record* key = keys + enc_id;
    xor_bytes(key->cipher_key, key->size_key, buf, size);
    return size;
}

encryptor_type_t get_type(void) {
    return ENCRYPTOR_SYMMETRIC;
}

int set_params(const char* json_str) {
    char* current_cipher_key = NULL;
    uint32_t current_size_key = 0;
    char* length_value = NULL;
    key_record* key = NULL;
    int ret = 0;

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
    if (!element) {
        ret = -1;
        goto err;
    }

    if (element->type != STRING) {
        ret = -1;
        goto err;
    }

    //parse key length
    length_value = (char*)(element->value);
    if (sscanf(length_value, "%u", &current_size_key) != 1) {
        ret = -1;
        goto err;
    }

    //parse key
    current_cipher_key = (char*)malloc(sizeof(char) * current_size_key);
    if (!current_cipher_key) {
        ret = -1;
        goto err;
    }

    element = json_object_get_element(json_root_msg, "key");
    if (!element) {
        ret = -1;
        goto err;
    }

    if (element->type != STRING) {
        ret = -1;
        goto err;
    }

    memcpy(current_cipher_key, element->value, sizeof(char) * current_size_key);

    //alloc new key
    keys = (key_record*)realloc(keys, sizeof(key_record) * (key_count + 1));

    if (!keys) {
        ret = -2;
        goto err;
    }

    key = keys + key_count;
    //alloc cipher_key for key record
    key->cipher_key = (char*)malloc(sizeof(char) * current_size_key);
    if (!key->cipher_key) {
        ret = -3;
        goto err;
    }

    memcpy(key->cipher_key, current_cipher_key, sizeof(char) * current_size_key);
    key->size_key = current_size_key;
    ++key_count;

    free(current_cipher_key);

    return (key_count - 1);

err:
    if (current_cipher_key) {
        free(current_cipher_key);
    }

    json_object_clear(json_root_msg);
    free(json_root);
    return ret;
}

static void xor_bytes(char* cipher_key, uint32_t cipher_size, char* buf, uint32_t size) {
    char* cur_cipher_key = cipher_key;
    uint32_t cur_cipher_size = cipher_size;

    while (size) {
        if (!cur_cipher_size) {
            cur_cipher_key = cipher_key;
            cur_cipher_size = cipher_size;
        }

        *buf ^= *cur_cipher_key;
        ++buf;
        ++cur_cipher_key;
        --cur_cipher_size;
        --size;
    }
}
