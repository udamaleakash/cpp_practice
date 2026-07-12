#include <iostream>
#include <memory>
using namespace std;

class Test
{
public:
    Test()
    {
        cout << "Constructor\n";
    }

    ~Test()
    {
        cout << "Destructor\n";
    }

    void display()
    {
        cout << "Hello\n";
    }
};

int main()
{
    // unique_ptr<Test> ptr = make_unique<Test>();

    // ptr->display();

    int *p1 = new int(10);
    unique_ptr<int> p2 = make_unique<int>(10);
    shared_ptr<int> p3 = make_unique<int>(10);
    shared_ptr<int> p4 = p3;
    weak_ptr<int>p5 = p4;

    return 0;
}