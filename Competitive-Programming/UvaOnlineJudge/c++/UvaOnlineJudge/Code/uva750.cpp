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

using namespace std;

int row[8];
vector<vector<int>> solutions;

static bool check_position(int col, int row2)
{
	for (int i = 0; i < col; i++)
	{
		if (row[i] == row2)
			return false;

		if (abs(row[i] - row2) == abs(i - col))
			return false;
	}

	return true;
}

static void find_8_queens(int col)
{
	if (col == 8)
	{
		vector<int> solution;
		for (int i = 0; i < 8; i++)
			solution.push_back(row[i] + 1);

		solutions.push_back(solution);
		return;
	}

	for (int i = 0; i < 8; i++)
	{
		if (check_position(col, i))
		{
			row[col] = i;
			find_8_queens(col + 1);
		}
	}
}

static void algorithm()
{
	printf("SOLN       COLUMN\n");
	printf(" #      ");
	for (int i = 0; i < 8; i++)
	{
		if (i > 0)
			cout << " ";

		cout << i + 1;
	}

	cout << endl;
	cout << endl;

	find_8_queens(0);

	int test_count = 0;
	cin >> test_count;

	while (test_count--)
	{
		int row;
		int col;

		cin >> row >> col;

		int hit_count = 0;

		for (int i = 0; i < solutions.size(); i++)
		{
			vector<int>& solution = solutions[i];
			if (solution[col - 1] == row)
			{
				hit_count++;

				printf("%2d      ", hit_count);

				for (int j = 0; j < 8; j++)
				{
					if (j > 0)
						cout << " ";

					cout << solution[j];
				}
				cout << endl;
			}
		}

		if (test_count != 0)
			cout << endl;
	}
}

int main750()
{
	algorithm();
	return 0;
}