#include "hash.h"

uint32_t OAT_Hash(const void* key, size_t len)
{
    uint32_t hash = 0;
    const byte* bytes = (const byte*)key;

    for (size_t i = 0; i < len; i++) {
        hash += bytes[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;

    return hash;
}