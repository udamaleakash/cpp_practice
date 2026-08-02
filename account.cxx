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
    void show()
    {
        cout << "A class call here\n";
    }
};

class B
{
    shared_ptr<A> ptr_a;

public:
    B(shared_ptr<A> e)
    {
        ptr_a = e;
    }
    void display()
    {
        ptr_a->show();
    }
};

int main()
{
    shared_ptr<A> a = make_shared<A>();
    a->show();
    cout << a.use_count()<<endl;

    B b1(a);
    b1.display();

    cout << a.use_count()<<endl;
    return 0;
}