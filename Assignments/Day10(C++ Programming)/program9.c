//rotate array cyclically to the right by k positions

#include <stdio.h>


int main()
{
    int n, k;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number of positions to rotate: ");
    scanf("%d", &k);
    
    k = k % n; 
    int temp[n];

    for (int i = 0; i < k; i++) {
        temp[i] = arr[n - k + i]; 
    }
    for (int i = k; i<n; i++) { 
        temp[i] = arr[i - k]; 
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }

    printf("Array after rotation:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}