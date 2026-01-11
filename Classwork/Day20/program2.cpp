//program for creating function template for swaping values of any type.
#include<iostream>
#include<cstdlib>

using namespace std;

template <typename T> //typename||class
void swap_sw(T& a,T& b)
{
    // cout<<typeid(T).name()<<endl;
    // cout<<typeid(a).name()<<endl;
    T t=a;
    a=b;
    b=t;
}

template <typename T1,typename T2>
auto add(T1& a, T2& b)//->decltype(a,b)
{
    return a+b;
}

int main()
{
    int a=10,b=20;
    swap_sw(a,b);
    cout<<a<<" "<<b<<endl;
    float a1=2.0,b1=3.0;
    swap_sw(a1,b1);
    cout<<a1<<" "<<b1<<endl;
    string s="ab";
    string k="ba";
    swap_sw(s,k);
    cout<<s<<" "<<k<<endl;
    int n1=10;
    float n2=20.5;
    cout<<add(n1,n2)<<endl;
    cout<<add(n2,n1)<<endl;
}