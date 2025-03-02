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


static string get_lower_string(string s)
{
	string ret = "";
	for (int i = 0; i < s.size(); i++)
	{
		if ('a' <= s[i] && s[i] <= 'z')
			ret += s[i];
		else
		{
			ret += s[i] - 'A' + 'a';
		}
	}

	return ret;
}

int main156()
{
	vector<tuple<string, string>> dic;
	vector<string> answer;

	while (true)
	{
		string line;
		getline(cin, line);
		if (line == "#")
			break;

		vector<string> dic2 = split(line);
		for (int i = 0; i < dic2.size(); i++)
		{
			string key = get_lower_string(dic2[i]);
			sort(&key[0], &key[key.size()], [](char a, char b) { return a < b; });
			dic.push_back(tuple<string, string>(key, dic2[i]));
		}
	}

	if (dic.size() == 0)
		return 0;

	sort(dic.begin(), dic.end(), 
		[](tuple<string, string>& a, tuple<string, string>& b)
		{ return get<0>(a) < get<0>(b);	}
	);

	string prev = "";
	int size = 0;

	for (vector<tuple<string, string>>::iterator it = dic.begin(); it != dic.end(); it++)
	{
		string key = get<0>(*it);
		if (prev == key)
			size++;
		else
		{
			if (size == 1)
				answer.push_back(get<1>(*(it - 1)));

			prev = key;
			size = 1;
		}
	}

	if (get<0>(*(dic.end() - 1)) != get<0>(*(dic.end() - 2)))
		answer.push_back(get<1>(*(dic.end() - 1)));

	sort(answer.begin(), answer.end());

	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << endl;

	return 0;
}