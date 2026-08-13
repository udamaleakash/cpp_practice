#include <iostream>
using namespace std;

class Shape
{
public:
    virtual void display()
    {
        cout << "Shape Area" << endl;
    }

    virtual ~Shape() {}
};

class Circle : public Shape
{
private:
    int area = 100;

public:
    void display() override
    {
        cout << "Circle Area: " << area << endl;
    }
};

class Square : public Shape
{
private:
    int area = 200;

public:
    void display() override
    {
        cout << "Square Area: " << area << endl;
    }
};

// Displayarea function
void Displayarea(Shape* obj)
{
    obj->display();
}

int main()
{
    Circle c;
    Square s;

    Displayarea(&c);
    Displayarea(&s);

    return 0;
}