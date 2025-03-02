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

int get_scc_main(int node_count, int node_index, vector<vector<int>>& edges, vector<bool>& visited,
	int& dfs_index, vector<int>& all_dfs_index, vector<int>& dfs_min_reachable,
	stack<int>& unfinished, vector<int>& finished, vector<vector<int>>& scc)
{
	if (visited[node_index])
		return -1;

	visited[node_index] = true;

	unfinished.push(node_index);
	all_dfs_index[node_index] = dfs_index;
	dfs_min_reachable[node_index] = dfs_index;
	dfs_index++;

	for (int i = 0; i < edges[node_index].size(); i++)
	{
		int neighbor = edges[node_index][i];
		if (finished[neighbor])
			continue;

		if (visited[neighbor] == false)
		{
			int ret_min_reachable = get_scc_main(node_count, neighbor, edges, visited, dfs_index, all_dfs_index, dfs_min_reachable, unfinished, finished, scc);
			if (ret_min_reachable < dfs_min_reachable[node_index])
				dfs_min_reachable[node_index] = ret_min_reachable;
		}
		else
		{
			if (dfs_min_reachable[neighbor] < dfs_min_reachable[node_index])
				dfs_min_reachable[node_index] = dfs_min_reachable[neighbor];
		}
	}

	if (all_dfs_index[node_index] == dfs_min_reachable[node_index])
	{
		vector<int> single_scc;

		int top = 0;
		do
		{
			top = unfinished.top();
			single_scc.push_back(top);
			finished[top] = true;
			unfinished.pop();
		} while (top != node_index);

		scc.push_back(single_scc);
	}

	return dfs_min_reachable[node_index];
}

static vector<vector<int>> get_scc(int node_count, vector<vector<int>>& edges)
{
	vector<bool> visited(node_count, false);
	int dfs_index = 0;
	vector<int> all_dfs_index(node_count, 0);
	vector<int> dfs_min_reachable(node_count, 0);
	stack<int> unfinished;
	vector<int> finished(node_count, false);

	vector<vector<int>> scc;

	for (int node_index = 0; node_index < node_count; node_index++)
	{
		if (visited[node_index] == false)
			get_scc_main(node_count, node_index, edges, visited, dfs_index, all_dfs_index, dfs_min_reachable, unfinished, finished, scc);
	}

	return scc;
}

static void algorithm()
{
	int node_count, edge_count;

	while (cin >> node_count >> edge_count, node_count != 0)
	{
		vector<vector<int>> edges(node_count, vector<int>());

		int node1, node2, dir;
		while (edge_count--)
		{
			cin >> node1 >> node2 >> dir;
			edges[node1 - 1].push_back(node2 - 1);

			if (dir == 2)
				edges[node2 - 1].push_back(node1 - 1);
		}

		vector<vector<int>> scc = get_scc(node_count, edges);

		if (scc.size() == 1)
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
}

int main11838()
{
	algorithm();
	
	return 0;
}