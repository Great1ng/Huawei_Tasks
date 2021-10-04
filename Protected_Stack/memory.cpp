#include "memory.h"

static void *mem_request(size_t size) {
    void *mem_ptr;
    if (posix_memalign(&mem_ptr, MIN_BLOCK_SIZE, size) != 0)
        return nullptr;

    return mem_ptr;
}

static void *cmem_request(size_t size) {
    return malloc(size);
}

Stack construct_stack() {
    size_t stk_size = sizeof(struct stack);
    Stack instance = (Stack) mem_request(stk_size);

    instance->data = nullptr;
    instance->capacity = 0;
    instance->size = 0;

    mprotect(instance, stk_size, PROT_READ);

    return instance;
}

Stack stack_construct() {
    size_t stk_size = sizeof(struct stack);
    Stack instance = (Stack) mem_request(stk_size);

    instance->data = nullptr;
    instance->capacity = 0;
    instance->size = 0;

    if (mprotect(instance, stk_size, PROT_READ) == -1) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return nullptr;
    }

    return instance;
}

void push_stack(Stack instance, int value) {
    size_t stk_size = sizeof(struct stack);
    int op_stat = 0;
    op_stat = mprotect(instance, stk_size, PROT_READ | PROT_WRITE);
    if (op_stat == -1) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return;
    }
    op_stat = mprotect(instance->data, instance->size, PROT_READ | PROT_WRITE);
    if (op_stat == -1) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return;
    }

    //todo aligned reallocation

    if (instance->capacity > 0) {
        instance->size++;
        ((int*)instance->data)[instance->size-1] = value;
        instance->capacity--;
        return;
    }

    instance->capacity += 7;
    void* tmp = instance->data;
    instance->data = mem_request((instance->size+instance->capacity+1) * sizeof(int));
    memcpy(instance->data, tmp, instance->size*sizeof(int));
    free(tmp);
    if (!instance->data) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return;
    }
    instance->size++;
    ((int*)instance->data)[instance->size - 1] = value;

    op_stat = mprotect(instance, stk_size, PROT_READ);
    if (op_stat == -1) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return;
    }
    op_stat = mprotect(instance->data, instance->size, PROT_READ);
    if (op_stat == -1) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return;
    }
}

void stack_push(Stack instance, int value) {
    size_t stk_size = sizeof(struct stack);
    int op_stat = 0;
    op_stat = mprotect(instance, stk_size, PROT_READ | PROT_WRITE);
    if (op_stat == -1) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return;
    }
    if (instance->data) {
        op_stat = mprotect(instance->data, instance->size, PROT_READ | PROT_WRITE);
        if (op_stat == -1) {
            fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
            return;
        }
    } else {
        instance->capacity = 8;
        instance->data = mem_request(instance->capacity * sizeof(int));
    }

    instance->size++;
    if (instance->capacity > 0) {
        ((int*)instance->data)[instance->size - 1] = value;
        instance->capacity--;
        return;
    }

    instance->capacity += 7;
    instance->data = realloc(instance->data, (instance->size+instance->capacity) * sizeof(int));
    if (!instance->data) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return;
    }
    ((int*)instance->data)[instance->size - 1] = value;

    op_stat = mprotect(instance, stk_size, PROT_READ);
    if (op_stat == -1) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return;
    }
    op_stat = mprotect(instance->data, instance->size, PROT_READ);
    if (op_stat == -1) {
        fprintf(stderr, "%s %d\n", strerror(errno), __LINE__);
        return;
    }
}

int top_stack(Stack instance) {
    return ((int*)instance->data)[instance->size - 1];
}

int stack_top(Stack instance) {
    return ((int*)instance->data)[instance->size - 1];
}

void pop_stack(Stack instance) {
    size_t stk_size = sizeof(struct stack);
    mprotect(instance, stk_size, PROT_READ | PROT_WRITE);
    mprotect(instance->data, instance->size, PROT_READ | PROT_WRITE);

    instance->size--;

    mprotect(instance, stk_size, PROT_READ);
    mprotect(instance->data, instance->size, PROT_READ);
}

void destruct_stack(Stack instance) {
    size_t stk_size = sizeof(struct stack);

    mprotect(instance, stk_size, PROT_READ | PROT_WRITE);
    mprotect(instance->data, instance->size, PROT_READ | PROT_WRITE);

    free(instance->data);
    free(instance);
}

void stack_destruct(Stack instance) {
    size_t stk_size = sizeof(struct stack);

    mprotect(instance, stk_size, PROT_READ | PROT_WRITE);
    mprotect(instance->data, instance->size, PROT_READ | PROT_WRITE);

    free(instance->data);
    free(instance);
}