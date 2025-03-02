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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static int row_count = 0;
static int col_count = 0;
static int pos_row = 0;
static int pos_col = 0;

static int direction_row = 0;
static int direction_col = 1;

static int start_pos_row = 0;
static int start_pos_col = 0;

static bool moved = false;

static vector<vector<int>>* maze = NULL;

static vector<int> statistics(5, 0);

static void move()
{
	int next_row = pos_row + direction_row;
	int next_col = pos_col + direction_col;
	
	statistics[(*maze)[next_row][next_col]]--;
	(*maze)[next_row][next_col]++;
	statistics[(*maze)[next_row][next_col]]++;
	
	pos_col = next_col;
	pos_row = next_row;

	moved = true;
}

static bool valid_move(int pos_row, int pos_col)
{
	if (pos_row < 0 || row_count <= pos_row || pos_col < 0 || col_count <= pos_col)
		return false;

	if ((*maze)[pos_row][pos_col] == -1)
		return false;

	return true;
}

static bool wall_on_right(int pos_row, int pos_col)
{
	int right_row = pos_row;
	int right_col = pos_col;

	if (direction_col == 1)
		right_row += 1;
	else if (direction_col == -1)
		right_row -= 1;
	else if (direction_row == 1)
		right_col -= 1;
	else
		right_col += 1;

	if (right_row < 0 || row_count <= right_row || right_col < 0 || col_count <= right_col)
		return true;
	else if ((*maze)[right_row][right_col] == -1)
		return true;
	else
		return false;
}

int main556()
{
	while (true)
	{
		row_count = 0;
		col_count = 0;
		pos_row = 0;
		pos_col = 0;

		direction_row = 0;
		direction_col = 1;
		moved = false;

		maze = NULL;

		for (int i = 0; i < 5; i++)
			statistics[i] = 0;

		scanf("%d %d", &row_count, &col_count);

		if (row_count == 0 && col_count == 0)
			break;

		start_pos_row = row_count - 1;
		start_pos_col = 0;
		pos_row = start_pos_row;
		pos_col = start_pos_col;

		maze = new vector<vector<int>>(row_count, vector<int>(col_count, 0));

		for (int i = 0; i < row_count; i++)
		{
			for (int j = 0; j < col_count; j++)
			{
				int temp = 0;
				scanf("%1d", &temp);
				if (temp == 1)
					(*maze)[i][j] = -1;
				else
				{
					(*maze)[i][j] = 0;
					statistics[0] += 1;
				}					
			}
		}

		do
		{
			int next_row = pos_row + direction_row;
			int next_col = pos_col + direction_col;

			if (valid_move(next_row, next_col))
			{
				if (wall_on_right(next_row, next_col))
				{
					move();
				}
				else
				{
					move();

					if (pos_row == start_pos_row && pos_col == start_pos_col)
						break;

					// Take right turn
					if (direction_row == 1)
					{
						direction_row = 0;
						direction_col = -1;
					}
					else if (direction_row == -1)
					{
						direction_row = 0;
						direction_col = 1;
					}
					else if (direction_col == 1)
					{
						direction_row = 1;
						direction_col = 0;
					}
					else
					{
						direction_row = -1;
						direction_col = 0;
					}

					move();
				}
			}
			else
			{
				// Take left turn
				if (direction_row == 1)
				{
					direction_row = 0;
					direction_col = 1;
				}
				else if (direction_row == -1)
				{
					direction_row = 0;
					direction_col = -1;
				}
				else if (direction_col == 1)
				{
					direction_row = -1;
					direction_col = 0;
				}
				else
				{
					direction_row = 1;
					direction_col = 0;
				}
			}

		} while (!(moved && pos_row == start_pos_row && pos_col == start_pos_col));

		printf("%3d%3d%3d%3d%3d\n", statistics[0], statistics[1],
			statistics[2], statistics[3], statistics[4]);
		
		if (maze)
			delete maze;
	}

	return 0;
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