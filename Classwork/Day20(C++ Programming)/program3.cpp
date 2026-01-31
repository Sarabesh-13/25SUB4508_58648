//program for creating a stack class with template and implementing it with header file.
#include<iostream>
#include<cstdlib>
#include "Stack.h"
#define MAX 20

using namespace std;

int main()
{
    Stack<int> s(MAX);
    s.push(50);
    s.push(60);
    s.push(70);
    s.pop();
    s.display();
    
}