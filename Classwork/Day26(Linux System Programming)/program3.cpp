//program to send message using message queue
#include<iostream>
#include<string>
#include<cstring>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MSG_SIZE 100

using namespace std;

struct Msg
{
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main()
{
    key_t key=ftok("/home/student/25SUB4508_58648/Classwork/Day24/progfile",61);
    if(key==-1)
    {
        cerr<<"error creating key"<<endl;
        return 1;
    }
    int msgid=msgget(key,IPC_CREAT|0666);
    if(msgid==-1)
    {
        cerr<<"error creating msg queue"<<endl;
        return 1;
    }
   Msg msg;
   msg.msg_type=1;
   string content="Hello from sender";
   strncpy(msg.msg_text,content.c_str(),MSG_SIZE);
   if(msgsnd(msgid,&msg,sizeof(msg.msg_text),0)==-1)
   {
     perror("msgsnd failure");
     return 1;
   }
   cout<<"msg_id:"<<msgid<<endl;
   cout<<"msg_sent:"<<msg.msg_text<<endl;
   return 0;
}