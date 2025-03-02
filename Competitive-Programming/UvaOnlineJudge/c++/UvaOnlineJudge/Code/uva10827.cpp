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

const int MAX_N = 76;

int matrix[MAX_N][MAX_N];
int temp_matrix[MAX_N][MAX_N];
int max_x_width;
int max_y_width;
int max_sum;

// y_pos, y_width;
int max_suffix[MAX_N][MAX_N];

// x_pos, y_pos, y_width;
// column sum
int column_sum[MAX_N][MAX_N][MAX_N];

// y_pos, y_width, x_width
int continuous_max_sum_left_to_right[MAX_N][MAX_N][MAX_N];
int continuous_max_sum_right_to_left[MAX_N][MAX_N][MAX_N];
int continuous_sum_left_to_right[MAX_N][MAX_N][MAX_N];
int continuous_sum_right_to_left[MAX_N][MAX_N][MAX_N];

static void algorithm()
{
	int test_count;
	cin >> test_count;

	const int min_value = -100 * 75 * 75 - 1;

	while (test_count--)
	{
		cin >> max_x_width;
		max_y_width = max_x_width;

		for (int i = 0; i < max_x_width; i++)
			for (int j = 0; j < max_y_width; j++)
				cin >> matrix[i][j];

		memset(max_suffix, 0, sizeof(int) * MAX_N * MAX_N);
		memset(column_sum, 0, sizeof(int) * MAX_N * MAX_N * MAX_N);
		memset(continuous_max_sum_left_to_right, 0, sizeof(int) * MAX_N * MAX_N * MAX_N);
		memset(continuous_max_sum_right_to_left, 0, sizeof(int) * MAX_N * MAX_N * MAX_N);
		memset(continuous_sum_left_to_right, 0, sizeof(int) * MAX_N * MAX_N * MAX_N);
		memset(continuous_sum_right_to_left, 0, sizeof(int) * MAX_N * MAX_N * MAX_N);

		max_sum = matrix[0][0];

		for (int y_pos = 0; y_pos < max_y_width; y_pos++)
		{
			for (int x_width = 1; x_width <= max_x_width; x_width++)
			{
				int col_sum = 0;

				for (int y_width = 1; y_width <= max_y_width; y_width++)
				{
					col_sum += matrix[(y_pos + y_width - 1) % max_y_width][x_width - 1];

					int new_sum = col_sum + max_suffix[y_pos][y_width];
					max_sum = max(max_sum, new_sum);

					max_suffix[y_pos][y_width] = new_sum;
					if (max_suffix[y_pos][y_width] < 0)
						max_suffix[y_pos][y_width] = 0;
				}
			}
		}

		// y_pos, y_width, x_width
		for (int y_pos = 0; y_pos < max_y_width; y_pos++)
		{
			for (int x_width = 1; x_width < max_x_width; x_width++)
			{
				int col_sum1 = 0;
				int col_sum2 = 0;
				for (int y_width = 1; y_width <= max_y_width; y_width++)
				{
					col_sum1 += matrix[(y_pos + y_width - 1) % max_y_width][x_width - 1];
					col_sum2 += matrix[(y_pos + y_width - 1) % max_y_width][max_x_width - x_width];
					
					if (x_width == 1)
					{
						continuous_sum_left_to_right[y_pos][y_width][x_width] = col_sum1;
						continuous_max_sum_left_to_right[y_pos][y_width][x_width] = col_sum1;
						continuous_sum_right_to_left[y_pos][y_width][x_width] = col_sum2;
						continuous_max_sum_right_to_left[y_pos][y_width][x_width] = col_sum2;
					}
					else
					{
						continuous_sum_left_to_right[y_pos][y_width][x_width] = col_sum1 + continuous_sum_left_to_right[y_pos][y_width][x_width - 1];
						continuous_max_sum_left_to_right[y_pos][y_width][x_width] = max(continuous_max_sum_left_to_right[y_pos][y_width][x_width - 1], continuous_sum_left_to_right[y_pos][y_width][x_width]);
						continuous_sum_right_to_left[y_pos][y_width][x_width] = col_sum2 + continuous_sum_right_to_left[y_pos][y_width][x_width - 1];
						continuous_max_sum_right_to_left[y_pos][y_width][x_width] = max(continuous_max_sum_right_to_left[y_pos][y_width][x_width - 1], continuous_sum_right_to_left[y_pos][y_width][x_width]);
					}
				}
			}
		}

		for (int y_pos = 0; y_pos < max_y_width; y_pos++)
			for (int y_width = 1; y_width <= max_y_width; y_width++)
				for (int x_width = 1; x_width <= max_x_width - 2; x_width++)
					max_sum = max(max_sum, continuous_max_sum_left_to_right[y_pos][y_width][x_width] + continuous_max_sum_right_to_left[y_pos][y_width][max_x_width - x_width - 1]);	

		cout << max_sum << endl;
	}
}

int main10827()
{
	algorithm();
	return 0;
}