/*
Task-3 Implement operator overloading for Point class
*/

//creating a Point class
#include<iostream>
#include<iomanip>

using namespace std;

class Point
{
private:
    int x1;
    int x2;

public:
    static int instance; 
    Point(){x1=0;x2=0; instance+=1;}
    Point(int n1, int n2) : x1(n1), x2(n2)
    {
        instance+=1;
        cout << "Constructor invoked" << endl;
    }
    
    Point operator + (const Point& other) const
    {
        return Point(x1 + other.x1, x2 + other.x2);
    }

    void display()
    {
        cout<<"x1="<<x1<<",x2="<<x2<<endl;
    }

    ~Point()=default;
};

int Point::instance=0;

int main(int argc,char* argv[])
{
   Point p1(2,3);
   cout<<"Point "<<p1.instance<<" ";
   p1.display();
   Point p2(3,4);
   cout<<"Point "<<p2.instance<<" ";
   p2.display();
   Point p3=p1+p2;
   cout<<"Point "<<p3.instance<<" ";
   p3.display();
   return 0;
}