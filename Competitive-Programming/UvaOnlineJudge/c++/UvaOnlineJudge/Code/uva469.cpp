#include <cstdio>
#include <cstdlib>
#include <cstring>
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
#include <list>
#include <iterator>

using namespace std;

static int col_move[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
static int row_move[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
static int row_count = 0;
static int col_count = 0;

static int flood_fill(char the_map[100][100], int row, int col)
{
	if (the_map[row][col] != 'W')
		return 0;

	int ans = 1;
	the_map[row][col] = 'X';

	for (int i = 0; i < 8; i++)
	{
		int new_row = row + row_move[i];
		int new_col = col + col_move[i];

		if (new_row < 0 || new_row >= row_count || new_col < 0 || new_col >= col_count)
			continue;

		ans += flood_fill(the_map, new_row, new_col);
	}

	return ans;
}

static void algorithm()
{
	int test_count;

	cin >> test_count;

	string line;
	getline(cin, line);
	getline(cin, line);

	for (int ti = 0; ti < test_count; ti++)
	{
		if (ti > 0)
			cout << endl;

		bool question = false;
		int row = 0;
		int col = 0;
		int question_row = 0;
		int question_col = 0;
		char the_map[100][100];
		row_count = 0;
		col_count = 0;

		while (!cin.eof())
		{
			col = 0;
			getline(cin, line);
			if (line == "")
				break;

			char c;
			sscanf(line.c_str(), "%c", &c);

			if (c != 'W' && c != 'L')
				question = true;

			if (!question)
			{
				col_count = line.size();
				for (int i = 0; i < col_count; i++)
					the_map[row_count][i] = line[i];

				row_count++;
			}
			else
			{
				sscanf(line.c_str(), "%d %d", &question_row, &question_col);

				char the_map2[100][100];
				memcpy(the_map2, the_map, sizeof(the_map));

				cout << flood_fill(the_map2, question_row - 1, question_col - 1) << endl;
			}
		}
	}
}

int main469()
{
	algorithm();

	return 0;
}