
#include <iostream>
#include <string.h>

using namespace std;

class Account{
    
    private:
        char *data;
    public:
    Account(const char *str)// constructor
    {
        data = new char [strlen(str)+1];
        strcpy(data, str);
        cout<<"constructor callled\n";
    }
    Account(const Account &other){
        data = new char[strlen(other.data)+1];
        strcpy(data, other.data);
        cout<<"copy constructor callled\n";
    }
    
    Account &operator=(const Account &other)
    {
        cout<<"copy Assignment operator callled\n";
        if(this != &other)
        {
           
            data = new char[strlen(other.data)+1];
            strcpy(data, other.data);
        }
        return *this;
    }
    
    ~Account()
    {
        cout<<"Destructor called\n";
        delete[] data;
        
    }
};

int main()
{
    Account a1("Hello");
    Account a2 = a1;
    
    Account a3("Akash");
    a2 = a3;
    

    return 0;
}