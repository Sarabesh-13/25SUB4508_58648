//remove duplicates from an array

#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

int main()
{
    int n, i, j, k;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[MAX_SIZE]; 

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
       scanf("%d", &arr[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; ) {
            if (arr[i] == arr[j]) {
                for (k = j; k < n - 1; k++) {
                    arr[k] = arr[k + 1];
                }
                n--; 
            } else {
                j++;
            }
        }
    }
    printf("Array after removing duplicates:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}