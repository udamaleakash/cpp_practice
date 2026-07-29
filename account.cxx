#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;

void freq(char str[], int len)
{
    unordered_map<char, int> freq;
    for (int i = 0; i < len; i++)
    {
        freq[str[i]]++;
    }
    unordered_map<char, int>::iterator it1;
    for (it1 = freq.begin(); it1 != freq.end(); it1++)
    {
        cout << it1->first << " " << it1->second << endl;
    }
}
int main()
{
    char str[] = {"Hello"};
    int len = strlen(str);
    freq(str, len);
    return 0;
}