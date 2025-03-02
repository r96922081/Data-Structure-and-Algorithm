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

using namespace std;

static vector<string> split(const char *str, char c = ' ')
{
	vector<string> result;

	do
	{
		const char *begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(string(begin, str));
	} while (0 != *str++);

	return result;
}

static vector<string> split(string str, char c = ' ')
{
	return split(str.c_str(), c);
}

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

int main10812()
{
	int T = 0;
	scanf("%d", &T);

	while (T--)
	{
		int sum = 0;
		int diff = 0;
		scanf("%d %d", &sum, &diff);

		int A = sum + diff;
		if (A % 2 == 1 || A < 0)
		{
			cout << "impossible" << endl;
			continue;
		}

		A /= 2;
		int B = sum - A;

		if (B < 0)
		{
			cout << "impossible" << endl;
			continue;
		}

		cout << A << " " << B << endl;
	}

	return 0;
}