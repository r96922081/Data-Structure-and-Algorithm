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

int main11340()
{
	int char_count[256];

	int T = 0;
	scanf("%d", &T);

	while (T--)
	{
		for (int i = 0; i < 256; i++)
			char_count[i] = 0;

		int K = 0;
		scanf("%d\n", &K);

		map<unsigned char, int> mapping;
		unsigned char c;
		int cent;

		for (int i = 0; i < K; i++)
		{
			scanf("%c %d\n", &c, &cent);

			mapping.insert(pair<unsigned char, int>(c, cent));
		}

		int M = 0;
		scanf("%d\n", &M);

		for (int i = 0; i < M; i++)
		{
			unsigned char c;
			while (c = getchar(), c != '\n')
				char_count[c]++;
		}

		int dollar = 0;
		for (auto it = mapping.begin(); it != mapping.end(); it++)
		{
			dollar += char_count[it->first] * it->second;
		}

		printf("%.2lf$\n", (double)dollar / 100);
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