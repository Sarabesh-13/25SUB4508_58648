//program for creating lambda function
#include<iostream>

using namespace std;

int main()
{
    auto msg = [](){cout<<"Hello world"<<endl;};
    auto add = [](int a,int b){cout<<a+b<<endl;};
    msg();
    add(3,5);
}