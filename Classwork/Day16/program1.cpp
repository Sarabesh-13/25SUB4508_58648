//program to demonstrate namespaces
#include<iostream>
#include<iomanip>

using namespace std;

namespace demo1
{
    void print(int& n)
    {
        cout<<"printing 0 to n"<<'\n';
        for(int i=0;i<n;i++)
        {
            cout<<i<<" "<<endl;
        }
        cout<<"done"<<endl;
    }
} 

namespace demo2
{
    void print(int& n)
    {
        cout<<"printing * pattern upto n"<<'\n';
        for(int i=0;i<n;i++)
        {
            cout<<'*'<<" "<<endl;
        }
    }

    void find_greatest_3()
    {
        int a=2,b=3,c=5;
        cout<<((a>b)?((a>c)?(a):(c)):((b>c))?(b):(c))<<endl;
    }
} 


int main(int argc,char* argv[])
{
    int n;
    cout<<"enter n value:"<<endl;
    cin>>n;
    demo1::print(n);
    demo2::find_greatest_3();
    cout<<"\nhello world"<<endl;
    demo2::print(n);
    return 0;
}