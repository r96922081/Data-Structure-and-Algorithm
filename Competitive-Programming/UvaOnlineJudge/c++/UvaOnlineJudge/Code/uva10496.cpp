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

const int max_n = 11;

pair<int, int> pos[max_n];
int pair_distance[max_n][max_n];
int n;

// step_count, end_n
int all_distance[max_n][max_n][(2 << max_n) - 1];

static struct queue_node {
	queue_node(int end_node, int visited_bit_mask, int step_count) : end_node(end_node), visited_bit_mask(visited_bit_mask), step_count(step_count) {}
	int end_node;
	int visited_bit_mask;
	int step_count;
};

static void algorithm()
{
	int test_count;
	cin >> test_count;

	while (test_count--)
	{
		for (int i = 0; i < max_n; i++)
			for (int j = 0; j < max_n; j++)
				pair_distance[i][j] = -1;

		for (int i = 0; i < max_n; i++)
			for (int j = 0; j < max_n; j++)
				for (int k = 0; k < (2 << max_n) - 1; k++)
					all_distance[i][j][k] = -1;

		int temp;
		cin >> temp >> temp;

		cin >> pos[0].first >> pos[0].second;

		cin >> n;

		for (int i = 1; i <= n; i++)
			cin >> pos[i].first >> pos[i].second;

		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= n; j++)
			{
				pair_distance[i][j] = (int)(abs(pos[i].first - pos[j].first)) + (int)(abs(pos[i].second - pos[j].second));
			}
		}
		
		all_distance[0][0][1] = 0;

		queue<queue_node> q;

		q.push(queue_node(0, 1, 0));

		while (!q.empty())
		{
			queue_node node = q.front();
			q.pop();

			for (int i = 1; i <= n; i++)
			{
				if (i != node.end_node && ((node.visited_bit_mask & (1 << i)) == 0))
				{
					if (all_distance[node.step_count + 1][i][(node.visited_bit_mask) | (1 << i)] == -1 ||
						all_distance[node.step_count][node.end_node][node.visited_bit_mask] + pair_distance[node.end_node][i] < all_distance[node.step_count + 1][i][(node.visited_bit_mask) | (1 << i)])
					{
						all_distance[node.step_count + 1][i][(node.visited_bit_mask) | (1 << i)] = all_distance[node.step_count][node.end_node][(node.visited_bit_mask)] + pair_distance[node.end_node][i];
						q.push(queue_node(i, node.visited_bit_mask | (1 << i), node.step_count + 1));
					}
				}
			}
		}

		int answer = -1;
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < (2 << max_n) - 1; j++)
			if (all_distance[n][i][j] != -1 && ((all_distance[n][i][j] + pair_distance[i][0] < answer) || answer == -1))
				answer = all_distance[n][i][j] + pair_distance[i][0];

		printf("The shortest path has length %d\n", answer);
	}
}

int main10496()
{
	algorithm();

	return 0;
}