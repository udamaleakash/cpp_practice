#include <iostream>
#include <memory>
using namespace std;

class B; // Forward declaration
class A
{
public:
    shared_ptr<B> ptrB;

    A()
    {
        cout << "A Constructor\n";
    }

    ~A()
    {
        cout << "A Destructor\n";
    }
};

class B
{
public:
    shared_ptr<A> ptrA;

    B()
    {
        cout << "B Constructor\n";
    }

    ~B()
    {
        cout << "B Destructor\n";
    }
};
enum class Akash
{
    Clever,
    Intelligent,
    Smart,
    Rich
};

template <typename T>
T add(T a, T b)
{
    return a + b;
}

int main()
{
    auto result = add(10, 20);
    cout << result << endl;
    // Genric Lambda Function
    auto add = [](auto a, auto b)
    {
        return a + b;
    };

    cout << add(10, 20);   // int
    cout << add(1.5, 2.5); // double

    return 0;
}