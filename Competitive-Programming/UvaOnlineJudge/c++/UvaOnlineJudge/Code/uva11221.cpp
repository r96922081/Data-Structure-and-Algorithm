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

using namespace std;

static bool IsPalindrome(string s)
{
	for (int i = 0; i < s.size(); i++)
		if (s[i] != s[s.size() - 1 - i])
			return false;

	return true;
}

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

int main11221()
{
	int T;
	scanf("%d\n", &T);

	for (int t = 1; t <= T; t++)
	{
		string line2;
		getline(cin, line2);

		string line = "";
		for (int i = 0; i < line2.size(); i++)
			if ('a' <= line2[i] && line2[i] <= 'z')
				line += line2[i];

		vector<string> s = split(line.c_str());

		int K = sqrt(line.size());
		if (K * K != line.size())
		{
			cout << "Case #" << t << ":" << endl << "No magic :(" << endl;
			continue;
		}

		bool magic = true;

		vector<vector<char>> matrix;

		for (int i = 0; i < line.size(); i++)
		{
			if (i % K == 0)
				matrix.push_back(vector<char>());

			matrix.back().push_back(line[i]);
		}

		string s1 = "";

		for (int i = 0; i < K; i++)
			for (int j = 0; j < K; j++)
				s1 += matrix[i][j];

		string s2 = "";
		for (int i = 0; i < K; i++)
			for (int j = 0; j < K; j++)
				s2 += matrix[j][i];

		if (s1 != s2)
		{
			cout << "Case #" << t << ":" << endl << "No magic :(" << endl;
			continue;
		}
			
		s2 = "";
		for (int i = 0; i < K; i++)
			for (int j = 0; j < K; j++)
				s2 += matrix[K - 1 - i][K - 1 - j];

		if (s1 != s2)
		{
			cout << "Case #" << t << ":" << endl << "No magic :(" << endl;
			continue;
		}

		s2 = "";
		for (int i = 0; i < K; i++)
			for (int j = 0; j < K; j++)
				s2 += matrix[K - 1 - j][K - 1 - i];

		if (s1 != s2)
		{
			cout << "Case #" << t << ":" << endl << "No magic :(" << endl;
			continue;
		}

		cout << "Case #" << t << ":" << endl << K << endl;
	}

	return 0;
}