#include "stack.h"

static bool LOG_IS_CLEAR = false;

/*
1 : "Run out of memory"
2 : "Not equal types"
3 : "Pop from empty"
4 : "Lose of data"
5 : "STACK DOES NOT EXIST"
6 : "CAN NOT READ STACK"
7 : "STACK HAS ZERO SIZE, BUT HAVE ELEMENTS"
8 : "STACK IS NOT ZERO SIZE, BUT HAS NO ELEMENTS"
9 : "STACK ELEMENT HAS ZERO LENGTH TYPE"
*/


Stack m_StackConstruct (size_t typeSize, Invocation invoke)
{
    Stack instance = (Stack) malloc(STK_SIZE);

    if (!instance) {
        m_StackDump(instance, invoke, E_ROOM);
        return nullptr;
    }

    instance->top = nullptr;
    instance->type_size = typeSize;
    instance->size = 0;

#ifdef STACK_USE_HASH
    instance->head_hash = 0;
    instance->body_hash = 0;
    size_t stack_without_hash = (size_t)((location)&instance->head_hash - (location)instance);
    OAT_Hash(&instance->head_hash, instance, stack_without_hash);
#endif

    return instance;
}

void m_StackPush (Stack instance, const void* ptr, size_t valueSize, Invocation invoke)
{
//    if (!m_StackIsCorrect(instance, invoke))
//        return;

    if (valueSize != instance->type_size) {
        m_StackDump(instance, invoke, E_NEQT);
        return;
    }

    void* block = malloc(ITER_SIZE + valueSize);

    if (!block) {
        m_StackDump(instance, invoke, E_ROOM);
        return;
    }

    Iterator iter = (Iterator) block;
    byte* data = (byte*)block + ITER_SIZE;

    memmove(data, ptr, valueSize);
    iter->prev = nullptr;
    iter->size = valueSize;

    if (instance->size)
        iter->prev = instance->top;

    instance->top = iter;
    instance->size++;

#ifdef STACK_USE_HASH
    instance->head_hash = 0;
    size_t stack_without_hash = (size_t)((location)&instance->head_hash - (location)instance);
    OAT_Hash(&instance->head_hash, instance, stack_without_hash);
    OAT_Hash(&instance->body_hash, instance->last, sizeof(m_Iterator) + instance->last->type);
#endif

//    m_StackIsCorrect(instance, invoke);
}

void m_StackPop (Stack instance, void* ptr, size_t valueSize, Invocation invoke)
{
//    if (!m_StackIsCorrect(instance, invoke))
//        return;

    if (!instance->size) {
        m_StackDump(instance, invoke, E_PFE);
        return;
    }

    if (valueSize != instance->type_size) {
        m_StackDump(instance, invoke, E_NEQT);
        return;
    }

    if (!ptr) {
        m_StackDump(instance, invoke, W_LODT);
    } else {
        memmove(ptr, instance->top + 1, instance->type_size);
    }

    Iterator prev = instance->top->prev;
    free(instance->top);
    instance->top = prev;
    instance->size--;

#ifdef STACK_USE_HASH
    instance->head_hash = 0;
    instance->body_hash = 0;
    size_t stack_without_hash = (size_t)((location)&instance->head_hash - (location)instance);
    OAT_Hash(&instance->head_hash, instance, stack_without_hash);

    Iterator current = instance->last;
    while (current) {
        OAT_Hash(&instance->body_hash, current, sizeof(m_Iterator) + current->type);
        current = current->prev;
    }
#endif

//    m_StackIsCorrect(instance, invoke);
}

bool m_StackIsCorrect (Stack instance, Invocation invoke)
{
    if (!instance) {
        m_StackDump(instance, invoke, E_STKEX);
        return false;
    }

    if (IsBadReadPtr(instance, STK_SIZE)) {
        m_StackDump(instance, invoke, E_BADPTR);
        return false;
    }

    if (!instance->size && instance->top) {
        m_StackDump(instance, invoke, E_ZBUTEL);
        return false;
    }

    if (instance->size && !instance->top) {
        m_StackDump(instance, invoke, E_NZBUTNEL);
        return false;
    }

    if (!instance->top) return true;

    if (IsBadReadPtr(instance->top, ITER_SIZE)) {
        m_StackDump(instance, invoke, E_BADPTR);
        return false;
    }

    if (IsBadReadPtr(instance->top+1, instance->type_size)) {
        m_StackDump(instance, invoke, E_BADPTR);
        return false;
    }

    if (!instance->type_size) {
        m_StackDump(instance, invoke, E_STKTYPE);
        return false;
    }

#ifdef STACK_USE_HASH
    uint32_t head_hash = 0;
    uint32_t body_hash = 0;
    size_t stack_without_hash = (size_t)((location)&instance->head_hash - (location)instance);
    OAT_Hash(&head_hash, instance, stack_without_hash);

    Iterator current = instance->last;
    while (current) {
        OAT_Hash(&body_hash, current, sizeof(m_Iterator) + current->type);
        current = current->prev;
    }

    if (head_hash != instance->head_hash) {
        m_StackDump(instance, function, line, "STACK HEAD HASH IS NOT CORRECT");
        return false;
    }

    if (body_hash != instance->body_hash) {
        m_StackDump(instance, function, line, "STACK BODY HASH IS NOT CORRECT");
        return false;
    }
#endif

    return true;
}

void m_StackDump (Stack instance, Invocation invoke, STK_ERROR error)
{
    if (!LOG_IS_CLEAR) {
        FILE* log = fopen(LOG_FILENAME, "w");
        assert (log && "CAN NOT OPEN LOG FILE");
        time_t cur_time = time(nullptr);
        fprintf(log, "<<< TIME >>>\n");
        fprintf(log, "!LOCAL --> %s",   ctime(&cur_time));
        fprintf(log, "!UTC   --> %s\n", asctime(gmtime(&cur_time)));
        assert(fclose(log) != EOF && "CAN NOT CLOSE LOG FILE");
        LOG_IS_CLEAR = true;
    }

    FILE* log = fopen(LOG_FILENAME, "a");
    assert (log && "CAN NOT OPEN LOG FILE");

    fprintf(log, "<<< DUMP >>>\n");
    fprintf(log, "!CALLED IN --> \"%s\"\n", invoke.file);
    fprintf(log, "!CALLED BY --> \"%s\"\n", invoke.function);
    fprintf(log, "!CALLED ON --> line:%d\n", invoke.line);
    fprintf(log, "!ERROR     --> %d\n", error);

    fprintf(log, "<<< STACK >>>\n");

    if (!instance) {
        assert(fclose(log) != EOF && "CAN NOT CLOSE LOG FILE");
        return;
    }

    fprintf(log, "!ADDRESS      --> %p\n", instance);

    if (IsBadReadPtr(instance, STK_SIZE)) {
        fprintf(log, "\n");
        assert(fclose(log) != EOF && "CAN NOT CLOSE LOG FILE");
        return;
    }

    fprintf(log, "!TYPE_SIZE    --> %lu\n", instance->type_size);
    fprintf(log, "!SIZE         --> %lu\n", instance->size);
#ifdef STACK_USE_HASH
    fprintf(log, "!HEAD HASH    --> %x\n", instance->head_hash);
    fprintf(log, "!BODY HASH    --> %x\n", instance->body_hash);
#endif

    fprintf(log, "<<< ELEMENTS >>>\n");
    if (!instance->top) {
        fprintf(log, "\n");
        assert(fclose(log) != EOF && "CAN NOT CLOSE LOG FILE");
        return;
    }

    Iterator current = instance->top;
    while (current) {
        fprintf(log, "!ADDRESS      --> %p \n", current);

        if (IsBadReadPtr(current, ITER_SIZE)) {
            fprintf(log, "#CAN NOT READ FROM STACK ELEMENT\n\n");
            assert(fclose(log) != EOF && "CAN NOT CLOSE LOG FILE");
            return;
        }

        fprintf(log, "!PREV_ADDRESS --> %p\n", current->prev);
        current = current->prev;
    }
    fprintf(log, "\n");

    assert(fclose(log) != EOF && "CAN NOT CLOSE LOG FILE");
}

void m_StackDestruct (Stack* ptr, Invocation invoke)
{
    if (!ptr) {
        m_StackDump(nullptr, invoke, E_STKEX);
        return;
    }

    if (IsBadReadPtr(ptr, sizeof(Stack))) {
        m_StackDump(nullptr, invoke, E_BADPTR);
        return;
    }

    Stack instance = *ptr;

    if (!m_StackIsCorrect(instance, invoke))
        return;

    Iterator current = instance->top;
    while (current) {
        Iterator prev = current->prev;
        free(current);
        current = prev;
    }

    free(instance);
    *ptr = nullptr;
}