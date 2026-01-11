//creating a custom namespace and access memebers in it
#include<iostream>
#include<iomanip>

using namespace std;

namespace myspace
{
    class Demo
    {
        public:
            Demo() { cout << "Constructor invoked" << endl; }
            void find_odd_or_even(int &n1)
            {
                if (n1 % 2 == 0)
                {
                    cout << "Even" << endl;
                }
                else
                {
                    cout << "Odd" << endl;
                }
            }

            ~Demo() { cout << "destroyed" << endl; }
    };
}

int main(int argc,char* argv[])
{
   int a=3,b=4;
   myspace::Demo *d = new myspace::Demo();
   d->find_odd_or_even(a);
   d->find_odd_or_even(b);
   delete d;
   return 0;
}