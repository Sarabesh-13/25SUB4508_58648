//program for RTII using dynamic cast (run_time)

#include<iostream>

using namespace std;

class Base
{
 public:
    virtual void show(){}
};

class Derived : public Base{
   public:
      void special()
      {
        cout<<"Derived specific function"<<endl;
      }
};

int main()
{
    Base *b=new Derived();
    Derived *d = dynamic_cast<Derived *>(b); //safer way for downcasting
    cout<<"type id of *b->"<<typeid(*b).name()<<endl;
    cout<<"type id of b->"<<typeid(b).name()<<endl;
    if(d!=nullptr)
    {
        d->special();
    }
    else{
        cout<<"Failed"<<endl;
    }

    delete b;
    return 0;

}