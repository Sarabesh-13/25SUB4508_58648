// observe layout of data in memory using gdb

#include <stdio.h>
#include <stdlib.h>

//defining constants
#define CONST_INT 500
#define CONST_FLOAT 600.5

//global variables
int g_var = 100;
float g_float = 200.5;

//static variables
static int s_var = 300;
static float s_float = 400.5;

int main() {
    //local variables
    int l_var = 700;
    float l_float = 800.5;

    //defining constants
    const int c_var = 900;
    const float c_float = 500.5;
    const int a = CONST_INT;
    const float b = CONST_FLOAT;

    printf("Address of g_var: %p\n", (void*)&g_var);
    printf("Address of g_float: %p\n", (void*)&g_float);
    printf("Address of s_var: %p\n", (void*)&s_var);
    printf("Address of s_float: %p\n", (void*)&s_float);
    printf("Address of l_var: %p\n", (void*)&l_var);
    printf("Address of l_float: %p\n", (void*)&l_float);
    printf("Address of c_var: %p\n", (void*)&c_var);
    printf("Address of c_float: %p\n", (void*)&c_float);
    printf("Address of CONST_INT: %p\n", (void*)&a);
    printf("Address of CONST_FLOAT: %p\n", (void*)&b);
    return 0;
}