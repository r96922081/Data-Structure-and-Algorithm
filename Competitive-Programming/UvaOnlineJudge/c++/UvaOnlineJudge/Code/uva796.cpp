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

static bool sort_function(pair<int, int> a, pair<int, int> b) 
{ 
	if (a.first < b.first)
		return true;
	else if (a.first == b.first && a.second < b.second)
		return true;
	else
		return false;
}

int get_bridges2(int node_count, vector<vector<int>>& edges, int node_index, int prev_node_index, vector<bool>& visited, 
	int& dfs_num, vector<int>& dfs_index, vector<int>& dfs_min_reachable)
{
	visited[node_index] = true;
	dfs_index[node_index] = dfs_num;
	dfs_min_reachable[node_index] = dfs_num;
	dfs_num++;

	for (int i = 0; i < edges[node_index].size(); i++)
	{
		int neighbor = edges[node_index][i];
		if (neighbor == prev_node_index)
			continue;

		if (visited[neighbor])
		{
			if (dfs_index[neighbor] < dfs_min_reachable[node_index])
				dfs_min_reachable[node_index] = dfs_index[neighbor];
		}
		else
		{
			int min_reachable = get_bridges2(node_count, edges, neighbor, node_index, visited, dfs_num, dfs_index, dfs_min_reachable);
			if (min_reachable < dfs_min_reachable[node_index])
				dfs_min_reachable[node_index] = min_reachable;
		}
	}

	return dfs_min_reachable[node_index];
}

static void get_bridges(int node_count, vector<vector<int>>& edges, vector<pair<int, int>>& bridges)
{
	vector<bool> visited(node_count, false);
	vector<int> dfs_index(node_count);
	vector<int> dfs_min_reachable(node_count);

	for (int i = 0; i < node_count; i++)
	{
		int dfs_num = 0;
		if (visited[i] == false)
		{
			get_bridges2(node_count, edges, i, -1, visited, dfs_num, dfs_index, dfs_min_reachable);
		}
	}

	// include root
	set<int> cut;

	for (int i = 0; i < node_count; i++)
	{
		for (int j = 0; j < edges[i].size(); j++)
		{
			int neighbor = edges[i][j];
			if (dfs_index[i] <= dfs_min_reachable[neighbor])
			{
				cut.insert(i);
			}
		}
	}

	for (auto it = cut.begin(); it != cut.end(); it++)
	{
		int i = *it;
		for (int j = 0; j < edges[i].size(); j++)
		{
			int neighbor = edges[i][j];
			if (dfs_index[i] < dfs_min_reachable[neighbor])
			{
				bridges.push_back(pair<int, int>(i, neighbor));
			}
		}
	}
}

static void algorithm()
{
	int node_count;
	
	while (scanf("%d", &node_count) == 1)
	{
		vector<pair<int, int>> bridges;
		vector<vector<int>> edges(node_count, vector<int>());

		for (int i = 0; i < node_count; i++)
		{
			int node_index;
			cin >> node_index;

			int edge_count;
			scanf(" (%d)", &edge_count);

			for (int j = 0; j < edge_count; j++)
			{
				int node2;
				cin >> node2;
				edges[node_index].push_back(node2);
			}
		}

		get_bridges(node_count, edges, bridges);

		for (int j = 0; j < bridges.size(); j++)
		{
			if (bridges[j].first > bridges[j].second)
			{
				int temp = bridges[j].first;
				bridges[j].first = bridges[j].second;
				bridges[j].second = temp;
			}
		}

		sort(bridges.begin(), bridges.end(), sort_function);

		printf("%d critical links\n", bridges.size());
		for (int i = 0; i < bridges.size(); i++)
			printf("%d - %d\n", bridges[i].first, bridges[i].second);

		cout << endl;
	}
}

int main796()
{
	algorithm();
	
	return 0;
}