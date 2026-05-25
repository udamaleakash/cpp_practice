#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};
void insert_begin(Node *&head, int val)
{
    Node *temp = new Node();
    temp->data = val;
    temp->next = head;
    head = temp;
}
void display(Node *head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
}
Node *reverse(Node *&head)
{
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;

    Node *temp = new Node();

    if (head == NULL)
    {
        return head;
    }

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

int main()
{
    Node *head = NULL;
    insert_begin(head, 200);
    insert_begin(head, 201);
    insert_begin(head, 202);
    insert_begin(head, 203);
    display(head);

    cout << endl;
    head = reverse(head);
    display(head);
    return 0;
}