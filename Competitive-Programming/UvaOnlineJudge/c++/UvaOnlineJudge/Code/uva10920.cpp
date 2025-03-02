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

static void print_answer(int sz, int row, int col)
{
	printf("Line = %d, column = %d.\n", sz - row,col + 1);
}

static int algorithm()
{
	int sz;
	long long p;
	while (true)
	{
		scanf("%d %lld\n", &sz, &p);
		if (sz == 0)
			break;

		int next_row[4] = { -1, 0, 1, 0 }; // up, left, down, right 
		int next_col[4] = { 0, -1, 0, 1 }; // up, left, down, right 

		if (p == 1)
		{
			print_answer(sz, sz / 2, sz / 2);
		}
		else
		{
			long long n = (long long)(sqrt(p));
			if (n % 2 == 0)
				n--;

			// The diagonal from center to top-right corner has rules
			// start walking from that point
			int pos_row = sz / 2 - (n - 1) / 2;
			int pos_col = sz / 2 + (n - 1) / 2;

			int turn1 = 1;
			int turn2 = turn1 + n;
			int turn3 = turn2 + n + 1;
			int turn4 = turn3 + n + 1;

			int direction = 0;

			for (long long i = n * n, step = 0; i < p; i++, step++)
			{
				if (step == turn1)
					direction = 1;
				else if (step == turn2)
					direction = 2;
				else if (step == turn3)
					direction = 3;
				else if (step == turn4)
					direction = 0;

				pos_row += next_row[direction];
				pos_col += next_col[direction];
			}

			print_answer(sz, pos_row, pos_col);
		}

	}

	return 0;
}

int main10920()
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