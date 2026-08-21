#include <iostream>
using namespace std;



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