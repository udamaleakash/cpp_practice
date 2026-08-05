#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <memory>
using namespace std;

class A
{
public:
    A()
    {
        cout << "constructor\n";
    }
    ~A()
    {
        cout << "Destructor\n";
    }
};

constexpr int add(int a, int b) // compile time constant
{
    return a + b;
}
enum class Akash
{
    Intelligent,
    Smart,
    Rich
};

int main()
{
    // 1
    int *ptr = (int *)malloc(10 * sizeof(int)); // here , using pointer store 10 elements & print dynamic memory allocate
    for (int i = 0; i <= 9; i++)
    {
        ptr[i] = i + 1;
        // cout << ptr[i] << " ";
    }
    free(ptr);

    // 2
    /* A void* is a generic pointer that can store the address of any data type, but it cannot be dereferenced without first casting it to the correct pointer type. */
    int x = 50;
    void *ptr1 = &x;
    // cout << *(int *)ptr1 << endl;

    int a = 10;
    float b = 12.5;
    char c = 'A';

    void *ptr2;

    ptr2 = &a;
    // cout << *(int *)ptr2 << endl;

    ptr2 = &b;
    // cout << *(float *)ptr2 << endl;

    ptr2 = &c;
    // cout << *(char *)ptr2 << endl;

    // 3
    /*
    Lvalue = Location (has a memory location).
    Rvalue = Read value (temporary value or literal).
    */

    // 4
    //  A p1;
    //  A p2 = p1;

    // A *p1 = new A();
    unique_ptr<A> p1 = make_unique<A>();
    // unique_ptr<A> p2 = move(p1);

    shared_ptr<A> s1 = make_shared<A>();
    // cout << s1.use_count() << endl; // 1 count
    shared_ptr<A> s2 = s1;
    // cout << s2.use_count() << endl; // 2
    shared_ptr<A> s3 = s2;
    // cout << s2.use_count() << endl; // 3

    // 5.
    const int a1 = 10;     // It does not guarantee compile-time evaluation. // constant
    constexpr int a2 = 20; // // Compile-time constant
    // The compiler knows the value before the program runs.
    // It guarantees compile-time evaluation and can be used in contexts that require constant expressions, such as array sizes and template parameters.

    // constexpr is commonly used for compile-time constants and compile-time functions.
    constexpr int result = add(10, 20); // Compiler already knows the answer (30), so it can eliminate the function call.
    cout << result << endl;
    /* const means a variable cannot be modified after initialization, but its value may be determined at runtime. constexpr, introduced in C++11, requires the value or function to be evaluable at compile time whenever possible. Every constexpr variable is const, but not every const variable is constexpr. constexpr is commonly used for compile-time constants and compile-time functions. */

    // 6.
    /* Advantages
    * Readable code.
    * Type-safe.
    * Avoids invalid values.
    * No name conflicts.
    * Easier to maintain.
    Interview Answer (30 Seconds)

enum class is used when a variable should have only one value from a fixed set of valid options, such as days, traffic lights, employee roles, transaction types, or order status. Compared to using integers or strings, it makes the code more readable, type-safe, and prevents invalid values and naming conflicts. It is the preferred choice in modern C++.
*/

    Akash a4 = Akash::Smart;
    cout << "Enum Class Value = " << static_cast<int>(a4) << endl;
    if (a4 == Akash::Smart)
    {
        cout << "Enum Class Value = Smart" << endl;
    }
    else if (a4 == Akash::Intelligent)
    {
        cout << "Enum Class Value = Intelligent" << endl;
    }
    else if (a4 == Akash::Rich)
    {
        cout << "Enum Class Value = Rich" << endl;
    }

    // 7.
    // Genric Lambda Function
    auto add = [](auto a, auto b)
    {
        return a + b;
    };

    cout << add(10, 20);   // int
    cout << add(1.5, 2.5); // double
    return 0;
}
