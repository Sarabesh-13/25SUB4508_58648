//program to demonstrate default arguments in functions
#include<iostream>
#include<iomanip>

using namespace std;

void sum(int a,int b=5)
{
    cout<<"the sum is->"<<a+b<<endl;
}


int main(int argc,char* argv[])
{
    int n1,n2;
    cout<<"enter two values:"<<endl;
    cin>>n1>>n2;
    sum(n1);
    return 0;
}