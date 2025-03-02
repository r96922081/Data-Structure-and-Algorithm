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

int get_dfs_info2(int node_count, vector<vector<int>>& edges, int node_index, int prev_node_index, vector<bool>& visited, 
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
			int min_reachable = get_dfs_info2(node_count, edges, neighbor, node_index, visited, dfs_num, dfs_index, dfs_min_reachable);
			if (min_reachable < dfs_min_reachable[node_index])
				dfs_min_reachable[node_index] = min_reachable;
		}
	}

	return dfs_min_reachable[node_index];
}

static void get_dfs_info(int node_count, vector<vector<int>>& edges, vector<int>& dfs_index, vector<int>& dfs_min_reachable)
{
	vector<bool> visited(node_count, false);

	for (int i = 0; i < node_count; i++)
	{
		int dfs_num = 0;
		if (visited[i] == false)
		{
			get_dfs_info2(node_count, edges, i, -1, visited, dfs_num, dfs_index, dfs_min_reachable);
		}
	}
}

static void get_connected_component_count2(int node_count, vector<vector<int>>& edges, vector<bool>& visited, int index, int skip_node)
{
	visited[index] = true;
	for (int i = 0; i < edges[index].size(); i++)
	{
		int neighbor = edges[index][i];
		if (neighbor == skip_node)
			continue;

		if (visited[neighbor] == false)
		{
			get_connected_component_count2(node_count, edges, visited, neighbor, skip_node);
		}
	}

}

static int get_connected_component_count(int node_count, vector<vector<int>>& edges, int skip_node)
{
	vector<bool> visited(node_count, false);
	int count = 0;

	for (int i = 0; i < node_count; i++)
	{
		if (i == skip_node)
			continue;

		if (visited[i] == false)
		{
			count++;
			get_connected_component_count2(node_count, edges, visited, i, skip_node);
		}
	}

	return count;
}

static bool sort_function(pair<int, int> p1, pair<int, int> p2)
{
	if (p1.second > p2.second)
		return true;
	else if (p1.second == p2.second && p1.first < p2.first)
		return true;

	return false;
}

static void algorithm()
{
	int node_count, max_cut_count;

	while (cin >> node_count >> max_cut_count, node_count != 0)
	{
		vector<vector<int>> edges(node_count, vector<int>());

		int node1, node2;
		while (cin >> node1 >> node2, node1 != -1)
		{
			edges[node1].push_back(node2);
			edges[node2].push_back(node1);
		}

		vector<int> dfs_index(node_count);
		vector<int> dfs_min_reachable(node_count);

		get_dfs_info(node_count, edges, dfs_index, dfs_min_reachable);

		vector<int> cut;

		for (int i = 0; i < node_count; i++)
		{
			bool end_edge_loop = false;
			for (int j = 0; j < edges[i].size() && !end_edge_loop; j++)
			{
				int neighbor = edges[i][j];
				if (dfs_index[i] <= dfs_min_reachable[neighbor])
				{
					if (dfs_index[i] == 0)
					{
						if (edges[i].size() == 1)
						{
							break;
						}
					}
					cut.push_back(i);
					end_edge_loop = true;
				}
			}
		}

		vector<pair<int, int>> connected_component_counts(node_count);
		for (int i = 0; i < node_count; i++)
		{
			pair<int, int> p(i, 1);
			connected_component_counts[i] = p;
		}

		for (int i = 0; i < cut.size(); i++)
			connected_component_counts[cut[i]].second = get_connected_component_count(node_count, edges, cut[i]);

		sort(connected_component_counts.begin(), connected_component_counts.end(), sort_function);

		for (int i = 0; i < max_cut_count; i++)
			printf("%d %d\n", connected_component_counts[i].first, connected_component_counts[i].second);

		cout << endl;
	}
}

int main10765()
{
	algorithm();
	
	return 0;
}