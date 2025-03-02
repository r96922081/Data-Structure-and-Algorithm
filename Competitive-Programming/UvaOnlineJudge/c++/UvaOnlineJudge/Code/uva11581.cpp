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
	int T = 0;
	scanf("%d\n", &T);

	for (int ti = 0; ti < T; ti++)
	{
		scanf("\n");

		char grid[3][3];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				char temp = 0;
				scanf("%c", &temp);
				if (temp == '0')
					grid[i][j] = 0;
				else
					grid[i][j] = 1;
			}
				
			scanf("\n");
		}

		int answer;

		int dx[4] = { 1, 0, -1, 0 };
		int dy[4] = { 0, 1, 0, -1 };

		for (answer = -1; ; answer++)
		{
			bool all_zero = true;
			bool break_i = false;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (grid[i][j] != 0)
					{
						all_zero = false;
						break_i = true;
						break;
					}
				}
				if (break_i)
					break;
			}

			if (all_zero)
				break;		

			char grid2[3][3];
			memcpy(grid2, grid, 9);

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{				
					grid[i][j] = 0;
					for (int k = 0; k < 4; k++)
					{
						int i2 = i + dx[k];
						int j2 = j + dy[k];

						if (0 <= i2 && i2 <= 2 && 0 <= j2 && j2 <= 2)
						{
							grid[i][j] += grid2[i2][j2];
						}

						grid[i][j] %= 2;
					}
				}
			}
		}

		cout << answer << endl;
	}

	return 0;
}

int main11581()
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