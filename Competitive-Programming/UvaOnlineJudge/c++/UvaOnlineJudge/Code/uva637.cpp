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

int main637()
{
	int pages = 0;
	while (scanf("%d", &pages), pages != 0)
	{
		printf("Printing order for %d pages:\n", pages);

		int sheet_count = (pages + 3) / 4;
		int sum = sheet_count * 4 + 1;
		
		if (pages == 1)
		{
			printf("Sheet 1, front: Blank, 1\n");
			continue;
		}

		for (int i = 0; i < sheet_count; i++)
		{
			int pos1 = i * 2 + 1;
			int pos2 = pos1 + 1;
			int pos3 = sum - pos2;
			int pos4 = sum - pos1;

			// Sheet 1, front: Blank, 1
			printf("Sheet %d, front: ", i + 1);
			if (pos4 <= pages)
				cout << pos4 << ", ";
			else
				cout << "Blank" << ", ";
			cout << pos1 << endl;

			// Sheet 1, back : 2, Blank
			printf("Sheet %d, back : ", i + 1);
			cout << pos2 << ", ";
			if (pos3 <= pages)
				cout << pos3 << endl;
			else
				cout << "Blank" << endl;		
		}
		
	}

	return 0;
}