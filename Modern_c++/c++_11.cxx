#include <iostream>
#include <vector>
using namespace std;
int main()
{
    cout << "Welcome Modern C++ 11" << endl;
    auto a = 10.8;
    cout << a << endl;
    // if i want to know which data type is assigned to a then i can use decltype
    cout << "Data type of a is: " << typeid(a).name() << endl; // here i means to print the data type of a

    auto add = [](int x, int y)
    { return x + y; }; // here i am using lambda function to add two numbers
    cout << "Addition of 10 and 20 is: " << add(10, 20) << endl;

    auto v = vector<int>{1, 2, 3, 4, 5};
    for (auto it = v.begin(); it != v.end(); it++)
        cout << *it << " ";

    auto name = "Akash";
    cout << "\n"
         << typeid(name).name() << endl; // PKc

    return 0;
}