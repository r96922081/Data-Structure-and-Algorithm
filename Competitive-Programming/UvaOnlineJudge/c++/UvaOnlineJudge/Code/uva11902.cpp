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

list<int> all_adj_list[100];
int vertex_count;

bool dominator_array[100][100];

static void dfs(vector<bool>& reachable_array, int src_node, int skip_node)
{
	reachable_array[src_node] = true;

	for (auto it = all_adj_list[src_node].begin(); it != all_adj_list[src_node].end(); it++)
	{
		auto adj_node = *it;
		if (adj_node == skip_node)
			continue;

		if (reachable_array[adj_node] == false)
			dfs(reachable_array, adj_node, skip_node);
	}
}

static vector<bool> get_reachable(int src_node, int skip_node)
{
	vector<bool> reachable_array1(vertex_count, false);
	dfs(reachable_array1, src_node, skip_node);

	return reachable_array1;
}

static void find_dominator()
{
	auto reachable_array1 = get_reachable(0, -1);

	for (int i = 0; i < vertex_count; i++)
	{
		if (reachable_array1[i])
		{
			dominator_array[0][i] = true;
			dominator_array[i][i] = true;
		}
	}
	
	for (int skip_node = 1; skip_node < vertex_count; skip_node++)
	{
		auto reachable_array2 = get_reachable(0, skip_node);

		for (int i = 1; i < vertex_count; i++)
		{
			if (i == skip_node)
				continue;

			if (reachable_array1[i] == true && reachable_array2[i] == false)
				dominator_array[skip_node][i] = true;
		}
	}
}

static void algorithm()
{
	int test_count;

	cin >> test_count;

	for (int ti = 0; ti < test_count; ti++)
	{
		cin >> vertex_count;

		for (int i = 0; i < 100; i++)
			all_adj_list[i].clear();

		for (int i = 0; i < vertex_count; i++)
		{
			for (int j = 0; j < vertex_count; j++)
			{
				int temp;
				cin >> temp;
				if (temp == 1)
					all_adj_list[i].push_back(j);
			}
		}

		memset(dominator_array, 0, sizeof(dominator_array));

		find_dominator();

		printf("Case %d:\n", ti + 1);
		for (int i = 0; i < vertex_count; i++)
		{
			printf("+");
			for (int j = 0; j < vertex_count * 2 - 1; j++)
				printf("-");
			printf("+\n");
			for (int j = 0; j < vertex_count; j++)
			{
				printf("|");
				if (dominator_array[i][j])
					printf("Y");
				else
					printf("N");
			}
			printf("|\n");
		}

		printf("+");
		for (int j = 0; j < vertex_count * 2 - 1; j++)
			printf("-");
		printf("+\n");
	}
}

int main11902()
{
	algorithm();

	return 0;
}