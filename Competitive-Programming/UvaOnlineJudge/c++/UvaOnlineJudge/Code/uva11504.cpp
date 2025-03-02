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
	stack<int>& unfinished, vector<int>& finished, vector<int>& all_scc_index, 
	int& scc_index,	set<int>& pushed_scc_index)
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

		if (visited[neighbor] == false)
		{
			int ret_min_reachable = get_scc_main(node_count, neighbor, edges, visited, dfs_index, all_dfs_index, dfs_min_reachable, unfinished, finished, all_scc_index, scc_index, pushed_scc_index);
			if (ret_min_reachable < dfs_min_reachable[node_index])
				dfs_min_reachable[node_index] = ret_min_reachable;
		}
		else
		{
			if (finished[neighbor] == false && dfs_min_reachable[neighbor] < dfs_min_reachable[node_index])
				dfs_min_reachable[node_index] = dfs_min_reachable[neighbor];
		}

		auto it = pushed_scc_index.find(all_scc_index[neighbor]);
		if (it != pushed_scc_index.end())
			pushed_scc_index.erase(it);
	}

	if (all_dfs_index[node_index] == dfs_min_reachable[node_index])
	{
		vector<int> single_scc;
		scc_index++;
		pushed_scc_index.insert(scc_index);
		int top = 0;
		do
		{
			top = unfinished.top();
			all_scc_index[top] = scc_index;
			finished[top] = true;
			unfinished.pop();

		} while (top != node_index);
	}

	return dfs_min_reachable[node_index];
}

static int get_scc_modified(int node_count, vector<vector<int>>& edges)
{
	vector<bool> visited(node_count, false);
	vector<int> all_scc_index(node_count);
	int scc_index = 0;
	int dfs_index = 0;
	vector<int> all_dfs_index(node_count, 0);
	vector<int> dfs_min_reachable(node_count, 0);
	stack<int> unfinished;
	vector<int> finished(node_count, false);
	set<int> pushed_scc_index;

	for (int node_index = 0; node_index < node_count; node_index++)
	{
		if (visited[node_index] == false)
			get_scc_main(node_count, node_index, edges, visited, dfs_index, all_dfs_index, dfs_min_reachable, unfinished, finished, all_scc_index, scc_index, pushed_scc_index);
	}

	return pushed_scc_index.size();
}

static void dfs(vector<bool>& visited, vector<vector<int>>& edges, int index)
{
	if (visited[index])
		return;

	visited[index] = true;

	for (int i = 0; i < edges[index].size(); i++)
	{
		int neighbor = edges[index][i];
		dfs(visited, edges, neighbor);
	}
}

static void algorithm()
{
	int node_count, edge_count;
	int test_count;
	cin >> test_count;

	while (test_count--)
	{
		cin >> node_count >> edge_count;
		vector<vector<int>> edges(node_count, vector<int>());
		vector<bool> visited(node_count, false);

		int node1, node2;
		while (edge_count--)
		{
			cin >> node1 >> node2;
			edges[node1 - 1].push_back(node2 - 1);
		}
				
		int answer = get_scc_modified(node_count, edges);

		cout << answer << endl;
	}
}

int main11504()
{
	algorithm();
	
	return 0;
}