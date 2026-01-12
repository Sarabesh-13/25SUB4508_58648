/*
    Task 13 sort vector storing string in descending order with lambdas
*/

#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>

using namespace std;

int main(int argc,char* argv[])
{
    vector<string> s = {"Franklin","Trevor","Michael","Benjamin","CJ"};
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