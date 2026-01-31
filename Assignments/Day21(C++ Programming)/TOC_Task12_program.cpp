/*
    Task 12 use stl map to map student names with grade
*/
#include<iostream>
#include<iomanip>
#include<map>

using namespace std;

int main(int argc,char* argv[])
{
    map<string,char> student_map;
    //inserting values to map
    student_map["Franklin"]='A';
    student_map.insert({"Michael",'A'});
    student_map.insert(make_pair("Trevor",'C'));
    //printing values to map
    cout<<"Student name with grades"<<endl;
    for(const auto& [key,val]:student_map)
    {
        cout<<"Student Name:"<<key<<endl;
        cout<<"Student Grade:"<<val<<endl;
    }
    return 0;
}