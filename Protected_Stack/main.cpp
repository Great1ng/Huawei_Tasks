#include <csignal>
#include <cstdio>

//#define ALIGNED

#include "memory.h"

#define handle_error(msg) \
           do { perror(msg); _exit(1); } while (0)

static void handler(int sig, siginfo_t *si, void *unused) {
    printf("Got SIGSEGV at address: %p\n", si->si_addr);
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa = {};

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
    if (sigaction(SIGSEGV, &sa, nullptr) == -1)
        handle_error("sigaction");

#ifdef ALIGNED
    Stack stack = construct_stack();
    push_stack(stack, 100);
    for (int i = 0; i < 100000; i++)
        push_stack(stack, i);
    destruct_stack(stack);
#else
    Stack stack = stack_construct();
    stack_push(stack, 100);
    for (int i = 0; i < 50; i++)
        stack_push(stack, i);

    stack_destruct(stack);
#endif


    return 0;
}
