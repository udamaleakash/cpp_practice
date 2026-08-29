#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

void insertBegin(Node *&head, int value)
{
    Node *newNode = new Node;
    newNode->data = value;
    // First node
    if (head == nullptr)
    {
        head = newNode;
        newNode->next = head;
        return;
    }
    Node *temp = head;
    // Find last node
    while (temp->next != head)
    {
        temp = temp->next;
    }
    newNode->next = head;
    head = newNode;
    temp->next = head;
}

void display(Node *head)
{
    if (head == nullptr)
        return;
    Node *temp = head;
    do
    {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
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