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
		int jack_cd_count;
		int jill_cd_count;

		scanf("%d %d", &jack_cd_count, &jill_cd_count);

		if (jack_cd_count == 0 && jill_cd_count == 0)
			break;

		set<int> jack_cd_set;

		for (int i = 0; i < jack_cd_count; i++)
		{
			int jack_cd_number;
			scanf("%d", &jack_cd_number);
			jack_cd_set.insert(jack_cd_number);
		}

		int count_of_cd_own_by_both = 0;

		for (int i = 0; i < jill_cd_count; i++)
		{
			int jill_cd_number;
			scanf("%d", &jill_cd_number);
			if (jack_cd_set.find(jill_cd_number) != jack_cd_set.end())
				count_of_cd_own_by_both++;
		}

		cout << count_of_cd_own_by_both << endl;
	}

	return 0;
}

int main11849()
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