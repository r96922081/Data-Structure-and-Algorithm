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

const int MAX_N = 101;

int matrix[MAX_N][MAX_N];

// y_pos, x_pos, y_length
long long sum_of_x_len_1[MAX_N][MAX_N][MAX_N];
int max_plot_size;
long long plot_cost_of_max_size;
int max_y, max_x;
long long max_valid_cost;

static void algorithm()
{
	int test_count;
	cin >> test_count;

	for (int test_index = 1; test_index <= test_count; test_index++)
	{
		memset(sum_of_x_len_1, 0, sizeof(long long) * MAX_N * MAX_N * MAX_N);
		max_plot_size = 0;
		plot_cost_of_max_size = 0;

		cin >> max_y >> max_x >> max_valid_cost;

		for (int i = 0; i < max_y; i++)
			for (int j = 0; j < max_x; j++)
				cin >> matrix[i][j];

		for (int y_pos = 0; y_pos < max_y; y_pos++)
		{
			for (int y_len = 1; y_pos + y_len <= max_y; y_len++)
			{
				long long prev_plot_cost = 0;
				int left_index = 0;

				for (int x_len = 1; x_len <= max_x; x_len++)
				{
					long long strip_cost = matrix[y_pos + y_len - 1][x_len - 1];

					if (y_len == 1)
					{
						sum_of_x_len_1[y_pos][x_len - 1][1] = strip_cost;
					}
					else
					{
						sum_of_x_len_1[y_pos][x_len - 1][y_len] = sum_of_x_len_1[y_pos][x_len - 1][y_len - 1] + strip_cost;
					}

					long long new_plot_cost = sum_of_x_len_1[y_pos][x_len - 1][y_len];
					long long new_cost = prev_plot_cost + new_plot_cost;

					for (; left_index < x_len && new_cost > max_valid_cost; left_index++)
						new_cost -= sum_of_x_len_1[y_pos][left_index][y_len];

					prev_plot_cost = new_cost;

					int plot_size = y_len * (x_len - left_index);

					if (plot_size > max_plot_size)
					{
						max_plot_size = plot_size;
						plot_cost_of_max_size = new_cost;
					}
					else if (plot_size == max_plot_size && new_cost < plot_cost_of_max_size)
					{
						plot_cost_of_max_size = new_cost;
					}
				}
			}
		}

		printf("Case #%d: %d %lld\n", test_index, max_plot_size, plot_cost_of_max_size);
	}
}

int main11951()
{
	algorithm();
	return 0;
}