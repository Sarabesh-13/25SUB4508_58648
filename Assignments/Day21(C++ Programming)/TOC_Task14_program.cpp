/*
    Task 14 use range based loop over stl containers
*/

#include<iostream>
#include<iomanip>
#include<array>
#include<algorithm>

using namespace std;

int main(int argc,char* argv[])
{
    array<string,5> s = {"Franklin","Trevor","Michael","Benjamin","CJ"};
    //sort string with lambdas
    sort(s.begin(), s.end(), [](const string &s1, const string &s2)
         { return s1 > s2; });
    //printing names in descending order
    for(const string& val:s)
    {
      cout<<val<<" ";
    }
    return 0;
}