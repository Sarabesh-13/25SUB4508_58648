//program to read message by using named pipe(fifo)
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

    char msg[1024];
    
    // mkfifo(MY_FILE,0666);

    fd=open(MY_FILE,O_RDONLY);

    if(fd<0)
    {
        perror("open failed");
        return 1;
    }
    read(fd,msg,sizeof(msg));
    cout<<"Msg from fifo:"<<msg<<endl;
    close(fd);
    cout<<endl;
    return 0;

}