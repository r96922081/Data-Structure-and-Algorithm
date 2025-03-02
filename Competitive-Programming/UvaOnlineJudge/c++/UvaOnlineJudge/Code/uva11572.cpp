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
#include <cassert>
#include <bitset>
#include <stack>
#include <queue>
#include <limits>

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static int algorithm()
{
	int N;

	scanf("%d", &N);

	while (N--)
	{
		int n = 0;
		scanf("%d", &n);

		vector<int> input1;
		map<int, int> input2;
		for (int i = 0; i < n; i++)
		{
			int temp;
			scanf("%d", &temp);
			input1.push_back(temp);
		}

		int longest_length = 0;

		int start = 0;

		for (int i = 0; i < input1.size(); i++)
		{
			auto it = input2.find(input1[i]);
			if (it != input2.end())
			{
				int length = ((i - 1) - start) + 1;
				longest_length = max(longest_length, length);

				int stop = it->second;
				for (int j = start; j <= stop; j++)
				{
					input2.erase(input1[j]);
				}

				start = stop + 1;
			}

			input2.insert(pair<int, int>(input1[i], i));
		}

		longest_length = max(longest_length, n - start);
		cout << longest_length << endl;
	}

	return 0;
}

int main11572()
{
	//extern void UnitTest();
	//UnitTest();
	return algorithm();
}

static void Check(bool expr)
{
	if (!expr)
	{
		int a = 1;
		int b = 2;
		int c = a / b;
		assert(false);
	}

}

///////////////////// UT //////////////////////

static void UnitTest()
{

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