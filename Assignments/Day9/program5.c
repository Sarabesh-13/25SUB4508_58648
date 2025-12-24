// program to replace zeroes with ones in an array

#include <stdio.h>
#define SIZE 10

void replaceZeroesWithOnes(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            arr[i] = 1;
        }
    }
}

int main() {
    int arr[SIZE] = {0, 2, 3, 0, 5, 0, 7, 8, 0, 10};

    printf("Original array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    replaceZeroesWithOnes(arr, SIZE);

    printf("Array after replacing zeroes with ones:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}