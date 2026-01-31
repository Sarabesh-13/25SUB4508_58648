//program for creating template accepting any array and find elements greater than given value
#include<iostream>
#include<cstdlib>
#define size 50;

using namespace std;

template <typename T>
int countgreater(T arr[],int s,T value)
{
    int c=0;
    for(int i=0;i<s;i++)
    {
        if(arr[i]>value)
        {
           c+=1;
        }
    }
    return c;
}
int main()
{
    int arr[5] = {0, 1, 2, 7, 7};
    cout << countgreater(arr, 5, 5) << endl;
    double arr1[5] = {10.4, 11.5, 997.7, 456.4, 345.6};
    cout << countgreater(arr1, 5, 500.0) << endl;
    return 0;
}