//program for printing command line arguments
#include<iostream>
#include<iomanip>

using namespace std;

int main(int argc,char* argv[])
{
   if(argc>0)
   {
    cout<<"total arguments:"<<argc<<endl;
    
    for(int i=0;i<argc;i++)
    {
        cout<<argv[i]<<" ";
    }
   }
   return 0;
}