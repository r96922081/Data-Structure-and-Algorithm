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

static string to_lower(string s)
{
	string ret = "";
	for (int i = 0; i < s.size(); i++)
	{
		ret += to_lower(s[i]);
	}

	return ret;
}

static bool mycompare(char a, char b)
{
	if (to_lower(a) == to_lower(b))
		return a < b;
	else
		return to_lower(a) < to_lower(b);
}

int main195()
{
	int T;
	scanf("%d\n", &T);

	while (T--)
	{
		string word;
		cin >> word;
		sort(&word[0], &word[word.size()], mycompare);

		do {
			cout << word << endl;
		} while (next_permutation(&word[0], &word[word.size()], mycompare));
	}

	return 0;
}