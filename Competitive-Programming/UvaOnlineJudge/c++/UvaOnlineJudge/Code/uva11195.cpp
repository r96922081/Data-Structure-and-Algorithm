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

bool broken[15][15];

static int find_queens(int row, int size, vector<bool>& used_col, vector<bool>& used_slash_diagonal, vector<bool>& used_back_slash_diagonal)
{
	if (row == size)
		return 1;

	int answer = 0;

	for (int col = 0; col < size; col++)
	{
		if (broken[row][col])
			continue;

		if (used_col[col] == true)
			continue;

		if (used_slash_diagonal[row + col] == true)
			continue;

		if (used_back_slash_diagonal[col - row + size - 1] == true)
			continue;

		used_col[col] = true;
		used_slash_diagonal[row + col] = true;
		used_back_slash_diagonal[col - row + size - 1] = true;

		answer += find_queens(row + 1, size, used_col, used_slash_diagonal, used_back_slash_diagonal);

		used_col[col] = false;
		used_slash_diagonal[row + col] = false;
		used_back_slash_diagonal[col - row + size - 1] = false;
	}

	return answer;
}

static void algorithm()
{
	int size;
	int test_index = 1;

	while (cin >> size, size > 0)
	{
		vector<bool> used_col;
		vector<bool> used_slash_diagonal;
		vector<bool> used_back_slash_diagonal;

		for (int i = 0; i < size; i++)
			used_col.push_back(false);

		for (int i = 0; i < 2 * size - 1; i++)
		{
			used_slash_diagonal.push_back(false);
			used_back_slash_diagonal.push_back(false);
		}

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				broken[i][j] = false;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				char temp;
				cin >> temp;

				if (temp == '*')
				{
					broken[i][j] = true;
				}
			}

			scanf("\n");
		}

		int answer = find_queens(0, size, used_col, used_slash_diagonal, used_back_slash_diagonal);
		printf("Case %d: %d\n", test_index++, answer);
	}
}

int main11195()
{
	algorithm();
	return 0;
}