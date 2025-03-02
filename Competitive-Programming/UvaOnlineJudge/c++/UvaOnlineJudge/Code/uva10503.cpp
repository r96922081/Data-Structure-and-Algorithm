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

int dominoes_side1[14];
int dominoes_side2[14];
bool used[14];
int last_side = -1;

static bool backtracking(int remaining_count, int total_count, int next_side)
{
	if (remaining_count == 0)
	{
		if (next_side == last_side)
			return true;
		else
			return false;
	}

	for (int i = 0; i < total_count; i++)
	{
		if (used[i] == true)
			continue;

		if (dominoes_side1[i] == next_side)
		{
			used[i] = true;

			if (backtracking(remaining_count - 1, total_count, dominoes_side2[i]))
				return true;

			used[i] = false;
		}
		else if (dominoes_side2[i] == next_side)
		{
			used[i] = true;

			if (backtracking(remaining_count - 1, total_count, dominoes_side1[i]))
				return true;

			used[i] = false;
		}
	}

	return false;
}

static void algorithm()
{
	while (true)
	{
		int remaining_count;
		int total_count;

		cin >> remaining_count;
		if (remaining_count == 0)
			return;

		cin >> total_count;

		int temp;
		cin >> temp;

		int first_side;
		cin >> first_side;
		cin >> last_side;
		cin >> temp;

		for (int i = 0; i < total_count; i++)
		{
			cin >> dominoes_side1[i];
			cin >> dominoes_side2[i];
			used[i] = false;
		}

		if (backtracking(remaining_count, total_count, first_side))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}

int main10503()
{
	algorithm();
	return 0;
}