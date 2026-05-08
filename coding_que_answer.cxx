
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <map>
#include <vector>

#define pass_irno "      "
using namespace std;

struct detail_1
{
	char actno[14];
	char long_name[41];
	char sh_name[21];
	char guar_name[36];
};

char firstNonRepeating(string str)
{
	int freq[256] = {0};

	for (int i = 0; i < str.length(); i++)
		freq[str[i]]++;

	for (int i = 0; i < str.length(); i++)
		if (freq[str[i]] == 1)
			return str[i];

	return '#';
}

char firstNonRepeating2(string str)
{
	char *str2 = new char[256];
	int count = 0;
	int len = str.length();
	strncpy(str2, str.c_str(), len);
	str2[len] = '\0';

	for (int i = 0; i < len; i++)
	{
		count = 0;
		for (int j = 0; j < len; j++)
		{
			if (str2[i] == str2[j])
				++count;
		}
		if (count == 1)
			return str2[i];
	}
	return '#';
	delete str2;
}

string reverseString1(string str)
{
	int i = 0;
	int j = str.length() - 1;
	while (i < j)
	{
		swap(str[i], str[j]);
		i++;
		j--;
	}
	return str;
}
string reverseString2(string str)
{
	int len = str.length();
	string result;
	for (int i = len - 1; i >= 0; i--)
	{
		result += str[i];
	}
	str = result;
	return str;
}

string reverseString3(string str) // good
{
	int i = 0;
	int j = str.length() - 1;

	while (i < j)
	{
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	return str;
}
string reverseString4(string str)
{
	for (int i = 0, j = str.length() - 1; i < j; i++, j--)
	{
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return str;
}

string reverseWordsString(string str)
{
	string result = "";
	string word = "";
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == ' ')
		{
			if (!word.empty())
			{
				result += word + " ";
				word = "";
			}
		}
		else
		{
			word = str[i] + word;
		}
	}
	if (!word.empty())
	{
		result += word;
	}
	else if (!result.empty())
	{
		result.erase(result.length() - 1);
	}
	return result;
}

void reverse(char *start, char *end)
{
	while (start < end)
	{
		char temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}

void reverseWordsString2(char *str)
{
	int len = strlen(str);
	// Step 1: reverse whole string
	reverse(str, str + len - 1);
	// Step 2: reverse each word
	char *word_start = str;
	for (int i = 0; i <= len; i++)
	{
		if (str[i] == ' ')
		{
			reverse(word_start, str + i - 1);
			word_start = str + i + 1;
		}
	}
}

void removeDuplicate(int arr[], int &len)
{
	for (int i = 0; i < len; i++) // 2, 2, 3, 4, 5, 3, 4, 1, 1, 88, 45, 45,88
	{
		for (int j = i + 1; j < len; j++)
		{
			if (arr[i] == arr[j])
			{
				for (int k = j; k < len; k++)
				{
					arr[k] = arr[k + 1]; /* duplicate element replaced by next element */
				}
				len--; /* when duplicate element remove then size decrease by one */
			}
		}
	}
}

void sort_arr(int arr[], int &len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (arr[i] > arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void missingNumber(int arr[], int &len, int result[], int &result_len)
{
	// 1, 10, 8, 5
	sort_arr(arr, len);
	for (int i = 0; i < len - 1; i++)
	{
		int current = arr[i];
		int next = arr[i + 1];					 // 1,5,8,10
		for (int j = current + 1; j < next; j++) /* print no.s between current to next  */
		{
			result[result_len++] = j;
		}
	}
	// 2, 3, 4, 6, 7, 9
}

void find_two_sum_number(int arr[], int len)
{
	int target = 18;
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if ((arr[i] + arr[j]) == target)
			{
				printf("\r\n [%d, %d]", arr[i], arr[j]);
			}
		}
	}
}
void merge_two_sorted_arr()
{
	int arr1[] = {1, 2, 3, 4, 5};
	int arr2[] = {11, 12, 13, 14, 15};

	int len1 = sizeof(arr1) / sizeof(arr1[0]);
	int len2 = sizeof(arr2) / sizeof(arr2[0]);

	int arr3[10];
	for (int i = 0; i < len1 + len2; i++)
	{
		if (i < len1)
			arr3[i] = arr1[i];
		else
			arr3[i] = arr2[i - len1];		
		printf("%d%c", arr3[i], i != (len1 + len2 - 1) ? ',' : ' ');
	}
}

int main()
{
	char actno[20];
	char key[1024];
	struct detail_1 d;

	// int a = 10;
	// int *p = &a;
	// int **q = &p;
	// printf("\r\n%d\r\n", **q); // 10

	vector<char *> v1;
	vector<detail_1> v2;
	map<string, detail_1> m1;

	vector<detail_1>::iterator it;
	int i = 0;
	for (it = v2.begin(); it != v2.end(); ++it)
	{
		i++;
		// printf("\r\n %3d %s %s %s %s", i, it->actno, it->long_name, it->sh_name, it->guar_name);
	}

	i = 0;
	char *actno2 = new char[13];
	char *long_name2 = new char[45];
	map<string, detail_1>::iterator it2;
	for (it2 = m1.begin(); it2 != m1.end(); ++it2)
	{
		i++;
		// printf("\r\n %3d %s %s %s %s", i, it2->first.data(), it2->second.actno, it2->second.sh_name, it2->second.guar_name);
		// actno2[13] = '\0';
		strcpy(actno2, it2->second.actno);
		strcpy(long_name2, it2->second.long_name);
		// printf("\r\n %s", long_name2);
	}

	string str;
	char result;
	str = long_name2;
	// result = firstNonRepeating(str);
	// result = firstNonRepeating2("cbbbghkhkc");
	// printf("\r\nstring = %s : %c", long_name2, result);
	delete actno2;
	delete long_name2;

	// string result2 = reverseString4("i love c++");
	// printf("\r\n %s", result2.c_str());

	// string result3 = reverseWordsString("i love c++");
	// printf("\r\n %s", result3.c_str());

	char str2[] = "i love c++";
	// reverseWordsString2(str2);
	// printf("\r\n %s", str2);

	int arr1[] = {2, 2, 3, 4, 5, 3, 4, 1, 1, 88, 45, 45, 88};
	int len = sizeof(arr1) / sizeof(arr1[0]);
	// removeDuplicate(arr1, len);

	// Find missing number
	int arr2[] = {1, 10, 8, 5};
	int len2 = sizeof(arr2) / sizeof(arr2[0]);
	int result2[100];
	int result_len = 0;
	// missingNumber(arr2, len2, result2, result_len);

	// for (int j = 0; j < result_len; j++)
	// {
	// //printf("%d,", arr1[j]);
	// printf("%d,", result2[j]);
	// }

	//

	// find_two_sum_number(arr2, len2);
	merge_two_sorted_arr();

	printf("\r\n");
}
