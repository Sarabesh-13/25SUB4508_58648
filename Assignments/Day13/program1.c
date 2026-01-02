//program for 1d,2d array and string creation and inspect their memory address using gdb
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int arr[10]={1,2,3,4}; //1d array
    int arr1[3][3]={1,2,3,4,5,6,7,8,9}; //2d array
    char str[20]="hello world"; //1d array
    char str1[4][20]={"gfg","accompany","udemy","coursera"}; //2d array
    return 0;
}