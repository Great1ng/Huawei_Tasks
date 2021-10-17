#define STACK_USE_HASH

#include "stack.h"

int main() {
    Stack stack = StackConstruct(sizeof(int));

    for (int i = 0; i < 10000000; i++) {
        StackPush(stack, i);
    }

    int res;
    for (int i = 0; i < 10000000; i++) {
        StackPop(stack, &res);
    }

    StackDestruct(&stack);

    return 0;
}