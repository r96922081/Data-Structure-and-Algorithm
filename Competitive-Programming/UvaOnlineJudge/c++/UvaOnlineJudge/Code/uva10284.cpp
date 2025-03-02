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

using namespace std;

char board[8][8];

static bool valid_pos(int i, int j)
{
	if (0 <= i && i < 8 && 0 <= j && j < 8)
		return true;
	else
		return false;
}

#define Check1(i, j) { \
                         if (!valid_pos(i, j))\
                              break;\
                         char d = board[i][j];\
                         if (d == 's' || d == 'd')\
                             board[i][j] = 'd';\
                         else\
                             break;}

static void Check2(int i, int j)
{
		if (valid_pos(i, j)) 
		{
			char d = board[i][j]; 
			if (d == 's')
				board[i][j] = 'd'; 
		}
}

int main10284()
{
	char line[100];

	while (fgets(line, 150, stdin) != NULL)
	{
		// remove \n
		char *pos;
		if ((pos = strchr(line, '\n')) != NULL)
			*pos = '\0';

        // 'd' for danger, 's' for safe
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				board[i][j] = 's';

		int row = 0;
		int col = 0;
		for (int i = 0; i < strlen(line); i++)
		{
			char c = line[i];
			if (c == '/')
			{
				row++;
				col = 0;
			}
			else if ('1' <= c && c <= '9')
			{
				col += (c - '1' + 1);
			}
			else
			{
				board[row][col] = c;
				col++;
			}
		}

		// print chess board
		/*for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				printf("%c", board[i][j]);
			printf("\n");
		}*/

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				// 'd' for danger, 's' for safe
				// pnbrqk, Black, top
				// PNBRQK, White, bottom
				char c = board[i][j];

				if (c == 'q' || c == 'Q' || c == 'r'  || c == 'R')
				{
					for (int k = i - 1; k >= 0; k--)
						Check1(k, j);
					for (int k = i + 1; k < 8; k++)
						Check1(k, j);
					for (int l = j - 1; l >= 0; l--)
						Check1(i, l);
					for (int l = j + 1; l < 8; l++)
						Check1(i, l);
				}
				
				if (c == 'q' || c == 'Q' || c == 'b' || c == 'B')
				{
					for (int k = i - 1, l = j - 1; k >= 0 && l >= 0; k--, l--)
						Check1(k, l);
					for (int k = i - 1, l = j + 1; k >= 0 && l < 8; k--, l++)
						Check1(k, l);
					for (int k = i + 1, l = j + 1; k < 8 && l < 8; k++, l++)
						Check1(k, l);
					for (int k = i + 1, l = j - 1; k < 8 && l >= 0; k++, l--)
						Check1(k, l);
				}

				if (c == 'n' || c == 'N')
				{
					Check2(i - 1, j - 2);
					Check2(i - 1, j + 2);
					Check2(i + 1, j - 2);
					Check2(i + 1, j + 2);
					Check2(i - 2, j - 1);
					Check2(i - 2, j + 1);
					Check2(i + 2, j - 1);
					Check2(i + 2, j + 1);
				}

				if (c == 'k' || c == 'K')
				{
					Check2(i - 1, j - 1);
					Check2(i - 1, j + 1);
					Check2(i + 1, j - 1);
					Check2(i + 1, j + 1);
					Check2(i, j - 1);
					Check2(i, j + 1);
					Check2(i + 1, j);
					Check2(i - 1, j);
				}

				if (c == 'p')
				{
					Check2(i + 1, j + 1);
					Check2(i + 1, j - 1);
				}

				if (c == 'P')
				{
					Check2(i - 1, j + 1);
					Check2(i - 1, j - 1);
				}
			}
		}

		int safe = 0;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (board[i][j] == 's')
					safe++;
		printf("%d\n", safe);
	}

	return 0;
}