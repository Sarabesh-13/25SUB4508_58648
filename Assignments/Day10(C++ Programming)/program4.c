//program for hexadecimal to decimal conversion

#include <stdio.h>
#include <string.h>
#include <math.h>

long long convertHexToDecimal(char hex[]) {
    int length = strlen(hex);
    long long decimal_num = 0;
    int base = 1; 
    for (int i = length - 1; i >= 0; i--) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            decimal_num += (hex[i] - '0') * base;
        } 
        else if (hex[i] >= 'A' && hex[i] <= 'F') {
            decimal_num += (hex[i] - 'A' + 10) * base;
        } 
        else if (hex[i] >= 'a' && hex[i] <= 'f') {
            decimal_num += (hex[i] - 'a' + 10) * base;
        }
        base *= 16; 
    }
    return decimal_num;
}

int main() {
    char hex[20];
    printf("Enter a hexadecimal number: ");
    scanf("%s", hex);
    long long decimal = convertHexToDecimal(hex);
    printf("Decimal equivalent: %lld\n", decimal);
    return 0;
}