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
            int find_gcd(int n1,int n2)
            {
                int t;
                while(n2!=0)
                {
                    t=n2;
                    n2=n1%n2;
                    n1=t;
                }
                return n1;
            }

            ~Demo() { cout << "destroyed" << endl; }
    };
}

int main(int argc,char* argv[])
{
   int a=3,b=4;
   myspace::Demo *d = new myspace::Demo();
   cout<<"Gcd of a and b is "<<d->find_gcd(a,b)<<endl;
   delete d;
   return 0;
}