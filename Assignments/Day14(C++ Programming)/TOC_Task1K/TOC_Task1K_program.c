/*
Task 1K: Use #pragma pack directive with a structure and observe the data layout in memory using gdb.
*/

#include <stdio.h>
#pragma pack(1) // Set packing alignment to 1 byte

struct demo
{
    char gender;
    int id;
};


int main()
{
    struct demo d;
    d.gender = 'M';
    d.id = 12345;
    printf("Gender: %c, ID: %d\n", d.gender, d.id);
    printf("Size of struct demo: %zu bytes\n", sizeof(struct demo)); 
    return 0;
}