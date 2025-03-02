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

using namespace std;

static bool must_win(vector<char> sorted)
{
	int s = 0;
	for (int i = 0; i < 6; i++)
	{
		if (sorted[i] == 'g' && s > 0)
			s--;
		else if (sorted[i] == 'b')
			s++;
	}

	if (s >= 2)
		return true;
	else
		return false;
}

int main12247()
{
	// Prince = b, Princess = g
	// sorted result: gbggbb, increasing from left to right 
	// scan from right to left, s = 0
	// if (g && s > 0) s--;
	// else if (b) s++;
	// if (s >= 2) print("must win");
	// else print("may loss");

	while (true)
	{
		vector<char> sorted;

		vector<char> used;
		for (int i = 1; i <= 53; i++)
			used.push_back('\0');

		int n;

		for (int i = 0; i < 5; i++)
		{
			scanf("%d", &n);
			if (n == 0)
				return 0;

			if (i < 3)
				used[n] = 'g';
			else
				used[n] = 'b';
		}

		for (int i = 1; i <= 52; i++)
		{
			if (used[i] != '\0')
				sorted.push_back(used[i]);
		}


		bool must_win_flag = false;
		int insert_pos = 0;
		for (int i = 1; i <= 52; i++)
		{
			if (used[i] == 'b' || used[i] == 'g')
			{
				insert_pos++;
			}				
			else
			{
				sorted.insert(sorted.begin() + insert_pos, 'b');
				if (must_win(sorted))
				{
					must_win_flag = true;
					printf("%d\n", i);
					break;
				}
				sorted.erase(sorted.begin() + insert_pos);
			}
		}

		if (!must_win_flag)
			printf("-1\n");
	}

	return 0;
}