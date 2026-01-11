//program for creating template function to return element less than target element in array
#include<iostream>
#include<iomanip>

using namespace std;

template <typename T1,typename T2>
int count_total(T1*,int,T2);

int main(int argc,char* argv[])
{
    int n_arr[3]={1,2,3};
    float f_arr[4]={1.0,2.0,3.0,4.0};
    char c_arr[6]={'h','e','l','l','o','\n'};
    cout<<count_total(n_arr,3,5)<<endl;
    cout<<count_total(f_arr,4,7.7)<<endl;
    cout<<count_total(c_arr,6,'z')<<endl;
    return 0;
}

template <typename T1,typename T2>
int count_total(T1* arr,int size,T2 target)
{
    int count=0;
    for(int i=0;i<size;i++)
    {
       if(arr[i]<target)
       {
        count+=1;
       }
    }
    return count;
}
