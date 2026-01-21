/*
get the employee data in a class with string or char type 
and store them in a binary format and try to read the contents 
back from the file.
*/
#include<bits/stdc++.h>

using namespace std;

class Employee
{
public:
Employee()=default;
Employee(int id ,const string& name): emp_id(id),emp_name(name) {}
void disp()
{
    cout<<"emp_id:"<<emp_id<<endl;
    cout<<"emp_name:"<<emp_name<<endl;
}
~Employee(){}
private:
int emp_id;
string emp_name;
};


int main()
{
    FILE *fp=fopen("data.bin","wb+");
    int id;
    string name;
    for(int i=0;i<5;i++)
    {
        cout<<"Enter id:"<<endl;
        cin>>id;
        cout<<"Enter name:"<<endl;
        cin>>name;
        Employee e(id,name);
        fwrite(&e,sizeof(Employee),1,fp);
    }
    rewind(fp);
    for(int i=0;i<5;i++)
    {
        Employee e;
        fread(&e,sizeof(Employee),1,fp);
        e.disp();
    }
    fclose(fp);
    return 0;
}