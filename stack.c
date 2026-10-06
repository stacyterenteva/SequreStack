#include <stdio.h>

#ifdef DOUBLE_STACK

const double dove1 = 3.1415926;
const double dove2 = 2.718281828;


#else

char* dove1 = NULL;
char* dove2 = NULL;

#endif

#include "stack.h"


const double EPS = 1e-9;

int stack_init(stack_t* stk, int capacity)
{
    assert(stk);

    int err = 0;

    if (stk->size != 0 || stk->capacity != 0) {
        err = 2;
    }

    stk->data = (stack_elem_t*) calloc(capacity, sizeof(stack_elem_t));
    memset(stk->data, NAN, capacity * sizeof(stack_elem_t));

    stk->data[0] = dove1;
    stk->data[capacity - 1] = dove2;
    stk->info = stk->data + 1;

    stk->size = 1;
    stk->capacity = capacity;
    stk->hash = 0;

    if (stk->data == NULL) {
        err = 1;
    }
    return err;
}

void process_init_error(int err, FILE* report, const char* file, int line) {
    switch(err) {
        case 0:
            break;
        case 1:
            printf("Error during stack_init: no memory for stack\n");
            break;
        case 2: {
            char temp[100] = {};
            snprintf(temp, sizeof(temp) / sizeof(temp[0]), "%s:%d: warning: initialization of not empty stack\n", file, line);
            fputs(temp, report);
            break;
        }
        case 3: {
            char temp[100] = {};
            snprintf(temp, sizeof(temp) / sizeof(temp[0]), "%s:%d: initialization of NULL\n", file, line);
            fputs(temp, report);
            break;
        }
        default:
            printf("Error during stack_init: unknown error\n");
            break;
    }
    return;
}

int push(stack_t* stk, stack_elem_t value)
{
    assert(stk);

    stk->data[stk->size] = value;

    stk->hash += stk->size * value;

    (stk->size)++;
    if (stk->size >= stk->capacity) {

        //NOTE: github

        const size_t old_cap = stk->capacity * sizeof(stack_elem_t);
        const size_t new_cap = (stk->capacity * 2) * sizeof(stack_elem_t);

        stk->data = (stack_elem_t*) realloc(stk->data, new_cap);
        memset(stk->data + stk->size, 0, new_cap - old_cap);
        stk->capacity = stk->capacity * 2;
        stk->data[stk->capacity - 1] = dove2;
    }

    if (stk->data == NULL) {
        return 1;
    }

    assert(stk);

    return 0;
}

void process_push_error(int err)
{
    switch(err) {
        case 0:
            break;
        case 1:
            printf("Error during push: no memory for stack\n");
            break;
        case 2:
            printf("Error during stack_init: data in stack is damaged(left attack)\n");
            break;
        case 3:
            printf("Error during stack_init: data in stack is damaged(right attack)\n");
            break;
        default:
            printf("Error during push: unknown error");
            break;
    }
    return;
}

int pop(stack_t* stk, stack_elem_t* box)
{
    assert(stk);

    if (stk->size <= 1) {
        return 1;
    }

    *box = stk->data[stk->size - 1];

    stk->hash -= stk->size * stk->data[stk->size - 1];

    (stk->size)--;

    return 0;
}

void process_pop_error(int err)
{
    switch(err) {
        case 0:
            break;
        case 1:
            printf("Error during pop: you have reached the end of the stack\n");
            break;
        default:
            printf("Error during pop: unknown error\n");
    }
}

void stack_dump(stack_t stk, const char* name, const char* file, int line)
{
    assert(name);
    assert(file);

    printf("%s:%d\n", file, line);
    printf("capacity: %d\n", stk.capacity);
    printf("size: %d\n", stk.size);
    printf("hash: %lg\n", stk.hash);

    if (stk.capacity == 0) {
        return;
    }
    for (int i = 0; i < stk.capacity; i++) {
        printf("%s[%d] = %lg\n", name, i, stk.data[i]);
    }

    putchar('\n');
}


void is_stack_ok(stack_t stk, FILE* report, const char* file, int line)
{
    assert(report);
    assert(file);

    if (stk.capacity < 0) {
        char temp[100] = {};
        snprintf(temp, sizeof(temp) / sizeof(temp[0]), "%s:%d: error: negative capacity\n", file, line);
        fputs(temp, report);
        return;
    }

    if (stk.size < 0) {
        char temp[100] = {};
        snprintf(temp, sizeof(temp) / sizeof(temp[0]), "%s:%d: error: negative size\n", file, line);
        fputs(temp, report);
        return;
    }

    if (stk.capacity < stk.size) {
        char temp[100] = {};
        snprintf(temp, sizeof(temp) / sizeof(temp[0]), "%s:%d: error: capacity less than size\n", file, line);
        fputs(temp, report);
        return;
    }

    if (stk.data == NULL) {
        char temp[100] = {};
        snprintf(temp, sizeof(temp) / sizeof(temp[0]), "%s:%d: error: NULL pointer of stk.data\n", file, line);
        fputs(temp, report);
        return;
    }

    #ifdef DOUBLE_STACK

    if (!is_equal(stk.data[0], dove1)) {
        char temp[100] = {};
        snprintf(temp, sizeof(temp) / sizeof(temp[0]), "%s:%d: warning: data in stack start to change(left attack)\n", file, line);
        fputs(temp, report);
        return;
    }


    if (!is_equal(stk.data[stk.capacity - 1], dove2)) {
        char temp[100] = {};
        snprintf(temp, sizeof(temp) / sizeof(temp[0]), "%s:%d: warning: data in stack start to change(right attack)\n", file, line);
        fputs(temp, report);
        return;
    }

    double current_hash = 0;
    for (int i = 1; i <= stk.size; i++) {
        current_hash += i * stk.data[i];
    }

    if (!is_equal(current_hash, stk.hash)) {

        char temp[100] = {};
        snprintf(temp, sizeof(temp) / sizeof(temp[0]), "%s:%d: warning: data in stack start change\n", file, line);
        fputs(temp, report);
        return;
    }

    #endif
}

bool is_equal(double a, double b)
{
    return (fabs(a - b) < EPS);
}

int compare_less(const void* a, const void* b)
{
    assert(a);
    assert(b);

    int value_a = *(const int*) a;
    int value_b = *(const int*) b;

    if (value_a < value_b) {
        return 1;
    }
    else if (value_a > value_b) {
        return -1;
    }
    else {
        return 0;
    }

    assert(0 && "Unreachable");
}

void stack_destroy(stack_t* stk)
{
    assert(stk);

    free(stk->data);
    stk = NULL;
}


void my_resize(stack_t* stk, int n) // NOTE: должны ли такие функции разбираться с неправильными данными
{
    assert(stk);

    stk->info = (stack_elem_t*) realloc(stk->data, (n + 2) * sizeof(stack_elem_t));
    stk->capacity = n + 2;
    if (stk->size >= stk->capacity) {
        stk->size = stk->capacity - 1;
    }

    stk->data[stk->capacity - 1] = dove2;

    double current_hash = 0;
    for (int i = 1; i <= stk->size; i++) {
        current_hash += i * stk->data[i];
    }

    stk->hash = current_hash;
}




