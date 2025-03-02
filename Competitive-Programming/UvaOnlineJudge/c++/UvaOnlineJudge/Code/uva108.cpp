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

int matrix[100][100];
int max_suffix_sum[100][100];
int min_value = -127 * 100 * 100 - 1;
int max_value = min_value;

static void algorithm()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int temp;
			cin >> temp;
			matrix[i][j] = temp;
			max_suffix_sum[i][j] = 0;
			max_value = max(max_value, temp);
		}
	}

	for (int col_pos = 0; col_pos < n; col_pos++)
	{
		for (int row_pos = 0; row_pos < n; row_pos++)
		{
			int value = 0;

			for (int row_count = 1; row_pos + row_count - 1 < n; row_count++)
			{
				value += matrix[row_pos + row_count - 1][col_pos];

				max_suffix_sum[row_pos][row_count] += value;

				if (max_suffix_sum[row_pos][row_count] < 0)
					max_suffix_sum[row_pos][row_count] = 0;
				else
					max_value = max(max_value, max_suffix_sum[row_pos][row_count]);
			}
		}
	}

	cout << max_value << endl;
}

int main108()
{
	algorithm();
	return 0;
}