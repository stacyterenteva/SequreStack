#include "calc.h"

void add(stack_t* stk)
{
    if (stk->size - 2 < 1) {
        printf("ERROR during add\n");
    }
    double value = stk->data[stk->size - 1] + stk->data[stk->size - 2];
    stk->data[stk->size - 2] = value;
    stk->data[stk->size - 1] = 0;
    stk->size--;
}

void sub(stack_t* stk)
{
    if (stk->size - 2 < 1) {
        printf("ERROR during sub\n");
    }
    double value = stk->data[stk->size - 2] - stk->data[stk->size - 1];
    stk->data[stk->size - 2] = value;
    stk->data[stk->size - 1] = 0;
    stk->size--;
}

void div(stack_t* stk)
{
    if (stk->size - 2 < 1) {
        printf("ERROR during sub\n");
    }

    if (is_equal(stk->data[stk->size - 1], 0)) {
        printf("ERROR: division by zero");
        return;
    }

    double value = stk->data[stk->size - 2] / stk->data[stk->size - 1];
    stk->data[stk->size - 2] = value;
    stk->data[stk->size - 1] = 0;
    stk->size--;
}


