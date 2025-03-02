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

static void algorithm()
{
	int test_count;
	cin >> test_count;

	for (int ti = 1; ti <= test_count; ti++)
	{
		int stop_count;
		cin >> stop_count;

		vector<int> routes;
		for (int i = 0; i < stop_count - 1; i++)
		{
			int temp;
			cin >> temp;
			routes.push_back(temp);
		}

		int max_sum = 0;
		int max_sum_start = -1;
		int max_sum_end = -1;

		int max_suffix_sum = 0;
		int max_suffix_sum_start = -1;
		int max_suffix_sum_end = -1;

		for (int i = 0; i < routes.size(); i++)
		{
			int start = i + 1;
			int end = start + 1;

			int route = routes[i];

			max_suffix_sum += route;
			if (max_suffix_sum < 0)
			{
				max_suffix_sum = 0;
				max_suffix_sum_start = -1;
				max_suffix_sum_end = -1;
			}
			else
			{
				max_suffix_sum_end = end;
				if (max_suffix_sum_start == -1)
					max_suffix_sum_start = start;
			}

			if (max_suffix_sum > max_sum)
			{
				max_sum = max_suffix_sum;
				max_sum_start = max_suffix_sum_start;
				max_sum_end = max_suffix_sum_end;
			}
			else if (max_suffix_sum == max_sum)
			{
				if (max_suffix_sum_end - max_suffix_sum_start > max_sum_end - max_sum_start)
				{
					max_sum_end = max_suffix_sum_end;
					max_sum_start = max_suffix_sum_start;
				}
			}
		}

		if (max_sum_start == -1)
			printf("Route %d has no nice parts\n", ti);
		else
			printf("The nicest part of route %d is between stops %d and %d\n", ti, max_sum_start, max_sum_end);
	}
}

int main507()
{
	algorithm();
	return 0;
}