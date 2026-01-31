/*
    Task 8 creating two custom namespace with same function name and different implementation.
*/
#include<iostream>
#include<iomanip>

using namespace std;

namespace myspace1
{
    void greet()
    {
        cout << "Hello friends" << '\n';
    }
}

namespace myspace2
{
    void greet()
    {
        cout << "Hello geeks" << '\n';
    }
}


int main(int argc,char* argv[])
{
   myspace1::greet();
   myspace2::greet();
   return 0;
}