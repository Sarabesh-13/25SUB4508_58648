/*
Task 1H: Use predefined macros in a printf and observe the output. 
Use these to write a logging macro, which when called logs the function name and line number in the log output.
*/

#include <stdio.h>
#define LOG(msg) printf("LOG: %s:%d: %s\n", __func__, __LINE__, msg)

void exampleFunction() {
    LOG("This is a log message from exampleFunction.");
}
