#ifndef PROTECTED_STACK_STACK_H
#define PROTECTED_STACK_STACK_H

#include <malloc.h>
#include <cstring>
#include <cassert>
#include <ctime>

#include "stk-config.h"
#include "hash.h"
#include "utils.h"

#define STANDARD_INVOKE {__FILE__, __PRETTY_FUNCTION__, __LINE__}

#define StackConstruct(typeSize) \
    m_StackConstruct ((typeSize), STANDARD_INVOKE)

#define StackPush(instance, value) ({ \
    typeof(value) element = (value);            \
    m_StackPush ((instance), &element, sizeof(element), STANDARD_INVOKE); \
})

#define StackPop(instance, value) ({ \
    m_StackPop ((instance), value, sizeof(typeof(*(value))), STANDARD_INVOKE); \
})

#define StackIsCorrect(instance) \
    m_StackIsCorrect ((instance), STANDARD_INVOKE)

#define StackDump(instance, error) \
    m_StackDump ((instance), STANDARD_INVOKE, (error))

#define StackDestruct(ptr) \
    m_StackDestruct ((ptr), STANDARD_INVOKE)


Stack m_StackConstruct (size_t typeSize, Invocation invoke);

void m_StackPush       (Stack instance, const void* ptr, size_t valueSize, Invocation invoke);

void m_StackPop        (Stack instance, void* ptr, size_t valueSize, Invocation invoke);

bool m_StackIsCorrect  (Stack instance, Invocation invoke);

void m_StackDump       (Stack instance, Invocation invoke, STK_ERROR error);

void m_StackDestruct   (Stack* ptr, Invocation invoke);

#endif //PROTECTED_STACK_STACK_H
