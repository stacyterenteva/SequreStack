#include "calc.h"

void add(stack_t* stk)
{
    double value = stk->data[stk->size - 1] + stk->data[stk->size - 2];
    printf("%lg\n", value);
    stk->data[stk->size - 2] = value;
    stk->data[stk->size - 1] = 0;
    stk->size--;
}

void sub(stack_t* stk)
{
    double value = stk->data[stk->size - 2] - stk->data[stk->size - 1];
    printf("%lg\n", value);
    stk->data[stk->size - 2] = value;
    stk->data[stk->size - 1] = 0;
    stk->size--;
}

void div(stack_t* stk)
{
    if (is_equal(stk->data[stk->size - 1], 0)) {
        printf("ERROR: division by zero");
        return;
    }

    double value = stk->data[stk->size - 2] / stk->data[stk->size - 1];
    printf("%lg\n", value);
    stk->data[stk->size - 2] = value;
    stk->data[stk->size - 1] = 0;
    stk->size--;
}


