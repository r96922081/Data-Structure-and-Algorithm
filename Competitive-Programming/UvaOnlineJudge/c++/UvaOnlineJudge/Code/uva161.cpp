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

int main161()
{
	int time;

	vector<int> times;

	while (true)
	{
		int check_second = 91;
		while (scanf("%d", &time), time != 0)
		{
			times.push_back(time);
		}

		for (int i = 0; i < times.size(); i++)
			check_second = min(check_second, times[i]);

		check_second -= 5;

		bool hit = true;
		for (; check_second <= 5 * 60 * 60; check_second++)
		{
			hit = true;
			for (int i = 0; i < times.size(); i++)
			{
				int cycle = times[i];
				if ((check_second % (cycle * 2)) >= (cycle - 5))
				{
					hit = false;
					break;
				}
			}

			if (hit)
			{
				int sec = check_second % 60;
				check_second /= 60;
				int min = check_second % 60;
				int hour = check_second / 60;
				printf("%02d:%02d:%02d\n", hour, min, sec);
				break;
			}
		}

		if (!hit)
			cout << "Signals fail to synchronise in 5 hours" << endl;

		times.clear();
		scanf("%d", &time);
		if (time == 0)
			return 0;

		times.push_back(time);
	}



	return 0;
}