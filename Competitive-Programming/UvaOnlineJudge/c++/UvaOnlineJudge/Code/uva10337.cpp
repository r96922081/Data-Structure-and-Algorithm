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
#include <iterator>

using namespace std;

int cost[10][1000];
int wind[10][1000];

static int min2(int a, int b)
{
	if (a == 0)
		return b;
	if (b == 0)
		return a;

	return min(a, b);
}

static void algorithm()
{
	int test_count;
	cin >> test_count;

	while (test_count--)
	{
		memset(cost, 0, sizeof(cost));
		memset(wind, 0, sizeof(wind));

		int distance;
		cin >> distance;

		distance /= 100;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < distance; j++)
			{
				cin >> wind[i][j];
			}
		}

		cost[9][0] = 30 - wind[9][0];
		cost[8][0] = 60 - wind[9][0];

		for (int i = 1; i < distance; i++)
		{
			for (int height = 0; height < 10; height++)
			{
				if (height != 0 && cost[height - 1][i - 1] != 0)
					cost[height][i] = min2(cost[height][i], cost[height - 1][i - 1] + 20 - wind[height - 1][i]);

				if (cost[height][i - 1] != 0)
					cost[height][i] = min2(cost[height][i], cost[height][i - 1] + 30 - wind[height][i]);

				if (height != 9 && cost[height + 1][i - 1] != 0)
					cost[height][i] = min2(cost[height][i], cost[height + 1][i - 1] + 60 - wind[height + 1][i]);
			}
		}

		cout << cost[9][distance - 1] << endl << endl;
	}
}

int main10337()
{
	algorithm();

	return 0;
}