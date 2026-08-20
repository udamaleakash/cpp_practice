

/* A Linked List is a linear data structure where elements (called nodes) are not stored in contiguous memory. */

// steps
// 1 structure creation
// 2 define head pointer and make it NULL
// 3 insertion a) b) c) d)
// 4 Display

#include <iostream>
using namespace std;

// 1. structure creation
struct Node
{
    int data;
    Node *next;
};
/* Why Node* &head ? in below
-> &head means - pass by reference & original head changes
without & changes it will local copy, original list will not update */
void insert(Node *&head, int value)
{
    // a) create new node
    Node *temp = new Node();
    // b) store data
    temp->data = value; // 10 | ?
    // c) connet new node to old head
    temp->next = head; // current head = NULL so, 10 | NULL

    // d) move head to new node
    head = temp; // here head = 10, so it will 10 | NULL

    // 2nd insertion head = 20, 20 | 10 | NULL
    // after same process,
    // 3rd insertion head = 30, it becomes 30->20->10->NULL
}
void display(Node *&head)
{
    while (head != NULL)
    {
        cout << head->data << " "; // it write fist value 30
        head = head->next; // move forward now head points to 20 so, like wise
    }
}

int main()
{
    Node *head = NULL; // 2.  head pointer, initally link list is empty

    insert(head, 10); // 3. first insertion
    insert(head, 20); // 2nd insertion, 20-> ?
    insert(head, 30);
    display(head); // 4. display
    return 0;
}