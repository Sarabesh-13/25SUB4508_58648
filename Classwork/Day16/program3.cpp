//program to demonstrate various string functions
#include<iostream>
#include<iomanip>

using namespace std;

int main(int argc,char* argv[])
{
    string str="abcedfghijklmnopqrstuvwxyz abcdefghijklmno";
    cout<<str.capacity()<<endl;
    cout<<str<<endl;
    cout<<str+"hello"<<endl;
    cout<<str.erase()<<endl;
    cout<<str.length()<<endl;
    cout<<str.append("hello")<<endl;
    cout<<str.capacity()<<endl;
    cout<<str.length()<<endl;
    cout<<str.at(0)<<endl;
    str.clear();
    cout<<str.capacity()<<endl;
    cout<<str.length()<<endl;
    return 0;
}