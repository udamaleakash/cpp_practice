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

    // ✅ NEW: actually reverse the linked list
    void reverse()
    {
        Node *prev = NULL;
        Node *curr = head;
        Node *next = NULL;

        while (curr != NULL)
        {
            next = curr->next;  // store next
            curr->next = prev;  // reverse link
            prev = curr;        // move prev
            curr = next;        // move curr
        }

        head = prev; // update head
    }

    void display()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << "-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
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

    cout << "Original: ";
    list.display();

    list.reverse();

    cout << "After Reverse: ";
    list.display();

    return 0;
}