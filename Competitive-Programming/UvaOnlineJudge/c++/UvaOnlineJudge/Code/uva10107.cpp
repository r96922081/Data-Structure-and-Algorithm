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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////


static int algorithm()
{
	unsigned long long n;

	vector<unsigned long long> all;

	while (scanf("%llu", &n) == 1)
	{
		all.push_back(n);
		for (int i = all.size() - 1; i > 0; i--)
		{
			if (all[i] < all[i - 1])
			{
				unsigned long long temp = all[i];
				all[i] = all[i - 1];
				all[i - 1] = temp;
			}
		}

		if (all.size() % 2 == 1)
			cout << all[all.size() / 2] << endl;
		else
		{
			unsigned long long a = all[all.size() / 2];
			unsigned long long b = all[all.size() / 2 - 1];

			cout << (a + b) / 2 << endl;
		}

	}

	return 0;
}

int main10107()
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