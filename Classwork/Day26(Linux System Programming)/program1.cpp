//program to write message to FIFO
#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<cstring>
#define MY_FILE "my_file"

using namespace std;

int main()
{
    int fd;

    char msg[1024]="\nmessage written using FIFO\n";
    
    mkfifo(MY_FILE,0666);

    fd=open(MY_FILE,O_WRONLY);

    if(fd<0)
    {
        perror("open failed");
        return 1;
    }
    write(fd,msg,strlen(msg));
    cout<<"Msg written to pipe:"<<endl;
    close(fd);
    cout<<endl;
    return 0;

}