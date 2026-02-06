# MineTunnel xor encryptor
The ecnryption plugin for [MineTunnel](https://github.com/MastMind/MineTunnel "MineTunnel repo").  
WARNING: This encryptor has been created for demonstration purposes. Do not use it in real encryption

# Build and requirements
Just run make in the folder with cloned project. The gcc 12 is recommended but the older versions should work as well.

# How to use it
The result as `.so` file can be attached to MineTunnel as encryption plugin (More detailed [here](https://github.com/MastMind/MineTunnel "MineTunnel repo") chapter "Encryption").

# How to build my own encryptor
The `.so` must have the next external calls:

```
extern "C" __attribute__ ((visibility ("default"))) uint32_t encrypt(void* instance, char* buf, uint32_t size);
extern "C" __attribute__ ((visibility ("default"))) uint32_t decrypt(void* instance, char* buf, uint32_t size);
extern "C" __attribute__ ((visibility ("default"))) encryptor_type_t get_type(void);
extern "C" __attribute__ ((visibility ("default"))) void* create_instance(const char* json_str);
extern "C" __attribute__ ((visibility ("default"))) void destroy_instance(void* instance);
```

The `encrypt` and `decrypt` functions handle the bytesbuffer. Here must be implementation of the encryption/decryption. The `get_type` function must returns only value `1` (only this value MineTunnel supports or it is `ENCRYPTOR_SYMMETRIC` value; `ENCRYPTOR_ASYMMETRIC` value reserved for future). The `encryptor_type_t` is an enum type (recommended for usage):
```
typedef enum encryptor_type_e {
    ENCRYPTOR_UNKNOWN = 0,
    ENCRYPTOR_SYMMETRIC,
    ENCRYPTOR_ASYMMETRIC
} encryptor_type_t;
```
The `create_instance` function must parse passed JSON's object string with encryption parameters and it returns the pointer on the encryption instance on heap (usually it stores the key data which using in `encrypt`/`decrypt`). The author of the plugin has to define the format of this instance. Also author has to write the `destroy_instance` method which handles freeing memory of the given instance (this method gets called by the MineTunnel when tunnels are destroing).
