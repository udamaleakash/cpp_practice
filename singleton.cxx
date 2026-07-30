#include <iostream>
using namespace std;

/*

 Singlton class means only one object of that class can be created.
 1. Constructor of that class should be private.
 2. Static method should be created which will return the object of that class.
 Cant create object of that class using new keyword.


 Constructor called only once.
 Addresses are same.

 WHY-
 The Singleton Design Pattern is used when you want only one object (instance) of a class to exist in the entire program, and everyone should use that same object.
 */

class Akash
{
    Akash() // 1.
    {
        cout << "constructor called" << endl;
    }

public:
    static Akash &get_obj() // 2.
    {
        static Akash obj; // a1, a2, a3 all refer here
        return obj;
    }
    void display()
    {
        cout << "Akash class obj created\n";
    }
};
int main()
{
    Akash &a1 = Akash::get_obj();
    Akash &a2 = Akash::get_obj();
    Akash &a3 = Akash::get_obj();

    a1.display();
    a2.display();
    cout << &a1 << endl;
    cout << &a2 << endl;
    if (&a1 == &a2 && &a1 == &a3)
    {
        cout << "All are pointing to same object\n";
    }
    else
    {
        cout << " Different objects\n";
    }

    return 0;
}
/*
output->

constructor called
Akash class obj created
Akash class obj created
0x5b1bc4527151
0x5b1bc4527151
Both are same object
 */

//  ____________________________________________________________________
/*
BELOW IS REAL PROJECT BAED E.G.

"In a banking application, multiple modules like ATM, UPI, and NEFT need unique transaction IDs. I would implement a TransactionIdGenerator as a Singleton so that only one counter exists in the application. Every module calls TransactionIdGenerator::getInstance().generateId(), ensuring IDs like 1001, 1002, 1003 are generated sequentially without duplicates. The constructor is private, the instance is created through a static method, and copy operations are deleted to ensure only one instance exists."

Banking Application
                     |
     ------------------------------------
     |               |                  |
  ATM Module      UPI Module       NEFT Module
     |               |                  |
     |               |                  |
     --------TransactionIdGenerator -----
                 (Singleton)

Constructor is called only once.
All modules use the same object.
Transaction IDs are unique.

----->

#include <iostream>
using namespace std;

class TransactionIdGenerator
{
private:
    int transactionId;

    TransactionIdGenerator()
    {
        transactionId = 1000;
        cout << "Transaction ID Generator Started\n";
    }

public:
  
    static TransactionIdGenerator& getInstance()
    {
        static TransactionIdGenerator obj;
        return obj;
    }

    int generateId()
    {
        return ++transactionId;
    }
};

// ATM Module
class ATM
{
public:
    void withdraw()
    {
        int id = TransactionIdGenerator::getInstance().generateId();

        cout << "ATM Withdrawal, Transaction ID = " << id << endl;
    }
};

// UPI Module
class UPI
{
public:
    void transfer()
    {
        int id = TransactionIdGenerator::getInstance().generateId();

        cout << "UPI Transfer, Transaction ID = " << id << endl;
    }
};

// NEFT Module
class NEFT
{
public:
    void sendMoney()
    {
        int id = TransactionIdGenerator::getInstance().generateId();

        cout << "NEFT Transfer, Transaction ID = " << id << endl;
    }
};

int main()
{
    ATM atm;
    UPI upi;
    NEFT neft;

    atm.withdraw();
    upi.transfer();
    neft.sendMoney();

    return 0;
}

outpout->
Transaction ID Generator Started
ATM Withdrawal, Transaction ID = 1001
UPI Transfer, Transaction ID = 1002
NEFT Transfer, Transaction ID = 1003
*/
