#include <iostream>
#include <memory>
using namespace std;

class Engine
{
public:
    void start()
    {
        cout << "Engine started\n";
    }

    ~Engine()
    {
        cout << "Engine Destructor\n";
    }
};

class Car
{
private:
    shared_ptr<Engine> engine;

public:
    Car(shared_ptr<Engine> e)
    {
        engine = e;
    }

    void drive()
    {
        engine->start();
        cout << "Car is driving\n";
    }
};

int main()
{
    shared_ptr<Engine> e = make_shared<Engine>();

    cout << "Reference count: "
         << e.use_count() << endl;       // 1

    Car c1(e);

    cout << "Reference count: "
         << e.use_count() << endl;       // 2

    c1.drive();

    return 0;
}