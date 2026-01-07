//program for creating structure program with constructor and member function
#include<iostream>
#include<iomanip>
#include<string>

using namespace std;

struct emp
{
    public:
    int id;
    string name;

    emp(): id(1),name("rohan")
    {
        cout<<"default constructor invoked"<<endl;
    }

    emp(int n,string str): id(n),name(str)
    {
        cout<<"constructor with arguments"<<endl;
    }

    bool check()
    {
        return id>0;
    }

    ~emp(){};

};

int main(int argc,char* argv[])
{
   emp e;
   if(e.check())
   {
      cout<<"valid"<<endl;
   }   
    return 0;
}