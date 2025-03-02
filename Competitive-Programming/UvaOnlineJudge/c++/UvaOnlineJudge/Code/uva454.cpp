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

int main454()
{
	int T;
	scanf("%d\n\n", &T);

	for (int Ti = 0; Ti < T; Ti++)
	{
		if (Ti > 0)
			cout << endl;

		vector<pair<string, string>> all_phrases;

		string line;
		while (getline(cin, line) && line != "")
		{
			string line_no_space = "";
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] != ' ')
				{
					line_no_space += line[i];
				}
			}	

			sort(&line_no_space[0], &line_no_space[line_no_space.size()]);

			all_phrases.push_back(pair<string, string>(line_no_space, line));
		}

		sort(all_phrases.begin(), all_phrases.end());

		map<string, int> count;

		for (auto it = all_phrases.begin(); it != all_phrases.end(); it++)
		{
			if (count.find(it->first) == count.end())
				count.insert(pair<string, int>(it->first, 1));
			else
			{
				count[it->first]++;
			}
		}

		for (auto it = all_phrases.begin(); it != all_phrases.end();)
		{
			if (count[it->first] == 1)
				it = all_phrases.erase(it);
			else
				it++;
		}

		if (all_phrases.size() == 0)
			continue;

		string current_string = all_phrases[0].first;
		int start = 0;

		vector<pair<string, string>> answer;

		for (int i = 1; i < all_phrases.size(); i++)
		{
			if (all_phrases[i].first != current_string)
			{
				vector<string> p;
				
				for (auto it = all_phrases.begin() + start; it != all_phrases.begin() + i; it++)
				{
					p.push_back(it->second);
				}

				sort(p.begin(), p.end());

				for (auto it = p.begin(); it != p.end(); it++)
					for (auto it2 = it + 1; it2 != p.end(); it2++)
						answer.push_back(pair<string, string>(*it, *it2));

				start = i;
				current_string = all_phrases[i].first;
			}
		}

		vector<string> p;
		for (auto it = all_phrases.begin() + start; it != all_phrases.end(); it++)
		{
			p.push_back(it->second);
		}

		sort(p.begin(), p.end());

		for (auto it = p.begin(); it != p.end(); it++)
			for (auto it2 = it + 1; it2 != p.end(); it2++)
				answer.push_back(pair<string, string>(*it, *it2));

		stable_sort(answer.begin(), answer.end());

		for (int i = 0; i < answer.size(); i++)
			cout << answer[i].first << " = " << answer[i].second << endl;

	}

	return 0;
}