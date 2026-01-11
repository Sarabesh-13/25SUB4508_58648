#include<iostream>
#include<iomanip>

using namespace std;

class Student
{
    protected:
     int sem;
     string course;
    private:
      int phone_no;
      char gender;
      int id;
      string name;
      string address;
      string dob;
    public:
       Student()
       {
         cout<<"Constructor Invoked"<<endl;
         name="User1";
         gender='M';
         id=21;
         phone_no=75065075;
       }
    public:
      Student(string,char,int,int);
      Student(Student&);
      void setValue();
      void getValue();
      void setValueArgs(string,char,int,int);
};

Student::Student(Student &other)
{
    cout<<"copy constructor invoked"<<endl;
    name=other.name;
    gender=other.gender;
    id=other.id;
    phone_no=other.phone_no;

}
Student::Student(string name_n,char g,int id_no,int ph_n)
{
    cout<<"parameterized constructor invoked"<<endl;
    cout<<id_no<<endl;
    name=name_n;
    gender=g;
    id=id_no;
    phone_no=ph_n;
}

void Student::setValue()
{
   cout<<"enter your name:"<<'\n';
   cin>>name;
   cout<<"enter your gender M/F:"<<'\n';
   cin>>gender;
   cout<<"\nenter your id:"<<'\n';
   cin>>id;
   cout<<"\nenter your phone number:"<<'\n';
   cin>>phone_no;
}

void Student::getValue()
{
    cout<<"Student details"<<endl;
    cout<<"your name is "<<name<<endl;
    cout<<"gender "<<gender<<endl;
    cout<<"id = "<<id<<endl;
    cout<<"phone number: "<<phone_no<<endl;
    cout<<"-------------------------------"<<endl;
}

void Student::setValueArgs(string n,char g,int id_no,int ph_no)
{
    name=n;
    gender=g;
    id=id_no;
    phone_no=ph_no;
    cout<<"values has been set"<<endl;
}

int main(int argc,char* argv[])
{
    Student s1,s2;
    // s1.setValueArgs("John doe",'M',25,60809);
    // // s1.setValue();
    // s1.getValue();
    // s2.setValue();
    s2.setValueArgs("Benjamin",'M',65,765890);
    s2.getValue();
    Student s3=s1;
    s3.getValue();
    Student s4(s3);
    s3.getValue();
    Student s5("Franklin",'M',456,87956784);
    s5.getValue();
    return 0;
}