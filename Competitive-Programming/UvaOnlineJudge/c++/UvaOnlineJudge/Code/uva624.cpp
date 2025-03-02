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

int sizes[20];
bool selected[20];
int min_remaining_size = 0;
vector<int> answer;

static void get_max_usage_backtracking(int remaining_size, int index, int count)
{
	if (index == count)
		return;

	int remaining_size_2 = remaining_size - sizes[index];

	if (remaining_size_2 >= 0)
	{
		selected[index] = true;

		if (remaining_size_2 < min_remaining_size)
		{
			min_remaining_size = remaining_size_2;
			answer.clear();

			for (int j = 0; j < count; j++)
				if (selected[j])
					answer.push_back(j);
		}

		get_max_usage_backtracking(remaining_size_2, index + 1, count);

		selected[index] = false;
	}

	get_max_usage_backtracking(remaining_size, index + 1, count);
}

static void algorithm()
{
	int capacity;

	while (scanf("%d", &capacity) == 1)
	{
		answer.clear();

		min_remaining_size = capacity;

		for (int i = 0; i < 20; i++)
			selected[i] = false;

		int count;
		cin >> count;

		for (int i = 0; i < count; i++)
			cin >> sizes[i];

		get_max_usage_backtracking(capacity, 0, count);

		for (int i = 0; i < answer.size(); i++)
			cout << sizes[answer[i]] << " ";

		cout << "sum:" << capacity - min_remaining_size << endl;
	}
}

int main624()
{
	algorithm();
	return 0;
}