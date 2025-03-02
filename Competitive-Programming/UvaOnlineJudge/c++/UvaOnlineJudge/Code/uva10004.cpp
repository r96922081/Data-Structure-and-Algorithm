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

static void algorithm()
{
	int v_count;

	cin >> v_count;
	while (v_count != 0)
	{
		vector<int> color(v_count, -1);
		vector<vector<int>> adj_list(v_count, vector<int>());

		int edge_count;
		cin >> edge_count;

		while (edge_count--)
		{
			int a, b;
			cin >> a >> b;
			adj_list[a].push_back(b);
			adj_list[b].push_back(a);
		}

		queue<int> q;
		q.push(0);
		color[0] = 0;
		bool bipartiable = true;

		while (!q.empty() && bipartiable)
		{
			int src = q.front();
			q.pop();

			for (auto it = adj_list[src].begin(); it != adj_list[src].end(); it++)
			{
				int dest = *it;
				if (color[dest] == -1)
				{
					color[dest] = (color[src] + 1) % 2;
					q.push(dest);
					break;
				}
				else
				{
					if (color[dest] == color[src])
					{
						bipartiable = false;
						break;
					}
				}
			}
		}

		if (bipartiable)
			cout << "BICOLORABLE." << endl;
		else
			cout << "NOT BICOLORABLE." << endl;

		cin >> v_count;
	}
}

int main10004()
{
	algorithm();

	return 0;
}