#include <cstdio>
#include "stdlib.h"
#include "string.h"
#include <limits>
#include <cstddef>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <tuple>
#include <sstream>

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static void print_diff(int first, int last)
{
	printf("-");

	string first_s = to_string(first);
	string last_s = to_string(last);

	if (last_s.size() > first_s.size())
		printf("%d", last);
	else
	{
		for (int i = 0; i < last_s.size(); i++)
		{
			if (first_s[i] != last_s[i])
			{
				for (int j = i; j < last_s.size(); j++)
					printf("%c", last_s[j]);
				break;
			}
		}
	}
}

int main12085()
{
	for (int ti = 1; ; ti++)
	{
		int n = 0;
		scanf("%d", &n);

		if (n == 0)
			break;

		vector<int> numbers;
		for (int i = 0; i < n; i++)
		{
			int temp = 0;
			scanf("%d", &temp);
			numbers.push_back(temp);
		}

		cout << "Case " << ti << ":";

		int prev = -1;
		int first = -1;
		bool consecutive = false;

		for (int i = 0; i < n; i++)
		{
			if (numbers[i] != prev + 1)
			{
				if (consecutive)
				{
					print_diff(first, prev);
				}
				
				printf("\n");
				printf("0");
				printf("%d", numbers[i]);
				first = numbers[i];
				consecutive = false;
			}
			else
			{
				consecutive = true;
			}

			prev = numbers[i];
		}

		if (consecutive)
		{
			print_diff(first, prev);
		}

		printf("\n");

		cout << endl;
	}

	return 0;
}













//////////////////// auxiliary functions /////////////////////

static char to_lower(char c)
{
	if ('a' <= c && c <= 'z')
		return c;
	else
		return c - 'A' + 'a';
}

static string to_lower2(string s)
{
	string ret = "";
	for (int i = 0; i < s.size(); i++)
	{
		ret += to_lower(s[i]);
	}

	return ret;
}