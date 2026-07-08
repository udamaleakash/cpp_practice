#include <iostream>
#include <string.h>
using namespace std;

class Akash
{
private:
    char *str;

public:
    Akash(const char *data)
    {
        cout << "constructor called" << endl;
        str = new char[strlen(data) + 1];
        strcpy(str, data);
    }
    Akash(const Akash &data)
    {
        cout << "copy constructor called" << endl;
        str = new char[strlen(data.str) + 1];
        strcpy(str, data.str);
    }
    Akash &operator=(const Akash &data)
    {
        if (this != &data)
        {
            cout << "copy assignment constructor called" << endl;
            str = new char[strlen(data.str) + 1];
            strcpy(str, data.str);
        }
        return *this;
    }
    Akash(Akash &&data) noexcept
    {
        cout << "move constructor called" << endl;
        str = data.str;
        data.str = nullptr;
    }
    Akash &operator=(Akash &&data) noexcept
    {
        cout << "move assignment constructor called" << endl;
        if (this != &data)
        {
            str = data.str;
            data.str = nullptr;
        }
        return *this;
    }
    ~Akash()
    {
        delete[] str;
    }
};
int main()
{
    Akash A1("Hello Developer !");
    Akash A2 = A1;

    Akash A3("How are you:");
    A3 = A2;

    Akash A4 = move(A3);
    A1 = move(A3);
    return 0;
}