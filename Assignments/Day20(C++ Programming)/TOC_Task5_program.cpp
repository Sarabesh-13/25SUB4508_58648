/*
Task-5 Implement abstract base class shape and override it methods
*/

//creating a shape class
#include<iostream>
#include<iomanip>

using namespace std;

class Shape
{
public:
   virtual void draw()=0;
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
   Shape *s=new Circle();
   s->draw();
   s=new Square();
   s->draw();
   delete s;
   return 0;
}