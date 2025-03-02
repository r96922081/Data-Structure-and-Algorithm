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

using namespace std;

// y_pos, x_pos, y_width, x_width
static long long max_suffix[20][20][20][20];

// z_pos, y_pos, x_pos, y_width, x_width
static long long sum[20][20][20][20][20];

static long long matrix[20][20][20];
static long long max_rectangle;

static void algorithm()
{
	int test_count;

	cin >> test_count;
	int x_count, y_count, z_count;
	bool first = true;

	while (test_count--)
	{
		memset(max_suffix, 0, sizeof(long long) * 20 * 20 * 20 * 20);
		memset(sum, 0, sizeof(long long) * 20 * 20 * 20 * 20 * 20);

		cin >> x_count >> y_count >> z_count;

		for (int i = 0; i < z_count; i++)
			for (int j = 0; j < y_count; j++)
				for (int k = 0; k < x_count; k++)
					cin >> matrix[i][j][k];

		max_rectangle = matrix[0][0][0];

		for (int y_width = 1; y_width <= y_count; y_width++)
		{
			for (int x_width = 1; x_width <= x_count; x_width++)
			{
				for (int z_pos = 0; z_pos < z_count; z_pos++)
				{
					for (int y_pos = 0; y_pos + y_width <= y_count; y_pos++)
					{
						for (int x_pos = 0; x_pos + x_width <= x_count; x_pos++)
						{
							if (y_width == 1 && x_width == 1)
								sum[z_pos][y_pos][x_pos][y_width][x_width] = matrix[z_pos][y_pos][x_pos];
							else if (x_width == 1)
							{
								sum[z_pos][y_pos][x_pos][y_width][x_width] = sum[z_pos][y_pos][x_pos][y_width - 1][x_width] + matrix[z_pos][y_pos + y_width - 1][x_pos];
							}
							else
							{
								sum[z_pos][y_pos][x_pos][y_width][x_width] = sum[z_pos][y_pos][x_pos][y_width][x_width - 1] + sum[z_pos][y_pos][x_pos + x_width - 1][y_width][1];
							}
						}
					}
				}
			}
		}


		for (int z_pos = 0; z_pos < z_count; z_pos++)
		{
			for (int y_pos = 0; y_pos < y_count; y_pos++)
			{
				for (int x_pos = 0; x_pos < x_count; x_pos++)
				{
					for (int y_width = 1; y_pos + y_width <= y_count; y_width++)
					{
						for (int x_width = 1; x_pos + x_width <= x_count; x_width++)
						{
							max_suffix[y_pos][x_pos][y_width][x_width] += sum[z_pos][y_pos][x_pos][y_width][x_width];
							max_rectangle = max(max_rectangle, max_suffix[y_pos][x_pos][y_width][x_width]);

							if (max_suffix[y_pos][x_pos][y_width][x_width] < 0)
								max_suffix[y_pos][x_pos][y_width][x_width] = 0;
						}
					}
				}
			}
		}

		if (!first)
			cout << endl;

		cout << max_rectangle << endl;

		first = false;
	}
}

int main10755()
{
	algorithm();
	return 0;
}