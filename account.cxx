#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Node
{
    Node *prev;
    int data;
    Node *next;
};
void reverse(string str, int len)
{
    if (len < 0)
        return;
    cout << str[len];
    reverse(str, len - 1);
}
string reverse2(string str)
{
    cout << endl;
    int i = 0;
    int len = str.length() - 1;
    while (i < len)
    {
        swap(str[i], str[len]);
        i++;
        len--;
    }
    return str;
}
void reverse3(char *str)
{
    cout << endl;
    int i = 0;
    int len = strlen(str) - 1;
    while (i < len)
    {
        char temp = str[i];
        str[i] = str[len];
        str[len] = temp;

        i++;
        len--;
    }
    cout << str;
}

int main()
{
    // prev|data|next
    Node *first = new Node();
    Node *second = new Node();

    first->prev = NULL;
    first->data = 10;
    first->next = second;

    second->prev = first;
    second->data = 20;
    second->next = NULL;

    cout << first->data << " ";
    cout << second->data;

    cout << "\n\n"
         << endl;
    string str = "Account";
    reverse(str, str.length() - 1);
    cout << reverse2(str);

    char str2[] = "Account";
    reverse3(str2);

    // map
    cout << "\nmap" << endl;
    map<string, int> m1;// unqiue key is allowed
    map<string, int>::iterator it1;
    multimap<string, int>m2; // here allowed duplicate key

    m1["TRAN111"] = 500;
    m1["TRAN112"] = 600;
    m1["TRAN113"] = 784;
    string target = "TRAN1134";
    bool flg = false;
    for (it1 = m1.begin(); it1 != m1.end(); it1++)
    {
        if (m1.find(it1->first) != m1.end())
        {
            if (it1->first == target)
            {

                flg = true;
                cout << "Matched:" << it1->first << it1->second << endl;
            }
        }
    }
    if (!flg)
    {
        cout << "Not Matched:" << endl;
    }

    // vector
    cout << "vector: " << endl;
    vector<string> v1;
    vector<string>::iterator it2;

    v1.push_back("TRAN111");
    v1.push_back("TRAN112");
    v1.push_back("TRAN113");

    string target2 = "TRAN1134";
    bool flg2 = false;
    for (it2 = v1.begin(); it2 != v1.end(); ++it2)
    {
        cout << it2->data() << endl;
    }

    return 0;
}