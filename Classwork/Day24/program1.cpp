//program for creating abstract class Shape with an common attribute and pure virtual function.
#include<iostream>

using namespace std;

class Shape
{
protected:
   float area;
public:
    virtual void calculate_area() = 0;

    virtual void display()
    {
        cout << "from shape class" << endl;
    }
    ~Shape(){}
};

class Circle : public Shape
{
    private:
    float radius;
    public:
    Circle(float r): radius(r){}

    void calculate_area() 
    {
        area=3.14*radius*radius;
        cout<<"Area:"<<area<<endl;
    }

    void display() {
        cout<<"This is Circle Class"<<endl;
    }
    ~Circle(){};
};

class Rectangle : public Shape
{
    private:
    float length;
    float breadth;
    public:
    Rectangle(float l,float b): length(l),breadth(b){}
    void calculate_area() 
    {
        area=length*breadth;
        cout<<"Area:"<<area<<endl;
    }

    void display(){
        cout<<"This is Rectangle Class"<<endl;
    }
    ~Rectangle(){};
};


int main()
{
    Shape* s= new Rectangle(3.0,4.0);
    s->calculate_area();
    s->display();
    s=new Circle(4.5);
    s->calculate_area();
    s->display();
}