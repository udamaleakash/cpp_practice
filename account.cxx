#include <iostream>
using namespace std;

struct Node
{
    Node *prev;
    int data;
    Node *next;
};

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

    return 0;
}