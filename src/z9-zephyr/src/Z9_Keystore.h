

#pragma once

#include <cstdint>

enum Z9_Key : uint8_t { KEY_PAIRING, KEY_LINK, KEY_NOC, NUM_Z9_KEY };
static const unsigned Z9_KEY_MAX_LENGTH = 16;

struct Z9_Keystore
{
private:
    struct Z9_Keystore_Key
    {
        uint8_t     key[Z9_KEY_MAX_LENGTH];
        uint8_t     key_length;
        bool        ready { false };
    };

    // TODO: do std containers work?
    //std:array<Z9_Keystore_Key, NUM_Z9_KEY> keys;
    Z9_Keystore_Key keys[NUM_Z9_KEY];

public:
    static Z9_Keystore& get();      // obtain singleton
    bool is_ready(enum Z9_Key) const;


    Z9_Keystore_Key& reset();
    Z9_Keystore_Key& set  (uint8_t *key_p, unsigned key_length);
    Z9_Keystore_Key& xor  (uint8_t *key_p, unsigned key_length);
    Z9_Keystore_Key& ready();    


};