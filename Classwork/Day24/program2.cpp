//program for creating Employee Payroll Management System.
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Employee
{
public:
    virtual void calculateSalary() = 0;
    virtual void displayDetails() = 0;
    virtual ~Employee() {}

protected:
    int id;
    string name;
    double salary;
    string status;
};

class FullTimeEmployee : public Employee
{
public:
    FullTimeEmployee(int e_id, const string &e_name, double e_salary, const string &e_status)
    {
        id = e_id;
        name = e_name;
        salary = e_salary;
        status = e_status;
    }

    void displayDetails() 
    {
        cout<<"-----------------"<<endl;
        cout<<"Full Time Employee Details"<<endl;
        cout<<"Employee ID   : " <<id<<endl;
        cout<<"Employee Name : " <<name<<endl;
        calculateSalary();
    }

    // protected:
    void calculateSalary() 
    {
        double hra = 0.30 * salary;
        double da = 0.15 * salary;
        cout<<"Total Salary: "<<salary + hra + da<<endl;
    }

    ~FullTimeEmployee(){}
};

class PartTimeEmployee : public Employee
{
private:
      double hourly_rate;
      int hours_worked;
public:
    PartTimeEmployee(int emp_id, const string &emp_name, double emp_salary, const string &emp_status,int hours)
    {
        id = emp_id;
        name = emp_name;
        salary = emp_salary;
        status = emp_status;
        hours_worked=hours;
        hourly_rate=15.00;
    }

    void displayDetails() 
    {
        cout<<"-----------------"<<endl;
        cout<<"Part Time Employee Details"<<endl;
        cout<<"Employee ID   : " <<id<<endl;
        cout<<"Employee Name : " <<name<<endl;
        calculateSalary();
    }

    // protected:
    void calculateSalary()
    {
        cout<<"Total Salary: "<<salary+(hourly_rate*hours_worked)<<endl;
    }

    ~PartTimeEmployee(){}
};

int main()
{
    vector<Employee *> employees;
    bool running = true;
    int employee_id;
    string employee_name;
    double employee_salary;
    string employee_status;
    int hours_worked;
    int choice;

    while (running)
    {
        cout<<"\nEmployee Payroll Management System\n";
        cout<<"1. Add Employee Details\n";
        cout<<"2. Display Employee Details\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice)
        {
        case 1:
        {
            cout<<"Enter employee status (full-time / part-time): ";
            cin>>employee_status;

            cout<<"Enter employee ID: ";
            cin>>employee_id;

            cout<<"Enter employee name: ";
            cin>>employee_name;

            cout<<"Enter employee salary: ";
            cin>>employee_salary;

            if (employee_status == "part-time")
            {
                cin>>hours_worked;
                employees.emplace_back(
                    new PartTimeEmployee(employee_id, employee_name, employee_salary, employee_status,hours_worked));
            }
            else if (employee_status == "full-time")
            {
                employees.emplace_back(
                    new FullTimeEmployee(employee_id, employee_name, employee_salary, employee_status));
            }
            else
            {
                cout<<"Invalid employee status!"<<endl;
            }
            break;
        }

        case 2:
        {
            if (employees.empty())
            {
                cout<<"No employee records found."<<endl;
            }
            else
            {
                for (const auto& emp : employees)
                {
                    emp->displayDetails();
                }
            }
            break;
        }

        case 3:
        {
            running = false;
            break;
        }

        default:
            cout<<"Invalid choice!"<<endl;
        }
    }
    for (Employee *emp : employees)
    {
        delete emp;
    }
    return 0;
}