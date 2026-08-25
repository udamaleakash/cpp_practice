#include <iostream>
#include <cstring>
using namespace std;

class A
{
private:
    char *name;

public:
    A(const char *data)
    {
        name = new char[strlen(data) + 1];
        strcpy(name, data);
    }
    A(const A &other)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }

    A &operator=(const A &other)
    {
        if (this != &other)
        {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        return *this;
    }
    A(A &&other)
    {
        name = other.name;
        other.name = nullptr;
    }
    A &operator=(A &&other)
    {
        if (this != &other)
        {
            delete[] name;
            name = other.name;
            other.name = nullptr;
        }
        return *this;
    }

    ~A()
    {
        delete[] name;
        name = nullptr;
    }
};

int main()
{
    A a1("Akash");
    A a2("Prakash");
    a2 = a1;
    A a3("Swapnil");
    a3 = move(a2);
    return 0;
}