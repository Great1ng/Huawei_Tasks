#ifndef PROTECTED_STACK_STK_CONFIG_H
#define PROTECTED_STACK_STK_CONFIG_H

#include <cinttypes>

#define STK_SIZE sizeof(m_Stack)
#define ITER_SIZE sizeof(m_Iterator)
#define HASH_SIZE sizeof(uint32_t)
#define CANARY_SIZE sizeof(uint64_t)

static const char* LOG_FILENAME = "../ProtectedStack.log";
static const uint64_t CANARY_VALUE = 0x420BAD69;

enum STK_ERROR {
    E_ROOM = 1,
    E_NEQT = 2,
    E_PFE = 3,
    W_LODT = 4,
    E_STKEX = 5,
    E_BADPTR = 6,
    E_ZBUTEL = 7,
    E_NZBUTNEL = 8,
    E_STKTYPE = 9
};

#ifndef __SIZE_TYPE__
typedef uint32_t size_t;
#else
typedef __SIZE_TYPE__ size_t;
#endif

typedef uint8_t  byte;
typedef struct m_Iterator* Iterator;
typedef struct m_Stack* Stack;

typedef struct Invocation {
    const char* file;
    const char* function;
    int line;
} Invocation;

typedef struct m_Iterator {
    m_Iterator *prev;
    size_t      size;
} m_Iterator;

typedef struct m_Stack {
    Iterator top;
    size_t   type_size;
    size_t   size;
#ifdef STACK_USE_HASH
    uint32_t head_hash;
    uint32_t body_hash;
#endif
} m_Stack;

#endif //PROTECTED_STACK_STK_CONFIG_H
