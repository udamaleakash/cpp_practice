#include <iostream>
#include <cstring>
#include <utility>  // for std::move

using namespace std;

class MyBuffer
{
private:
    char *data;
    int size;

public:
    // 1. Constructor (from string)
    MyBuffer(const char* str)
    {
        size = strlen(str) + 1;   // +1 for '\0'
        data = new char[size];
        memcpy(data, str, size);
        cout << "Constructor\n";
    }

    // 2. Destructor
    ~MyBuffer()
    {
        delete[] data;
        cout << "Destructor\n";
    }

    // 3. Copy Constructor
    MyBuffer(const MyBuffer &other)
    {
        size = other.size;
        data = new char[size];
        memcpy(data, other.data, size);
        cout << "Copy Constructor\n";
    }

    // 4. Copy Assignment
    MyBuffer &operator=(const MyBuffer &other)
    {
        cout << "Copy Assignment\n";

        if (this != &other)
        {
            delete[] data;

            size = other.size;
            data = new char[size];
            memcpy(data, other.data, size);
        }
        return *this;
    }

    // 5. Move Constructor
    MyBuffer(MyBuffer &&other) noexcept
    {
        data = other.data;
        size = other.size;

        other.data = NULL;
        other.size = 0;

        cout << "Move Constructor\n";
    }

    // 6. Move Assignment
    MyBuffer &operator=(MyBuffer &&other) noexcept
    {
        cout << "Move Assignment\n";

        if (this != &other)
        {
            delete[] data;

            data = other.data;
            size = other.size;

            other.data = NULL;
            other.size = 0;
        }
        return *this;
    }

    // Helper function to print data
    void print() const
    {
        if (data)
            cout << data << endl;
        else
            cout << "Empty\n";
    }
};

int main()
{
    MyBuffer a("Hello");

    MyBuffer b = a;            // Copy constructor
    MyBuffer c("World");
    c = a;                     // Copy assignment

    MyBuffer d = std::move(a); // Move constructor
    MyBuffer e("Test");
    e = std::move(b);          // Move assignment

    cout << "\nData:\n";
    d.print();
    e.print();

    return 0;
}