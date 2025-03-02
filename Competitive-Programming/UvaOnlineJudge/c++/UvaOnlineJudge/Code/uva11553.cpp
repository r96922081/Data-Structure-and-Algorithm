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

static int max_count = -1;
static int answer[20];

static void algorithm2(int built_index, int built_count, int* selection, vector<int>& tower, vector<vector<int>>& tower_to_overlapping, vector<int>& overlapped_area)
{
	if (built_index == built_count)
	{
		vector<int> overlapped_area_copy = overlapped_area;
		int served_count = 0;

		for (int i = 0; i < built_count; i++)
		{
			int selection_index = selection[i];
			served_count += tower[selection_index];

			for (int j = 0; j < tower_to_overlapping[selection_index].size(); j++)
			{
				served_count += overlapped_area_copy[tower_to_overlapping[selection_index][j]];
				overlapped_area_copy[tower_to_overlapping[selection_index][j]] = 0;
			}
		}

		if (served_count > max_count)
		{
			max_count = served_count;

			for (int j = 0; j < built_count; j++)
				answer[j] = selection[j];
		}
		return;
	}

	int last_tower = tower.size() - 1;
	int i = 1;
	if (built_index > 0)
		i = selection[built_index - 1] + 1;
	for (; i <= last_tower - (built_count - built_index) + 1; i++)
	{
		selection[built_index] = i;
		algorithm2(built_index + 1, built_count, selection, tower, tower_to_overlapping, overlapped_area);
	}
}

static void algorithm()
{
	int test_case_count = 0;
	cin >> test_case_count;

	int grid[8][8];

	while (test_case_count--)
	{
		int size;
		cin >> size;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cin >> grid[i][j];
			}
		}

		int* permutation_array = new int[size];

		for (int i = 0; i < size; i++)
			permutation_array[i] = i;

		int min_winned_candy = 8001;

		do
		{
			int min_winned_candy_in_this_permutation = 0;

			for (int i = 0; i < size; i++)
				min_winned_candy_in_this_permutation += grid[i][permutation_array[i]];

			min_winned_candy = min(min_winned_candy, min_winned_candy_in_this_permutation);
		} while (std::next_permutation(permutation_array, permutation_array + size));

		cout << min_winned_candy << endl;

		delete[] permutation_array;
	}
}

int main11553()
{
	algorithm();
	return 0;
}