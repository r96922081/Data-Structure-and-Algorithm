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

int row_count, col_count;
vector<pair<int, int>> top_left;
vector<pair<int, int>> bottom_right;
vector<vector<int>> matrix;
int L, U;

static void get_corner()
{
	for (int i = 0; i < row_count; i++)
	{
		int left = 0;
		int right = col_count - 1;
		int answer = -1;

		while (left <= right)
		{
			int mid = (left + right) / 2;
			int mid_value = matrix[i][mid];

			if (L <= mid_value && (mid == 0 || matrix[i][mid - 1] < L))
			{
				answer = mid;
				break;
			}

			if (mid_value < L)
				left = mid + 1;
			else
				right = mid - 1;
		}

		if (answer == -1)
			continue;

		int row = i;
		int col = answer;
		
		bool candidate = true;

		for (auto it = top_left.begin(); it != top_left.end(); it++)
		{
			if (it->first <= row && it->second <= col)
			{
				candidate = false;
				break;
			}
		}

		if (candidate)
			top_left.push_back(pair<int, int>(row, col));
	}

	for (int i = row_count - 1; i >= 0; i--)
	{
		int left = 0;
		int right = col_count - 1;
		int answer = -1;

		while (left <= right)
		{
			int mid = (left + right) / 2;
			int mid_value = matrix[i][mid];

			if (mid_value <= U && (mid == col_count - 1 || U < matrix[i][mid + 1]))
			{
				answer = mid;
				break;
			}

			if (U < mid_value)
				right = mid - 1;
			else
				left = mid + 1;
		}

		if (answer == -1)
			continue;

		int row = i;
		int col = answer;

		bool candidate = true;

		for (auto it = bottom_right.begin(); it != bottom_right.end(); it++)
		{
			if (row <= it->first && col <= it->second)
			{
				candidate = false;
				break;
			}
		}

		if (candidate)
			bottom_right.push_back(pair<int, int>(row, col));
	}
}

static int get_largest_side()
{
	int largest_side = 0;

	for (auto it1 = bottom_right.begin(); it1 != bottom_right.end(); it1++)
	{
		pair<int, int> cell1 = *it1;

		int it2_pos = top_left.size();

		int left = 0;
		int right = top_left.size() - 1;

		int max_it2_row = cell1.first - largest_side;
		int max_it2 = right;

		while (left <= right)
		{
			int mid = (left + right) / 2;
			int mid_value = top_left[mid].first;

			if (mid_value <= max_it2_row && (mid == top_left.size() - 1 || top_left[mid + 1].first > max_it2_row))
			{
				max_it2 = mid;
				break;
			}

			if (mid_value > max_it2_row)
				right = mid - 1;
			else
				left = mid + 1;
		}

		for (int it2 = 0; it2 <= max_it2; it2++)
		{
			pair<int, int> cell2 = top_left[it2];
			largest_side = max(largest_side, min(cell1.first - cell2.first + 1, cell1.second - cell2.second + 1));
		}
	}

	return largest_side;
}

static void algorithm()
{
	int temp;

	while (cin >> row_count >> col_count, row_count != 0)
	{
		matrix.clear();

		for (int i = 0; i < row_count; i++)
		{
			for (int j = 0; j < col_count; j++)
			{
				if (j == 0)
					matrix.push_back(vector<int>());

				cin >> temp;
				matrix[i].push_back(temp);
			}
		}

		int query_count;
		cin >> query_count;

		while (query_count--)
		{
			cin >> L >> U;

			top_left.clear();
			bottom_right.clear();
			get_corner();

			cout << get_largest_side() << endl;
		}

		cout << "-" << endl;
	}
}

int main12192()
{
	algorithm();
	return 0;
}