/*
Program for RTII using static_cast (compilation_time)
BC -> Employee
DC1-> contractEmp
DC2-> perEmp
*/

#include <iostream>

using namespace std;

class Emp
{
public:
    //no virtual functions
    void show()
    {
        cout<<"\nEmployee BC"<<endl;
    }
};

class PerEmp: public Emp
{
public:
    void calculateSalary(){
        cout<<"\nPermanent Employee Salary calculted"<<endl;
    }
};

class ContEmp: public Emp
{
public:
    void calculateWages(){
        cout<<"\nContract Employee Wages calculted"<<endl;
    }
};

void ProcessEmp(Emp *emp, int type)
{
    //Manual selection of the type of emp
    if(type == 1)
    {
        PerEmp *p = static_cast<PerEmp*>(emp);
        p->calculateSalary();
    }

    else if(type == 2)
    {
        ContEmp *c = static_cast<ContEmp*>(emp);
        c->calculateWages();
    }
}


int main()
{
    Emp *e1 = new PerEmp();
    Emp *e2 = new ContEmp();

    ProcessEmp(e1,1);
    ProcessEmp(e2,1);

    delete e1;
    delete e2;

    return 0;
}