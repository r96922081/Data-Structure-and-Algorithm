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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static int algorithm()
{
	while (true)
	{
		int day_count;
		scanf("%d", &day_count);

		if (day_count == 0)
			break;

		multiset<int> urn;

		int bill_count;
		unsigned long long paid_amount = 0;

		while (day_count--)
		{
			scanf("%d", &bill_count);

			while (bill_count--)
			{
				int bill;
				scanf("%d", &bill);
				urn.insert(bill);
			}

			auto it1 = urn.begin();
			int min = *it1;
			urn.erase(it1);

			auto it2 = urn.end();
			it2--;
			int max = *it2;
			urn.erase(it2);

			paid_amount += max - min;
		}

		cout << paid_amount << endl;
	}

	return 0;
}

int main11136()
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