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

static void right_rotate(vector<vector<char>>& v)
{
	vector<vector<char>> temp_v = v;
	int n = v.size();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			v[i][j] = temp_v[n - 1 - j][i];
}

static int algorithm()
{
	int N, n;
	while (true)
	{
		scanf("%d %d\n", &N, &n);
		if (N == 0)
			break;

		vector<vector<char>> N_square(N, vector<char>(N, ' '));
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				scanf("%c", &N_square[i][j]);
			scanf("\n");
		}

		vector<vector<char>> n_square(n, vector<char>(n, ' '));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				scanf("%c", &n_square[i][j]);
			scanf("\n");
		}

		for (int T = 0; T < 4; T++)
		{
			int number = 0;

			for (int i = 0; i + n <= N; i++)
			{
				for (int j = 0; j + n <= N; j++)
				{
					bool match = true;
					for (int k = 0; k < n; k++)
						for (int l = 0; l < n; l++)
						{
							if (N_square[i + k][j + l] != n_square[k][l])
							{
								match = false;
								break;
							}
						}

					if (match)
						number++;
				}
			}

			printf("%d", number);
			if (T == 3)
				printf("\n");
			else
				printf(" ");

			right_rotate(n_square);
		}
	}

	return 0;
}

int main10855()
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

static void Test1()
{
	vector<vector<char>> v1(3, vector<char>(3, ' '));
	v1[0][0] = 1;
	v1[0][1] = 2;
	v1[0][2] = 3;
	v1[1][0] = 4;
	v1[1][1] = 5;
	v1[1][2] = 6;
	v1[2][0] = 7;
	v1[2][1] = 8;
	v1[2][2] = 9;

	right_rotate(v1);
	Check(v1[0][0] == 7);
	Check(v1[0][1] == 4);
	Check(v1[0][2] == 1);
	Check(v1[1][0] == 8);
	Check(v1[1][1] == 5);
	Check(v1[1][2] == 2);
	Check(v1[2][0] == 9);
	Check(v1[2][1] == 6);
	Check(v1[2][2] == 3);

	vector<vector<char>> v2(1, vector<char>(1, 1));
	right_rotate(v2);
	Check(v2[0][0] == 1);
}

static void UnitTest()
{
	Test1();
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