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
#include <functional>

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static int algorithm()
{
	int number_count;

	while (scanf("%d", &number_count), number_count != 0)
	{
		priority_queue<int, std::vector<int>, std::greater<int>> numbers;
		int temp = 0;
		for (int i = 0; i < number_count; i++)
		{
			scanf("%d", &temp);
			numbers.push(temp);
		}
			
		int cost = 0;
		while (true)
		{
			int sum = numbers.top();
			numbers.pop();
			sum += numbers.top();
			numbers.pop();

			cost += sum;

			if (numbers.empty())
				break;

			numbers.push(sum);
		}

		cout << cost << endl;
	}

	return 0;
}

int main10954()
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