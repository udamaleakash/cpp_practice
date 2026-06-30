#include <iostream>
#include <cstring>
#include <utility> // for std::move
using namespace std;

class student
{
private:
    char *name;

public:
    // constructor
    student(const char *str)
    {
        cout << "\nConstructor called" << endl;
        name = new char[strlen(str) + 1];
        strcpy(name, str);
    }

    // 1) copy constructor
    student(const student &other)
    {
        cout << "Copy Constructor called" << endl;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    // 2) copy Assignment operator
    student &operator=(const student &other)
    {
        cout << "Copy Assignment operator called" << endl;
        if (this != &other)
        {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        return *this;
    }

    // 3) Destructor
    ~student()
    {
        cout << "Destructor called" << endl;
        delete[] name;
        name = nullptr;
    }

    // 4) Move Constructor
    student(student &&other) noexcept
    {
        cout << "Move Constructor called" << endl;
        name = other.name;
        other.name = nullptr;
    }

    // 5) Move Assignment operator
    student &operator=(student &&other) noexcept
    {
        cout << "Move Assignment operator called" << endl;
        if (this != &other)
        {
            delete[] name;
            name = other.name;
            other.name = nullptr;
        }
        return *this;
    }
};

/*

student(const char *str) // constructor
student(const student &other) // copy constructor
student &operator=(const student &other) // copy Assignment operator
~student() // Destructor
student(student &&other) noexcept // Move Constructor
student &operator=(student &&other) noexcept // move assignment operator

*/

int main()
{
    // Rule Of 5
    student s1("Hello"); // constructor
    student s2 = s1;     // copy constructor

    student s3("Temp");
    s2 = s3; // copy Assignment operator

    student s4 = move(s1); // move constructor

    student s5("Account");
    s5 = move(s4); // Move Assignment operator

    return 0;
}