/*
Task-9 Directory Operation in C
Use system calls to list all files and the directories in the current working directory
Change current working directory to tmp and set permission to 755.
*/

#include<iostream>
#include<cstdlib>

using namespace std;

int main()
{
    cout<<"Listing directories"<<endl;
    system("ls -lia");
    cout<<"Changing the current working directory to /tmp"<<endl;
    // system("clear");
    system("cd tmp");
    cout<<"creating new directory named testdir within /tmp and set permission to 0755"<<endl;
    system("mkdir -p tmp/testdir");
    system("chmod 755 tmp/testdir");
    // system("cd ..");
    return 0;
}