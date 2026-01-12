/*
    Task 10 write a template function to compare and return larger values of it
*/
#include<iostream>
#include<iomanip>


using namespace std;

template <typename T>
auto compare_values(const T& a,const T& b)
{
    return (a>b)?(a):(b);
}

int main(int argc,char* argv[])
{
    int a=2,b=3;
    cout<<"larger of int type->"<<compare_values(a,b)<<endl;
    float n1=7.0,n2=97.6;
    cout<<"larger of float type->"<<compare_values(n1,n2)<<endl;
    string s1="abc",s2="abcd";
    cout<<"larger of string type->"<<compare_values(s1,s2)<<endl;
    return 0;
}