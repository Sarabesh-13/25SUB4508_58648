/*
    Task 11 use stl vector to store values and manipulation
*/
#include<iostream>
#include<iomanip>
#include<vector>

using namespace std;

void find_sum_and_average_of_vector(const vector<int>& v)
{
    int sum=0;
    float avg=0.0;
    for(int value:v)
    {
      sum+=value;
    }
    avg=sum/v.size();
    cout<<"sum = "<<sum<<endl;
    cout<<"averge = "<<avg<<endl;
}


int main(int argc,char* argv[])
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);
    find_sum_and_average_of_vector(v);
    return 0;
}