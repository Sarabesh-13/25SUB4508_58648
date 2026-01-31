// observe layout of data in memory using gdb
#include <stdio.h>
#include <stdlib.h>

//defining constants
#define CONST_INT 500
#define CONST_FLOAT 600.5

//global variables
int global_variable = 100;
float global_float = 200.5;

//static variables
static int static_variable = 300;
static float static_float = 400.5;

int main() {
    //local variables
    int local_variable = 700;
    float local_float = 800.5;

    //defining constants
    const int constant_variable = 900;
    const float constant_float = 500.5;
    const int a = CONST_INT;
    const float b = CONST_FLOAT;

    printf("Address of global_variable: %p\n", (void*)&global_variable);
    printf("Address of global_float: %p\n", (void*)&global_float);
    printf("Address of global static_variable: %p\n", (void*)&static_variable);
    printf("Address of global static_float: %p\n", (void*)&static_float);
    printf("Address of local_variable: %p\n", (void*)&local_variable);
    printf("Address of local_float: %p\n", (void*)&local_float);
    printf("Address of constant_var: %p\n", (void*)&constant_variable);
    printf("Address of constant_float: %p\n", (void*)&constant_float);
    printf("Address of Macro CONST_INT: %p\n", (void*)&a);
    printf("Address of Macro CONST_FLOAT: %p\n", (void*)&b);
    return 0;
}