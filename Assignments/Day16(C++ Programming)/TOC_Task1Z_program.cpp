/*
Task-1Z Implement a Basic Class
*/

//creating a Car class
#include<iostream>
#include<iomanip>

using namespace std;

class Car
{
private:
    string make;
    string model;
    int year;

public:
    Car(string makes, string models, int y) : make(makes), model(models), year(y)
    {
        cout << "Constructor invoked" << endl;
    }
    void get_values()
    {
        cout << "Car make:" << make << endl;
        cout << "Car model:" << model << endl;
        cout << "Car manufactured year:" << year << endl;
    }

    void set_values(const string& m1,const string& m2,int& y1)
    {
        this->make=m1;
        this->model=m2;
        this->year=y1;
    }

    ~Car() = default;
};

int main(int argc,char* argv[])
{
   Car c("Maruthi Suzuki","Alto 800",2009);
   c.get_values();
   string m1="Kun Kia";
   string m2="Carens";
   int y=2022;
   c.set_values(m1,m2,y);
   c.get_values();
   return 0;
}