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
extern "C" __attribute__ ((visibility ("default"))) uint32_t encrypt(int enc_id, char* buf, uint32_t size);
extern "C" __attribute__ ((visibility ("default"))) uint32_t decrypt(int enc_id, char* buf, uint32_t size);
extern "C" __attribute__ ((visibility ("default"))) encryptor_type_t get_type(void);
extern "C" __attribute__ ((visibility ("default"))) int set_params(const char* json_str);
```

The `encrypt` and `decrypt` functions handle the bytesbuffer. Here must be implementation of the encryption. The `get_type` function must returns only value `1` (only this value MineTunnel supports or it is `ENCRYPTOR_SYMMETRIC` value; `ENCRYPTOR_ASYMMETRIC` value reserved for future). The `encryptor_type_t` is an enum type (recommended for usage):
```
typedef enum encryptor_type_e {
    ENCRYPTOR_UNKNOWN = 0,
    ENCRYPTOR_SYMMETRIC,
    ENCRYPTOR_ASYMMETRIC
} encryptor_type_t;
```
The `set_params` function must parse passed JSON's object string with encryption parameters and it returns the valid encryption id (should be integer more than or equal 0; values below 0 will be interpreted as error). The author of the plugin has to define the format of this object and use it for setting the encryption. Also author should write the management of encryption id (this parameter passes to `encrypt/decrypt` and defines the right keys for any crypto request). Here `enc_id` works by the next algorythm: `set_params` parses JSON string and stores key into special array of keys and returns the index of record in this array as `enc_id`; when `MineTunnel` encrypts or decrypts data it passes the `enc_id` as argument and those methods should get the right keys from stored array.
