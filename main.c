#include <stdio.h>
#include "calc.h"

int main()
{
    stack_t stk1 = {};
    stack_init(&stk1, 5);

    push(&stk1, 20);
    push(&stk1, 30);

    add(&stk1);

    push(&stk1, 8);
    push(&stk1, 3);

    sub(&stk1);

    div(&stk1);

    double x = 0;
    pop(&stk1, &x);

    printf("%lg\n", x);
}
