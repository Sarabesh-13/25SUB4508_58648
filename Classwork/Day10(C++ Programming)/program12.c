//program for prime numbers from 1 to 200 using sieve of eratosthenes

#include <stdio.h>
#include <stdbool.h>
#define MAX 200

int main() {
    bool isPrime[MAX + 1];
    for (int i = 0; i <= MAX; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false; 

    for (int p = 2; p * p <= MAX; p++) {
        if (isPrime[p]) {
            for (int multiple = p * p; multiple <= MAX; multiple += p) {
                isPrime[multiple] = false;
            }
        }
    }

    printf("Prime numbers from 1 to %d are:\n", MAX);
    for (int i = 2; i <= MAX; i++) {
        if (isPrime[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}