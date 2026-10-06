#include <stdio.h>
#include "calc.h"

int main()
{
    stack_t stk1 = {};
    stack_init(&stk1, 5);

    int program[] = {1, 20, 1, 30, 2, 1, 8, 1, 3, 3, 4, 5};
    double answer = 0;
    for (size_t pc = 0; pc < sizeof(program) / sizeof(int); pc++) {
        switch(program[pc]) {
            case 1:
                push(&stk1, program[++pc]);
                break;
            case 2:
                add(&stk1);
                break;
            case 3:
                sub(&stk1);
                break;
            case 4:
                div(&stk1);
                break;
            case 5:
                pop(&stk1, &answer);
                break;
            default:
                printf("ERROR: unknown comand\n");
                break;
        }
    }
    printf("%lg\n", answer);
}
