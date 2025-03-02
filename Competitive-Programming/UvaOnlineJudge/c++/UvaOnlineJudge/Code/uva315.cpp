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

static set<int> cut_points;
static vector<vector<int>> adj_list;
static vector<bool> visited;
static int root = 0;
static int root_children = 0;
static vector<int> dfs_num;
static vector<int> dfs_low;

static void find_cut_point(int u, int& iteration)
{
	dfs_num[u] = iteration;
	dfs_low[u] = iteration;
	iteration++;

	visited[u] = true;

	for (auto it = adj_list[u].begin(); it != adj_list[u].end(); it++)
	{
		int v = *it;

		if (!visited[v])
		{
			if (u == root)
				root_children++;

			find_cut_point(v, iteration);

			if (dfs_low[v] >= dfs_num[u])
			{
				if (u == root)
				{
					if (root_children > 1)
						cut_points.insert(u);
				}
				else
					cut_points.insert(u);
			}

			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else
		{
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
		}
	}
}

static void algorithm()
{
	int v_count;
	string line;

	cin >> v_count;
	getline(cin, line);
	
	while (v_count)
	{
		int src;

		getline(cin, line);
		stringstream ss(line);
		ss >> src;

		cut_points.clear();
		adj_list.assign(v_count, vector<int>());
		visited.assign(v_count, false);
		dfs_num.assign(v_count, -1);
		dfs_low.assign(v_count, -1);
		root_children = 0;

		while (src != 0)
		{
			int dest;
			while (ss >> dest)
			{
				adj_list[src - 1].push_back(dest - 1);
				adj_list[dest - 1].push_back(src - 1);
			}

			getline(cin, line);
			ss = stringstream(line);
			ss >> src;
		}

		int interation = 0;
		find_cut_point(0, interation);
		cout << cut_points.size() << endl;

		cin >> v_count;
		getline(cin, line);
	}
}

int main315()
{
	algorithm();

	return 0;
}