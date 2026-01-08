/*
Single inheritence -> this pointer
*/

#include <iostream>
#include <string>

using namespace std;

class Person
{
protected:
   
    string name;
    

public:
    virtual void display()
    {
        cout<<"\n==========Personal details are==========\n";
        cout<<"\nName: "<<name<<endl;
        
        cout<<"\n=========================================\n";
    }
public:
    
    Person()
    {
        cout<<"Cnstr Person"<<endl;
    }
    Person(string name)
    {
        this->name = name;
        
    }
    
    ~Person()
    {
        cout<<"Destr Person"<<endl;
    }
};

class Employee: public Person
{
private:
    int e_id;
    
public:
    Employee()
    {
        cout<<"Cnstr Employee"<<endl;
    }
    Employee(int e_id, string n) 
            : Person(n)
    {
        this->e_id = e_id;
        
    }
    
    void setValues(int id, string n)
    {
        this->e_id = id;
        name = n;
    }
    void display()
    {
        
        cout<<"\n==========Employee details are==========\n";
        cout<<"\nID: "<<e_id<<endl;
        cout<<"\nName: "<<name<<endl;
        cout<<"\n=========================================\n";
    }
    ~Employee()
    {
        cout<<"Destr Employee"<<endl;
    }
};


int main()
{
    Employee e[3];
    string name;
    int id;
    // for(int i=0;i<3;i++)
    // {   cout<<"\nEnter, ";
    //     cout<<"\nName: ";
    //     cin>>name;
    //     cout<<"\nID: ";
    //     cin>>id;
    //     e[i].setValues(id,name);
    // }

    Person *ptrBC[3];
    for(int i=0;i<3;i++)
    {
        cout<<"\nEnter, ";
        cout<<"\nName: ";
        cin>>name;
        cout<<"\nID: ";
        cin>>id;
        ptrBC[i]=new Employee(id,name);
    }   
    for(int i=0;i<3;i++)
    {
        ptrBC[i]->display();
    }

    return 0;
}