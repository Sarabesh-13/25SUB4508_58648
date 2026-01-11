/*
Task-4 Implement base class shape and override it methods
*/

//creating a shape class
#include<iostream>
#include<iomanip>

using namespace std;

class Shape
{
public:
   virtual void draw()
   {
    cout<<"Drawing from base class"<<endl;
   }
   ~Shape()=default;
};

class Circle: public Shape
{
public:
   void draw() override
   {
    cout<<"Drawing from Circle class"<<endl;
   }
   ~Circle()=default;
};

class Square: public Shape
{
public:
   void draw() override
   {
    cout<<"Drawing from Square class"<<endl;
   }

   ~Square()=default;
};

int main(int argc,char* argv[])
{
   Shape s;
   s.draw();
   Circle c;
   c.draw();
   Square sq;
   sq.draw();
   return 0;
}