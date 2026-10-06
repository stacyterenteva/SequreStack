#ifndef STACK_H
#define STACK_H


#define INIT_CHECK(err, report) process_init_error(err, report, __FILE__, __LINE__);
#define STACK_CHECK(stk, report) is_stack_ok(stk, report, __FILE__, __LINE__);
#define STACK_DUMP(stk) stack_dump(stk, "stk", __FILE__, __LINE__);

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef DOUBLE_STACK

typedef double stack_elem_t;

#else

typedef char* stack_elem_t;

#endif

struct stack_t
{
    stack_elem_t* data;
    int size;
    int capacity;
    stack_elem_t* info;
    stack_elem_t hash;
};

int stack_init(stack_t* stk, int capacity);
void process_init_error(int err, FILE* report, const char* file, int line);
int push(stack_t* stk, stack_elem_t value);
void process_push_error(int err);
int pop(stack_t* stk, stack_elem_t* x);
void stack_dump(stack_t stk, const char* name, const char* file, int line);
void is_stack_ok(stack_t stk, FILE* report, const char* file, int line);
bool is_equal(double a, double b);
int compare_less(const void* a, const void* b);
void process_pop_error(int err);
void stack_destroy(stack_t* stk);
void my_resize(stack_t* stk, int n);


#endif /* STACK_H */
