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

using namespace std;

bool board_mark[5][5];
int number_map[76];

static bool check_bingo()
{
	for (int i = 0; i < 5; i++)
	{
		bool bingo = true;
		for (int j = 0; j < 5; j++)
		{
			if (board_mark[i][j] == false)
			{
				bingo = false;
				break;
			}
		}
		if (bingo)
			return true;
	}

	for (int i = 0; i < 5; i++)
	{
		bool bingo = true;
		for (int j = 0; j < 5; j++)
		{
			if (board_mark[j][i] == false)
			{
				bingo = false;
				break;
			}
		}
		if (bingo)
			return true;
	}

	bool bingo = true;
	for (int i = 0; i < 5; i++)
	{
		if (board_mark[i][i] == false)
		{
			bingo = false;
			break;
		}
	}
	if (bingo)
		return true;

	bingo = true;
	for (int i = 0; i < 5; i++)
	{
		if (board_mark[4 - i][i] == false)
		{
			bingo = false;
			break;
		}
	}
	if (bingo)
		return true;

	return false;
}

int main10813()
{
	int T;
	scanf("%d", &T);

	while (T--)
	{
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				board_mark[i][j] = false;
		board_mark[2][2] = true;

		for (int i = 1; i <= 75; i++)
			number_map[i] = -1;

		for (int i = 0; i < 25; i++)
		{
			if (i == 12)
				continue;
			else
			{
				int n;
				scanf("%d", &n);
				number_map[n] = i;
			}
		}

		bool bingo = false;		

		for (int i = 1; i <= 75; i++)
		{
			int n;
			scanf("%d", &n);
			if (bingo)
				continue;

			int pos = number_map[n];

			if (pos == -1)				
				continue;

			board_mark[pos / 5][pos % 5] = true;

			if (check_bingo())
			{
				cout << "BINGO after " << i << " numbers announced" << endl;
				bingo = true;
			}
		}
	}

	return 0;
}