#include <iostream>
#include <cstring>

using namespace std;

class Account
{
private:
    char *data;

public:
    Account(char *str);
    Account(const Account &other);
    // Account &Account::operator=(const Account &other);

    ~Account();
    void display();
};

Account::Account(char *str)
{
    data = new char[strlen(str) + 1];
    strcpy(data, str);
    cout << "constructor" << endl;
}
Account::Account(const Account &other)
{
    data = new char[strlen(other.data) + 1];
    strcpy(data, other.data);
}
// Account &Account::operator=(const Account &other)
// {
//     if (this != &other)
//     {
//         data = new char[strlen(other.data) + 1];
//         strcpy(data, other.data);
//     }
//     return *this;
// }

Account::~Account()
{
    cout << "destructor" << endl;
    delete[] data;
}
void Account::display()
{
    cout << data << endl;
}

int main()
{
    Account A1();
    Account A2("Hello");
    A2.display();

    Account A3();
    A3() = A1();

    return 0;
}