#include <stdio.h>
#include <sys/stat.h>
#include <malloc.h>
#include <assert.h>

char** make_index_array(char* text, size_t size);
int my_strchr(const char* string, char ch);

int main(int argc, char* argv[])
{
    if (argc == 1) {
        printf("No file for compilation\n");
    }
    else if (argc == 2) {
        char* file_name = argv[1];
    }
    else {
        printf("Too many files\n");
    }

    char* file_name = argv[1];
    FILE* program_asm = fopen(file_name, "r");

    struct stat file_inf = {};
    stat(file_name, &file_inf);

    char* text = (char*) calloc(file_inf.st_size + 1, sizeof(char));
    fread(text, file_inf.st_size + 1, sizeof(char), program_asm);
    char** program = make_index_array(text, file_inf.st_size + 1);

    for (int i = 0; i < 11; i++) {
        printf("num %d, line: <%s>\n", i, program[i]);
    }

    FILE* program_exe = fopen("program.txt", "w");
    for (int i = 0; i < 11; i++) {
        if (my_strchr(program[i], ' ') != -1) {
            int value = 0;
            char str[100];
            sscanf(program[i], "%s%d", str, &value);
            fprintf(program_exe, "%d\n", 1);
            fprintf(program_exe, "%d\n", value);
        }
        else {
            if (strcmp(program[i], "ADD") == 0) {
                fprintf(program_exe, "%d\n", 2);
            }
            else if (strcmp(program[i], "SUB") == 0) {
                fprintf(program_exe, "%d\n", 3);
            }
            else if (strcmp(program[i], "DIV") == 0) {
                fprintf(program_exe, "%d\n", 4);
            }
            else if (strcmp(program[i], "OUT") == 0) {
                fprintf(program_exe, "%d\n", 5);
            }

            else if (strcmp(program[i], "HLT") == 0) {
                fprintf(program_exe, "%d\n", 0);
            }
        }
    }
}

char** make_index_array(char* text, size_t size)
{
    assert(text);

    char** index = (char**) calloc(size, sizeof(char*));
    int line_num = 0;
    index[line_num] = text;
    line_num++;

    for (size_t i = 0; i < size; i++) {
        if (text[i] == '\n') {
            text[i] = '\0';
            index[line_num] = text + i + 1;
            line_num++;
        }
    }
    return index;
}

int my_strchr(const char* string, char ch)
{
    assert(string);
    int i = 0;
    for (i = 0; string[i] != '\0' && string[i] != ch; i++) {
        ;
    }
    if (string[i] == ch) {
        return i;
    }
    else {
        return -1;
    }
}


