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

int result[100000];

static int algorithm()
{
	int N;

	scanf("%d", &N);

	for (int Ni = 0; Ni < N; Ni++)
	{
		if (Ni > 0)
			cout << endl;

		int battlefield_count, green_count, blue_count;
		scanf("%d %d %d", &battlefield_count, &green_count, &blue_count);

		int temp = 0;

		priority_queue<int> green;
		for (int i = 0; i < green_count; i++)
		{
			scanf("%d", &temp);
			green.push(temp);
		}

		priority_queue<int> blue;
		for (int i = 0; i < blue_count; i++)
		{
			scanf("%d", &temp);
			blue.push(temp);
		}

		while (green.size() != 0 && blue.size() != 0)
		{
			int real_battle_count = min(battlefield_count, (int)green.size());
			real_battle_count = min(real_battle_count, (int)blue.size());

			for (int i = 0; i < real_battle_count; i++)
			{
				result[i] = green.top() - blue.top();
				green.pop();
				blue.pop();
			}

			for (int i = 0; i < real_battle_count; i++)
			{
				if (result[i] > 0)
					green.push(result[i]);
				else if (result[i] < 0)
					blue.push(-result[i]);
			}
		}

		if (green.size() == 0 && blue.size() == 0)
		{
			cout << "green and blue died" << endl;
		}
		else if (green.size() != 0)
		{
			cout << "green wins" << endl;
			while (!green.empty())
			{
				cout << green.top() << endl;
				green.pop();
			}
		}
		else
		{
			cout << "blue wins" << endl;
			while (!blue.empty())
			{
				cout << blue.top() << endl;
				blue.pop();
			}
		}
	}

	return 0;
}

int main978()
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