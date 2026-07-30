// Factory Method:-
/* Factory design pattern that creates objects without exposing the object creation logic to the client.
We use the Factory Method to hide object creation from the client.

Why use Factory at all?
--> Factory is useful when the client does NOT know which object to create at compile time.

A good answer is:
If object creation is simple and the concrete type is always known at compile time, using a Factory Method adds unnecessary complexity. I would use it when the object type is determined at runtime, when creation logic is complex, or when I want to centralize object creation and reduce coupling."

This answer shows good design judgment.

So your question is valid: for a tiny example, Factory doesn't seem useful. The real value appears in large applications, where many modules need to create different objects dynamically and you want all creation logic in one place rather than scattered throughout the code.

---------------------------------------------------------------------------------------------------------------

NOW SEE E.G.->

Suppose your banking application supports:

ATM Transaction
UPI Transaction
NEFT Transaction

All are transactions.
*/

#include <iostream>
#include <string>
using namespace std;

// Step 1: Base Class
class Transaction
{
public:
    virtual void process() = 0;
    virtual ~Transaction() {};
};

// Step 2: Derived Classes
class AtmTransaction : public Transaction
{
public:
    void process() override
    {
        cout << "\nProcessing ATM transactions\n";
    }
};

class UpiTransaction : public Transaction
{
public:
    void process() override
    {
        cout << "\nProcessing UPI transactions\n";
    }
};

class NeftTransaction : public Transaction
{
public:
    void process() override
    {
        cout << "\nProcessing NEFT transactions\n";
    }
};

// Step 3: Factory Class
class TransactionFactory // Factory decides which object to create.
{
public:
    static Transaction *createTransaction(string type)
    {
        if (type == "ATM")
        {
            return new AtmTransaction();
        }
        else if (type == "UPI")
        {
            return new UpiTransaction();
        }
        else if (type == "NEFT")
        {
            return new NeftTransaction();
        }
        return nullptr;
    }
};

int main()
{
    // The client only talks to the Factory.
    // The factory decides which object to create.

    Transaction *t1 = TransactionFactory::createTransaction("ATM");
    t1->process();

    Transaction *t2 = TransactionFactory::createTransaction("UPI");
    t2->process();

    Transaction *t3 = TransactionFactory::createTransaction("NEFT");
    t3->process();

    delete t1;
    delete t2;
    delete t3;
    return 0;
}

/*            Client
                 |
                 |
                 V
        TransactionFactory
                 |
      ------------------------
      |         |           |
      V         V           V
 ATMTransaction UPITransaction NEFTTransaction 



 "In our banking application, different transaction types such as ATM, UPI, and NEFT shared a common interface. Instead of creating concrete objects directly using new, we used a TransactionFactory that returned a Transaction* based on the transaction type. This centralized the object creation logic and reduced coupling between the client and concrete transaction classes. If a new transaction type like IMPS is introduced, we only update the factory without changing the client code."


Q.Why do we use the Factory Method pattern?
You can answer:-
"We use the Factory Method to hide object creation from the client. Instead of creating objects using new everywhere, the client requests an object from the factory. This reduces coupling, centralizes object creation, and makes it easy to add new types without changing the client code. It follows the Open/Closed Principle because we can extend the system by adding new classes while making minimal changes to existing code."


If the interviewer asks:
Q. If I can directly create the object using new, why do I need a Factory?
->
"Direct object creation is fine for small applications. In large applications, many modules may need to create the same types of objects. Using a Factory centralizes the creation logic, reduces code duplication, and decouples the client from concrete classes. The client only works with the base class interface, while the factory decides which concrete object to create."

 */