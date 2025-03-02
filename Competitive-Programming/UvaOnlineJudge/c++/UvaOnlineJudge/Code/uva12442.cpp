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

vector<int> length;
vector<int> adj;
set<int> undone_node;
vector<int> depth;
int current_depth;
int start_depth = 0;
int circle_depth = 0;

static int find_length(int node)
{
	current_depth++;
	int next_node = adj[node];
	depth[node] = current_depth;
	
	auto it = undone_node.find(node);
	undone_node.erase(it);

	if (length[next_node] != -1)
	{
		length[node] = length[next_node] + 1;
	}
	else
	{
		if (depth[next_node] != 0 && start_depth <= depth[next_node] && depth[node] > depth[next_node])
		{
			length[node] = depth[node] - depth[next_node] + 1;
			circle_depth = depth[next_node];
		}
		else
		{
			int next_len = find_length(next_node);

			if (circle_depth != 0 && circle_depth <= depth[node])
				length[node] = next_len;
			else
				length[node] = next_len + 1;
		}
	}

	return length[node];
}

static void algorithm()
{
	int test_count;

	cin >> test_count;

	for (int ti = 1; ti <= test_count; ti++)
	{
		int node_count;
		cin >> node_count;

		adj = vector<int>(node_count + 1, -1);
		length = vector<int>(node_count + 1, - 1);
		depth = vector<int>(node_count + 1, 0);

		for (int i = 0; i < node_count; i++)
		{
			int u, v;
			cin >> u >> v;

			adj[u] = v;
			undone_node.insert(i + 1);
		}

		int answer = 0;

		while (!undone_node.empty())
		{
			auto it = undone_node.begin();
			int current_node = *it;
			current_depth = 0;
			circle_depth = 0;

			find_length(current_node);
		}

		int max_len = 0;
		for (int i = 1; i <= node_count; i++)
		{
			if (length[i] > max_len)
			{
				max_len = length[i];
				answer = i;
			}
		}

		printf("Case %d: %d\n", ti, answer);
	}
}

int main12442()
{
	algorithm();

	return 0;
}