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

int surplus[12];

bool max_surplus_is_deficit = true;
int max_surplus = 0;
int s;
int d;


static void calculate_surplus_by_backtracking(int index, int surplus_so_far)
{
	if (index >= 5)
	{
		int surplus_for_5_month = 0;
		for (int i = 0; i < 5; i++)
			surplus_for_5_month += surplus[index - 1 - i];

		if (surplus_for_5_month > 0)
			return;
	}

	if (index == 12)
	{
		if (max_surplus < surplus_so_far)
			max_surplus = surplus_so_far;

		if (surplus_so_far >= 0)
			max_surplus_is_deficit = false;

		return;
	}

	surplus_so_far += s;
	surplus[index] = s;
	calculate_surplus_by_backtracking(index + 1, surplus_so_far);

	surplus_so_far -= s;
	surplus_so_far += d;
	surplus[index] = d;
	calculate_surplus_by_backtracking(index + 1, surplus_so_far);
}

static void algorithm()
{
	while (scanf("%d %d", &s, &d) == 2)
	{
		max_surplus = 0;
		d = -d;
		max_surplus_is_deficit = true;

		calculate_surplus_by_backtracking(0, 0);

		if (max_surplus_is_deficit)
			cout << "Deficit" << endl;
		else
		{
			cout << max_surplus << endl;
		}
	}
}

int main10576()
{
	algorithm();
	return 0;
}