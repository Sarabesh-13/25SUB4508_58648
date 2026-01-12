/*
    Task 15 practise use of auto to simplfy code
*/

#include<iostream>
#include<iomanip>


using namespace std;

int main(int argc,char* argv[])
{
    auto i=34;
    auto str="hello";
    auto f=3.14;
    //detecting of type of variables declared with auto keyword
    cout<<"type id of i:"<<typeid(i).name()<<endl;
    cout<<"type id of str:"<<typeid(str).name()<<endl;
    cout<<"type id of f:"<<typeid(f).name()<<endl;
    return 0;
}