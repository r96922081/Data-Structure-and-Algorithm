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

	for (int test_index = 1; test_index <= test_count; test_index++)
	{
		int max_diff = 0;
		int stone_count = 0;
		cin >> stone_count;

		int distance = 0;
		cin >> distance;

		scanf("\n");

		vector<vector<int>> stone_distances;

		vector<char> type;
		vector<int> stone_distance;

		type.push_back('B');
		stone_distance.push_back(0);

		for (int i = 0; i < stone_count; i++)
		{
			if (i != 0)
				scanf(" ");

			char type2;
			int distance2;

			scanf("%c-%d", &type2, &distance2);

			type.push_back(type2);
			stone_distance.push_back(distance2);
		}

		type.push_back('B');
		stone_distance.push_back(distance);

		for (int i = 0; i < stone_distance.size() - 1; i++)
		{
			int current_pos = stone_distance[i];
			if (type[i + 1] == 'S')
				max_diff = max(max_diff, stone_distance[i + 2] - current_pos);
			else
				max_diff = max(max_diff, stone_distance[i + 1] - current_pos);
		}

		printf("Case %d: %d\n", test_index, max_diff);
	}
}

int main11157()
{
	algorithm();
	return 0;
}