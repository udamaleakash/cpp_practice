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
    TransactionIdGenerator(const TransactionIdGenerator&) = delete;
    TransactionIdGenerator& operator=(const TransactionIdGenerator&) = delete;

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