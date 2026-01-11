#include<iostream>
#include<iomanip>

using namespace std;

class A
{
  private:
    int a;
  public:
    A(){cout<<"A constructor got invoked"<<endl;}
    ~A(){cout<<"A destroyed"<<endl;}
    void setA(int v)
    {
        this->a=v;
    }
    void dispA()
    {
        cout<<"A.a value="<<a<<endl;
    }
    friend int friendValue(A&);
};   

int friendValue(A& obj)
{
    return obj.a;
}


int main(int argc,char* argv[])
{

    A aa;
    aa.setA(50);
    aa.dispA();
    cout<<"friend value = "<<friendValue(aa)<<endl;
    return 0;
}