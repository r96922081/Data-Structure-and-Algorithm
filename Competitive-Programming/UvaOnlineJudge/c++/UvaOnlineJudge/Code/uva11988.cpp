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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

inline void append_str(int l, int r, string& output, char& prev_sign, string& line)
{
	if (l == -1)
		return;

	if (prev_sign == ']')
		output = output + line.substr(l, r - l + 1);
	else
		output = line.substr(l, r - l + 1) + output;
}

static int algorithm()
{
	string line = "";
	while (getline(cin, line))
	{ 
		string output = "";
		int l = -1;
		int r = -1;
		char prev_sign = ']';

		for (int i = 0; i < line.size(); i++)
		{
			char c = line[i];
			if (c == ']' || c == '[')
			{
				append_str(l, r, output, prev_sign, line);
				prev_sign = c;
				l = -1;
				r = -1;
			}
			else
			{
				if (l == -1)
					l = i;
				r = i;
			}
		}
	
		append_str(l, r, output, prev_sign, line);

		cout << output << endl;
	}

	return 0;
}

int main11988()
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