//print very big c alphabet with 9 rows and 10 columns

#include <stdio.h>

int main() {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 10; j++) {
            if ((i == 0 || i == 8) && (j > 0 && j < 9)) {
                printf("*");
            }
            else if ((j == 0) && (i > 0 && i < 8)) {
                printf("*");
            } 
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
    
}