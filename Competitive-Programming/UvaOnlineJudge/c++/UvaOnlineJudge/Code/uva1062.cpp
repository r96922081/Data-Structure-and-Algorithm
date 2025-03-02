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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static int algorithm()
{
	string line = "";
	for (int i = 1; getline(cin, line), line != "end";i++)
	{
		vector<char> s;
		s.push_back('A' - 1);

		for (int i = line.size() - 1; i >= 0; i--)
		{
			char c = line[i];

			vector<char>::reverse_iterator it = s.rbegin();
			for (; it != s.rend(); it++)
			{
				if (c >= *it)
				{
					*it = c;
					break;
				}
			}

			if (it == s.rend())
				s.insert(s.begin(), c);
		}

		printf("Case %d: %d\n", i, s.size());
	}

	return 0;
}

int main1062()
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