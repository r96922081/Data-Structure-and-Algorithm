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

using namespace std;

int main11507()
{
	// +x = 0, -x = 1, +y = 2, -y = 3, +z = 4, -z = 5;

	int fsm[6][6] = 
	{
		{0, 0, 2, 3, 4, 5},
		{0, 0, 3, 2, 5, 4},
		{ 0, 0, 1, 0, 2, 2 },
		{ 0, 0, 0, 1, 3, 3 },
		{ 0, 0, 4, 4, 1, 0 },
		{ 0, 0, 5, 5, 0, 1 },
	};

	map<string, int> s_to_i = 
	{ 
		{"+x", 0 },{ "-x", 1 },
		{ "+y", 2 },{ "-y", 3 },
		{ "+z", 4 },{ "-z", 5 },
	};

	map<int, string> i_to_s =
	{
		{ 0, "+x" },{ 1,"-x" },
		{ 2, "+y" },{ 3, "-y" },
		{ 4, "+z" },{ 5, "-z" },
	};

	int N = 0;
	while (scanf("%d", &N), N)
	{
		char s[3];
		int answer = 0;

		while (N != 1)
		{
			scanf("%s", &s);
			N--;

			if (strcmp(s, "No") == 0)
				continue;

			int next_step = s_to_i[s];
			answer = fsm[answer][next_step];
		}

		printf("%s\n", i_to_s[answer].c_str());
	}

	return 0;
}