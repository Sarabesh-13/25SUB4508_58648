/*
Task-7 program to handle exception in function that divide two numbers.
*/


#include <iostream>
using namespace std;

void demo()
{
    int a, b;

    cout << "Enter two numbers: ";
    cin >> a >> b;

    try {
        if (b == 0) {
            throw runtime_error("Arithmetic Exception: Division by zero");
        }

        int result = a / b;
        cout << "Result: " << result << endl;
    }
    catch (const runtime_error& e) 
    {
        cout << "Exception caught: " << e.what() << endl;
    }
}

int main() 
{
    demo();
    return 0;
}
