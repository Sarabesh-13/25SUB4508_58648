/*
    Task 9 write a program to make use of unique_ptr
*/
#include<iostream>
#include<iomanip>
#include<memory>

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
    // unique_ptr<int> s = make_unique<int>(10);
    // cout << "unique pointer s address:" << s << endl;
    // cout << "unique ptr s value = " << *s << endl;
    // // transfering ownership of unique_ptr
    // unique_ptr<int> k = move(s);
    // cout << "unique ptr value of k after transfering ownership = " << *k << endl;
    // cout << "unique pointer k's address after transfering:" << k << endl;

    //creating unique_ptr for class and access it's members
    unique_ptr<Car> c = make_unique<Car>("Maruthi Suzuki","Alto 800",2009);
    c->get_values();
    return 0;
}