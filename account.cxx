#include <iostream>
using namespace std;

class test
{
    int a = 20;
    int b = 40;

public:
    void show()
    {
        cout << "a= " << a << endl;
        cout << "b= " << b << endl;
    }
};

int main()
{
    test t1;
    t1.show();
}