/*
Task-6 program to create a new file and add text and read it again and print to console.
*/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//function for file I/O operations
void createWriteAndPrintFile() 
{

    ofstream outFile("example.txt");

    if (!outFile) {
        cout << "Error creating file!" << endl;
        return;
    }

    outFile << "Hello, this is line 1." << endl;
    outFile << "This is line 2 written to the file." << endl;
    outFile << "C++ file handling is simple!" << endl;

    outFile.close();

    ifstream inFile("example.txt");
    string line;

    cout << "\nContents of the file:\n";
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}

int main() {
    createWriteAndPrintFile();
    return 0;
}
