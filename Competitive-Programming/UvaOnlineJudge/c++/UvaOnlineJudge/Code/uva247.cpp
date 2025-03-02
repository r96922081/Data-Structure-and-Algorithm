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

vector<vector<int>> adj_list;
vector<bool> visited;
vector<int> dfs_num;
vector<int> dfs_low;
stack<int> order;
set<int> order_set;
map<string, int> mapping_string_int;
map<int, string> mapping_int_string;
int vertex_index;

static void find_scc(int u, int& iteration)
{
	dfs_num[u] = iteration;
	dfs_low[u] = iteration;
	iteration++;
	order.push(u);
	order_set.insert(u);

	visited[u] = true;

	for (auto it = adj_list[u].begin(); it != adj_list[u].end(); it++)
	{
		int v = *it;

		if (!visited[v])
			find_scc(v, iteration);
		if (order_set.find(v) != order_set.end())
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
	}

	if (dfs_num[u] == dfs_low[u])
	{
		int stack_element;
		bool first = true;

		do{
			if (!first)
				cout << ", ";
			first = false;

			stack_element = order.top();
			order.pop();
			order_set.erase(stack_element);
			cout << mapping_int_string[stack_element];
		} while (stack_element != u);

		cout << endl;		
	}
}

static void algorithm()
{
	int n, m;

	cin >> n >> m;
	bool first = true;
	int question_index = 1;
	
	while (n != 0)
	{
		if (!first)
			cout << endl;
		first = false;
		printf("Calling circles for data set %d:\n", question_index++);

		adj_list.assign(n, vector<int>());
		visited.assign(n, false);
		dfs_num.assign(n, -1);
		dfs_low.assign(n, -1);
		mapping_string_int.clear();
		mapping_int_string.clear();
		order = stack<int>();
		order_set = set<int>();
		vertex_index = 0;

		for (int i = 0; i < m; i++)
		{
			string src_str, dest_str;			
			cin >> src_str >> dest_str;

			int src = -1, dest = -1;

			auto it = mapping_string_int.find(src_str);
			if (it != mapping_string_int.end())
				src = it->second;
			else
			{
				src = vertex_index++;
				mapping_string_int.insert(pair<string, int>(src_str, src));
				mapping_int_string.insert(pair<int, string>(src, src_str));
			}

			it = mapping_string_int.find(dest_str);
			if (it != mapping_string_int.end())
				dest = it->second;
			else
			{
				dest = vertex_index++;
				mapping_string_int.insert(pair<string, int>(dest_str, dest));
				mapping_int_string.insert(pair<int, string>(dest, dest_str));
			}

			adj_list[src].push_back(dest);
		}

		int interation = 0;

		for (int i = 0; i < visited.size(); i++)
		{
			if (visited[i] == false)
				find_scc(i, interation);
		}

		cin >> n >> m;
	}
}

int main247()
{
	algorithm();

	return 0;
}