#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    Node *next;
};
// ** comment part is for circular**

// First node
// Find last node
// point last node to new head


void insertBegin(Node *&head, int val)
{
    Node *newnode = new Node();
    newnode->data = val;

    // // first node
    // if (head == nullptr)
    // {
    //     head = newnode;
    //     newnode->next = head;
    //     return;
    // }

    // // find last node
    // Node *temp = head;
    // while (temp->next != head)
    // {
    //     temp = temp->next;
    // }
    newnode->next = head;
    head = newnode;
    // temp->next = head;
}
void display(Node *&head)
{
    // if (head == nullptr)
    //     return;
    // Node *temp = head;
    // do
    // {
    //     cout << temp->data << " ";
    //     temp = temp->next;
    // } while (temp != head);

    /* below for singly */
    while (head != nullptr)
    {
        cout << head->data << " ";
        head = head->next;
    }
}

int main()
{
    Node *head = nullptr;
    insertBegin(head, 10);
    insertBegin(head, 20);
    insertBegin(head, 30);
    display(head);
    return 0;
}