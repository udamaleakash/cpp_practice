#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int val)
    {
        data = val;
        next = NULL;
    }
};

class Linklist
{
private:
    Node *head;

public:
    Linklist()
    {
        head = NULL;
    }

    void insert(int val)
    {
        /*
        newNode created
        if head NULL → head = newNode
        else go to last node → last->next = newNode
         */
        Node *newNode = new Node(val);
        if (head == NULL)
        {
            head = newNode;
            return;
        }
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    void delete_by_value()
    {
        /* 
        if head matches → delete head
        else find previous node
        previous->next = current->next
        delete current
        */
    }

    void display()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << "-> ";
            temp = temp->next;
        }
        cout << " NULL " << endl;
    }
    ~Linklist()
    {
        Node *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    Linklist list;
    list.insert(1000);
    list.insert(2000);
    list.insert(3000);
    list.display();
    return 0;
}