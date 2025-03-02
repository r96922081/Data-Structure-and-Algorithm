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

char space1[100][100];
char space2[100][100];

int main10443()
{
	int T = 0;
	scanf("%d", &T);

	for (int t = 0; t < T; t++)
	{
		if (t >= 1)
			cout << endl;

		int row, col, day;

		scanf("%d %d %d\n", &row, &col, &day);
		for (int i = 0; i < row; i++)
		{
			string line;
			getline(cin, line);
			for (int j = 0; j < col; j++)
			{
				space1[i][j] = line[j];
			}				
		}

		for (int d = 0; d < day; d++)
		{
			char (*src_space)[100][100] = NULL;
			char (*dest_space)[100][100] = NULL;

			if (d % 2 == 0)
			{
				src_space = &space1;
				dest_space = &space2;
			}
			else
			{
				src_space = &space2;
				dest_space = &space1;
			}

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					(*dest_space)[i][j] = (*src_space)[i][j];

					for (int k = 0; k < 4; k++)
					{
						int compared_i = i - 1;
						int compared_j = j;

						if (k == 1)
						{
							compared_i = i + 1;
							compared_j = j;
						}
						else if (k == 2)
						{
							compared_i = i;
							compared_j = j - 1;
						}
						else if (k == 3)
						{
							compared_i = i;
							compared_j = j + 1;
						}


						if (0 <= compared_i && compared_i < row && 0 <= compared_j && compared_j < col)
						{
							char comparing_char = (*src_space)[i][j];
							char compared_char = (*src_space)[compared_i][compared_j];
							if ((comparing_char == 'R' && compared_char == 'P') ||
								(comparing_char == 'P' && compared_char == 'S') ||
								(comparing_char == 'S' && compared_char == 'R'))
							{
								(*dest_space)[i][j] = compared_char;
								break;
							}
						}
					}
				}
			}
		}

		char (*space)[100][100] = NULL;
		if (day % 2 == 1)
			space = &space2;
		else
			space = &space1;

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				cout << (*space)[i][j];
			cout << endl;
		}
			
	}

	return 0;
}