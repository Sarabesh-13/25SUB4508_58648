//program to creatie a chair class with member functions to set and get chair attributes
#include <iostream>
#include <string>

using namespace std;

class Chair 
{

    private:
    string material;
    string color;
    double height;
    double width;
    double depth;
    float price;

    public: 
    void setAttributes(const string& mat, const string& col, double h, double w, double d, float p) {
        material = mat;
        color = col;
        height = h;
        width = w;
        depth = d;
        price = p;
    }

    void getAttributes() const {
        cout << "Chair Attributes:" << endl;
        cout << "Material: " << material << endl;
        cout << "Color: " << color << endl;
        cout << "Height: " << height << " cm" << endl;
        cout << "Width: " << width << " cm" << endl;
        cout << "Depth: " << depth << " cm" << endl;
        cout << "Price: $" << price << endl;
    }
};

int main() 
{
    Chair myChair;
    myChair.setAttributes("Wood", "Brown", 100.0, 50.0, 60.0, 79.99);
    myChair.getAttributes();
    return 0;
}
