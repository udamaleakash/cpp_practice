
/* A linked list is a linear dynamic data structure where elements are stored in separate memory locations and connected using pointers.

Each node contains:
--data
pointer to next node */

#include <iostream>
using namespace std;

struct Node // 1
{
    int data;
    Node *next;
};
void insert_begin(Node *&head, int val)
{
    // a)
    Node *temp = new Node();
    // b)
    temp->data = val;
    // c)
    temp->next = head;
    // d)
    head = temp;
}

void insertEnd(Node *&head, int val) // insert at end
{
    Node *temp = new Node();
    temp->data = val;
    temp->next = NULL;

    if (head == NULL)
    {
        head = temp;
        return;
    }

    Node *curr = head;
    while (curr->next != NULL) // travrsea and add
    {
        curr = curr->next;
    }
    curr->next = temp;
}

Node *reverse(Node *head) // reverse link list
{
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

void display(Node *head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
}

int main()
{
    Node *head = NULL; // 2
    cout << "\nInsertion at Begin: ";

    /*
    // Steps-> Insertion at begin [1-4]
    // 1 structure creation
    // 2 define NULL head pointer
    // 3 insertion at begin a) b) c) d)
    // 4 display
    */
    insert_begin(head, 111); // 3
    insert_begin(head, 222);
    insert_begin(head, 333);
    insert_begin(head, 444);
    display(head); // 4

    cout << "\nInsertion at End: ";
    insertEnd(head, 555);
    insertEnd(head, 666);
    insertEnd(head, 777);
    insertEnd(head, 888);
    display(head);

    cout << "\nReverse Link List: ";
    head = reverse(head);
    display(head);

    return 0;
}