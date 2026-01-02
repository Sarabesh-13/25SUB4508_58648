/*
Task 1J: Use #ifdef directive in a header file to make it get included only once in a C file. 
Create a header file "myheader.h" with a function prototype for a function that prints "Hello, World!" to the console. 
Implement this function in a C file "program9.c" and include the header file using the #include directive. Ensure that the header file is protected against multiple inclusions using the #ifdef directive.
*/

#ifndef MYHEADER_H
#define MYHEADER_H

void printHelloWorld();

#endif 

// MYHEADER_H