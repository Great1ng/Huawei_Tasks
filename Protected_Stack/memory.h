#ifndef PROTECTED_STACK_MEMORY_H
#define PROTECTED_STACK_MEMORY_H

#include <unistd.h>
#include <sys/mman.h>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <cstring>

const size_t MIN_BLOCK_SIZE = (size_t)sysconf(_SC_PAGE_SIZE);

struct stack {
    void *data;
    size_t capacity;
    size_t size;
};

typedef struct stack *Stack;

Stack construct_stack();

Stack stack_construct();

void push_stack(Stack instance, int value) __nonnull((1));

void stack_push(Stack instance, int value);

int top_stack(Stack instance) __nonnull((1));

int stack_top(Stack instance);

void pop_stack(Stack instance) __nonnull((1));

void destruct_stack(Stack instance) __nonnull((1));

void stack_destruct(Stack instance);

#endif //PROTECTED_STACK_MEMORY_H
