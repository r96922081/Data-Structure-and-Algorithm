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

static int algorithm()
{
	int dimension = 0;
	while (scanf("%d", &dimension) == 1)
	{
		int max_sum = 0;
		int count = (int)pow(2, dimension);

		map<int, pair<int, int>> all;

		for (int i = 0; i < count; i++)
		{
			int w = 0;
			scanf("%d", &w);
			all.insert(pair<int, pair<int, int>>(i, pair<int, int>(w, w)));
		}

		for (int i = 0; i < count; i++)
		{
			int sum2 = all.find(i)->second.first;

			bitset<14> b(all.find(i)->first);

			for (int j = 0; j < dimension; j++)
			{
				bitset<14> b2 = b;
				b2.flip(j);
				all.find(i)->second.second += all.find((int)b2.to_ulong())->second.first;
			}
		}

		for (int i = 0; i < count; i++)
		{
			bitset<14> b(all.find(i)->first);

			for (int j = 0; j < dimension; j++)
			{
				bitset<14> b2 = b;
				b2.flip(j);
				int temp_sum = all.find(i)->second.second + all.find((int)b2.to_ulong())->second.second -
					all.find(i)->second.first - all.find((int)b2.to_ulong())->second.first;

				if (temp_sum > max_sum)
					max_sum = temp_sum;
			}
		}

		cout << max_sum << endl;
	}

	return 0;
}

int main10264()
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