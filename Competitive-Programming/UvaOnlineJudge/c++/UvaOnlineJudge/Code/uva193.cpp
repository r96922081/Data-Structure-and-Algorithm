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

set<int> answer;
bool black_nodes[101];
bool nodes_can_be_black[101];
int can_be_black_count = 100;
int black_count = 0;
vector<int> adjacency_list[101];
int node_count = 0;

static void backtracking(int node_index)
{
	if (black_count + can_be_black_count <= answer.size())
		return;

	if (node_index == node_count + 1)
	{
		if (black_count > answer.size())
		{
			answer.clear();
			for (int i = 1; i <= node_count; i++)
				if (black_nodes[i])
					answer.insert(i);
		}

		return;
	}

	if (nodes_can_be_black[node_index])
	{
		black_nodes[node_index] = true;
		black_count++;
		can_be_black_count--;

		vector<int> temp;

		for (auto it = adjacency_list[node_index].begin(); it != adjacency_list[node_index].end(); it++)
		{
			if (nodes_can_be_black[*it])
			{
				nodes_can_be_black[*it] = false;
				temp.push_back(*it);
			}
		}
		can_be_black_count -= temp.size();

		backtracking(node_index + 1);

		for (int i = 0; i < temp.size(); i++)
		{
			nodes_can_be_black[temp[i]] = true;
		}
		can_be_black_count += temp.size();
		can_be_black_count++;
		black_count--;
		black_nodes[node_index] = false;
	}

	backtracking(node_index + 1);
}

static void algorithm()
{
	int test_count;

	cin >> test_count;

	while (test_count--)
	{
		int edge_count;

		cin >> node_count >> edge_count;

		for (int i = 1; i <= node_count; i++)
		{
			black_nodes[i] = false;
			nodes_can_be_black[i] = true;
			adjacency_list[i].clear();
		}

		can_be_black_count = node_count;
		black_count = 0;

		for (int i = 0; i < edge_count; i++)
		{
			int node1, node2;
			cin >> node1 >> node2;

			if (node1 < node2)
				adjacency_list[node1].push_back(node2);
			else
				adjacency_list[node2].push_back(node1);
		}

		answer.clear();
		backtracking(1);

		cout << answer.size() << endl;

		auto it = answer.begin();
		cout << *it;
		it++;

		for (; it != answer.end(); it++)
			cout << " " << *it;

		cout << endl;
	}
}

int main193()
{
	algorithm();
	return 0;
}