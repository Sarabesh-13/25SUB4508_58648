/*
Task-1G: Define a function operation() which should take a function pointer and 2 more arguments. 
Define add, subtrack, multiply and divide as functions. 
Pass one of these functions to operation() with other  two arguments and check correct function gets called. 
*/

#include <stdio.h>
typedef int (*operation_func)(int, int);

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b != 0)
        return a / b;
    else {
        printf("Error: Division by zero\n");
        return 0;
    }
}

int operation(operation_func func, int x, int y) {
    return func(x, y);
}


int main() {
    int a = 10, b = 5;

    printf("Addition: %d\n", operation(add, a, b));
    printf("Subtraction: %d\n", operation(subtract, a, b));
    printf("Multiplication: %d\n", operation(multiply, a, b));
    printf("Division: %d\n", operation(divide, a, b));

    return 0;
}