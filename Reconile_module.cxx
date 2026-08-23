
/* Reconciliation module */

#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <mutex>

/* Interview explanation — short and impressive

"I worked on a reconciliation module where I compared ledger and statement transactions. I used map with the transaction number as the key, which allowed efficient lookup of corresponding transactions.

I implemented configurable reconciliation rules using an enum and switch, such as transaction number + amount + date, amount + date, or amount-only matching.

For large volumes, I divided the transactions into independent batches and processed those batches using multiple worker threads. This improves overall processing throughput because independent batches can run concurrently.

Since multiple threads can access shared output/result data, I used mutex with lock_guard to make that section thread-safe.

So, in short: map handles efficient lookup, reconciliation rules handle business validation, multithreading handles parallel batch processing, and mutex provides thread safety." */

using namespace std;

struct Transaction
{
    string tran_no;
    int amount;
    string date;
};

map<string, Transaction> ledger;
map<string, Transaction> statement;

mutex mtx;

enum RC_RULE
{
    TRAN_AMT_DATE,
    AMT_DATE,
    AMT
};

bool match(RC_RULE rule,
           const Transaction &l,
           const Transaction &s)
{
    switch (rule)
    {
    case TRAN_AMT_DATE:
        return l.tran_no == s.tran_no &&
               l.amount == s.amount &&
               l.date == s.date;

    case AMT_DATE:
        return l.amount == s.amount &&
               l.date == s.date;

    case AMT:
        return l.amount == s.amount;
    }

    return false;
}

void reconcile(const map<string, Transaction> &data,
               RC_RULE rule)
{
    for (map<string, Transaction>::const_iterator it = data.begin();
         it != data.end(); ++it)
    {
        string result = "NOT FOUND";

        map<string, Transaction>::const_iterator st =
            statement.find(it->first);

        if (st != statement.end())
        {
            result = match(rule, it->second, st->second)
                         ? "MATCHED"
                         : "UNMATCHED";
        }

        // lock_guard<mutex> lock(mtx);

        cout << result << " "
             << it->first << " : "
             << it->second.amount << endl;
    }
}

int main()
{
    ledger["1001"] = {"1001", 2500, "01012026"};
    ledger["1002"] = {"1002", 4000, "01012026"};
    ledger["1004"] = {"1004", 3500, "01012026"};

    statement["1001"] = {"1001", 2500, "01012026"};
    statement["1002"] = {"1002", 3500, "01012026"};

    RC_RULE rule = AMT_DATE;

    reconcile(ledger, rule); // without multithreading

    // Simplified threading demonstration
    // thread t1(reconcile, ledger, rule);
    // thread t2(reconcile, ledger, rule);
    /* "For a large number of reconciliation records, I divide the transactions into independent batches. Each worker thread processes a separate batch, so multiple transactions can be reconciled concurrently. The map is responsible for efficient transaction lookup, while multithreading improves overall processing throughput. If threads access shared result data, I protect that section using mutex and lock_guard." */

    // t1.join();
    // t2.join();
    return 0;
}

/* map → efficient lookup
Multithreading → parallel batch processing
mutex → safe access to shared data
RC_RULE → business-rule selection */

/* Using batch wise for multithrading

// Each thread processes its own batch
void reconcileBatch(const vector<string>& batch,
                    RC_RULE rule,
                    int threadId)
{
    for (size_t i = 0; i < batch.size(); ++i)
    {
        const string& tranNo = batch[i];

        map<string, Transaction>::const_iterator l =
            ledger.find(tranNo);

        map<string, Transaction>::const_iterator s =
            statement.find(tranNo);

        string result = "NOT FOUND";

        if (l != ledger.end() && s != statement.end())
        {
            result = match(rule, l->second, s->second)
                     ? "MATCHED"
                     : "UNMATCHED";
        }

        // Protect shared output
        lock_guard<mutex> lock(mtx);

        cout << "Thread " << threadId
             << " -> " << tranNo
             << " -> " << result << endl;
    }
}

int main()
{
    // In real project these records come from DB/file.
    ledger["1001"] = {"1001", 2500, "01012026"};
    ledger["1002"] = {"1002", 4000, "01012026"};
    ledger["1003"] = {"1003", 3000, "01012026"};
    ledger["1004"] = {"1004", 3500, "01012026"};

    statement["1001"] = {"1001", 2500, "01012026"};
    statement["1002"] = {"1002", 3500, "01012026"};
    statement["1003"] = {"1003", 3000, "01012026"};
    // 1004 is not present → NOT FOUND


    // Divide records into batches
    vector<string> batch1;
    vector<string> batch2;

    batch1.push_back("1001");
    batch1.push_back("1002");

    batch2.push_back("1003");
    batch2.push_back("1004");


    // Select reconciliation rule
    RC_RULE rule = AMT_DATE;


    // Create worker threads
    thread t1(reconcileBatch, batch1, rule, 1);
    thread t2(reconcileBatch, batch2, rule, 2);

    // Wait for both threads
    t1.join();
    t2.join();
 */