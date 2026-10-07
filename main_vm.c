#include <stdio.h>
#include "calc.h"

int main()
{
    stack_t stk1 = {};
    stack_init(&stk1, 5);

    int program[16] = {};
    FILE* program_exe = fopen("program.txt", "r");
    for (int i = 0; i < 16; i++) {
        fscanf(program_exe, "%d", &program[i]);
    }

    double answer = 0;
    for (size_t pc = 0; program[pc] != 0; pc++) {
        switch(program[pc]) {
            case 1:
                push(&stk1, program[++pc]);
                STACK_DUMP(stk1);
                break;
            case 2:
                add(&stk1);
                STACK_DUMP(stk1);
                break;
            case 3:
                sub(&stk1);
                STACK_DUMP(stk1);
                break;
            case 4:
                div(&stk1);
                STACK_DUMP(stk1);
                break;
            case 5:
                pop(&stk1, &answer);
                STACK_DUMP(stk1);
                break;
            default:
                printf("ERROR: unknown comand\n");
                break;
        }
    }
    printf("%lg\n", answer);
}
