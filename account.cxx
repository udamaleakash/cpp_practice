#include <iostream>
#include <memory>
using namespace std;

class A
{
public:
    A()
    {
        cout << "constructor called\n";
    }
    ~A()
    {
        cout << "Destructor called\n";
    }
};
int main()
{
    unique_ptr<A> p1 = make_unique<A>();
    shared_ptr<A> s1 = make_shared<A>();
    cout << s1.use_count() << endl;

    shared_ptr<A> s2 = s1;
    cout << s1.use_count() << endl;

    weak_ptr<A> w1 = s1;
    cout << s1.use_count() << endl;
    if(auto temp = w1.lock()){
        
    }


    return 0;  
}