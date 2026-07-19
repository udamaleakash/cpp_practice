// mutlithreding

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class Animal
{
public:
    virtual void sound() // Virtual Function
    {
        cout << "Animal makes a sound" << endl;
    }
};

class Dog : public Animal
{
public:
    void sound() override
    {
        cout << "Dog barks" << endl;
    }
};

class Cat : public Animal
{
public:
    void sound() override
    {
        cout << "Cat meows" << endl;
    }
};
void merge_two_arr()
{
    int arr1[] = {91, 433, 5, 7};
    int arr2[] = {34, 567, 45, 23};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int merged[n1 + n2];

    int j = 0;
    for (int i = 0; i < (n1 + n2); i++)
    {
        if (i < n1)
            merged[i] = arr1[i];
        else
        {
            merged[i] = arr2[j++];
        }
        
        for (int k = i + 1; k < (n1 + n2); k++)
        {
            if (merged[i] > merged[k])
            {
                int temp = merged[i];
                merged[i] = merged[k];
                merged[k] = temp;
            }
        }
    }

    for (int i = 0; i < (n1 + n2); i++)
    {
        cout << merged[i] << " ";
    }
}

int main()
{
    // Animal *ptr1 = new Animal();
    // ptr1->sound();

    // Animal *ptr2 = new Dog();
    // ptr2->sound();

    // Animal *ptr3 = dynamic_cast<Dog >;

    /* what is malloc in c */
    /* malloc is a function in C that is used to dynamically allocate memory on the heap. It takes the size of the memory block to be allocated as an argument and returns a pointer to the allocated memory. */
    int *p = (int *)malloc(100);
    int *p2 = (int *)malloc(5 * sizeof(int));
    // here malloc is used to allocate memory for 5 integers, and sizeof(int) is used to determine the size of an integer in bytes. The total amount of memory allocated will be 5 times the size of an integer.

    // Calloc is another function in C that is used to dynamically allocate memory on the heap. It is similar to malloc, but it also initializes the allocated memory to zero. It takes two arguments: the number of elements to allocate and the size of each element. It returns a pointer to the allocated memory.

    int *ptr3 = (int *)calloc(6, sizeof(int));
    // here calloc is used to allocate memory for 6 integers, and sizeof(int) is used to determine the size of an integer in bytes. The total amount of memory allocated will be 6 times the size of an integer, and all the allocated memory will be initialized to zero.
    // above total memory = 6 * sizeof(int) = 6*4 = 24 bytes
    char *ptr4 = (char *)calloc(10, sizeof(char));
    // here calloc is used to allocate memory for 10 characters, and sizeof(char) is used to determine the size of a character in bytes. The total amount of memory allocated will be 10 times the size of a character, and all the allocated memory will be initialized to zero.
    // hence total memory = 10 * sizeof(char) = 10*
    // different between malloc and calloc is that malloc does not initialize the allocated memory, while calloc initializes the allocated memory to zero.

    // realloc is a function in C that is used to resize a previously allocated memory block. It takes two arguments: a pointer to the previously allocated memory block and the new size of the memory block. It returns a pointer to the resized memory block. If the new size is larger than the old size, realloc will allocate additional memory and copy the contents of the old memory block to the new memory block. If the new size is smaller than the old size, realloc will free the excess memory and return a pointer to the resized memory block.

    int *ptr5 = (int *)realloc(ptr3, 10 * sizeof(int));
    // here realloc is used to resize the previously allocated memory block pointed to by ptr3 to hold 10 integers. The new size of the memory block will be 10 times the size of an integer, and the contents of the old memory block will be copied to the new memory block. If the new size is larger than the old size, realloc will allocate additional memory and copy the contents of the old memory block to the new memory block. If the new size is smaller than the old size, realloc will free the excess memory and return a pointer to the resized memory block.

    merge_two_arr();

    /* fork() is not a standard C library function. It is a Linux/Unix system call declared in <unistd.h>. It requests the operating system kernel to create a new process. (to create new child process) */

    // A process is an independent program in execution
    // A thread is a lightweight execution unit inside a process.

    

    return 0;
}