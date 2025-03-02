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

const int INFINITE = 999999999;
const int MAX_NODE_COUNT = 51;

int pair_distance[MAX_NODE_COUNT][MAX_NODE_COUNT];
int store_diff[MAX_NODE_COUNT];
long long store_want_to_visit;
int saved_money = 0;
map<long long, int> shortest_path_between_ends[MAX_NODE_COUNT];

struct QueueElement {
	QueueElement(long long used_bit_mask, long long visited_bit_mask, int end) : used_bit_mask(used_bit_mask), visited_bit_mask(visited_bit_mask), end(end) {}
	long long used_bit_mask;
	long long visited_bit_mask;
	int end;
};

void algorithm()
{
	int test_count;
	cin >> test_count;

	while (test_count--)
	{
		for (int i = 0; i < MAX_NODE_COUNT; i++)
			for (int j = 0; j < MAX_NODE_COUNT; j++)
				pair_distance[i][j] = INFINITE;

		for (int i = 0; i < MAX_NODE_COUNT; i++)
		{
			shortest_path_between_ends[i].clear();
			shortest_path_between_ends[i].insert(make_pair(0, 0));
			store_diff[i] = 0;
		}

		store_want_to_visit = 0;
		saved_money = -1;

		int node_count;
		int edge_count;

		cin >> node_count >> edge_count;

		node_count++;

		for (int i = 0; i < edge_count; i++)
		{
			int src;
			int dest;
			double len;

			cin >> src >> dest >> len;

			if ((int)(len * 100) < pair_distance[src][dest])
			{
				pair_distance[src][dest] = (int)(len * 100);
				pair_distance[dest][src] = (int)(len * 100);
			}
		}

		for (int k = 0; k < node_count; k++)
			for (int i = 0; i < node_count; i++)
				for (int j = 0; j < node_count ; j++)
					if (pair_distance[i][k] + pair_distance[k][j] < pair_distance[i][j])
						pair_distance[i][j] = pair_distance[i][k] + pair_distance[k][j];


		int store_want_to_visit_count;
		cin >> store_want_to_visit_count;

		for (int i = 0; i < store_want_to_visit_count; i++)
		{
			int n;
			double diff;

			cin >> n >> diff;

			store_diff[n] = (int)(diff * 100);

			store_want_to_visit |= (((long long)1) << n);
		}

		queue<QueueElement> q;
		
		q.push(QueueElement(0, 0, 0));

		while (!q.empty())
		{
			QueueElement q_element = q.front();
			q.pop();

			long long visited_bit_mask = q_element.visited_bit_mask;
			long long used_bit_mask = q_element.used_bit_mask;
			int end = q_element.end;

			for (int i = 1; i < node_count; i++)
			{
				long long compare_bit_mask = (((long long)1) << i);

				if (((used_bit_mask & compare_bit_mask) == 0) && ((compare_bit_mask & store_want_to_visit) != 0))
				{
					long long new_used_bit_mask = used_bit_mask | compare_bit_mask;

					// not use this store
					q.push(QueueElement(new_used_bit_mask, visited_bit_mask, end));

					// use this store
					int prev_len = shortest_path_between_ends[end].find(visited_bit_mask)->second;
					long long new_visited_bit_mask = (visited_bit_mask | compare_bit_mask);
					int new_len = prev_len + pair_distance[end][i];

					auto it = shortest_path_between_ends[i].find(new_visited_bit_mask);
					if (it == shortest_path_between_ends[i].end())
						shortest_path_between_ends[i].insert(make_pair(new_visited_bit_mask, new_len));
					else if (new_len < it->second)
						it->second = new_len;

					q.push(QueueElement(new_used_bit_mask, new_visited_bit_mask, i));

					// Calculate saved money
					int total_diff = 0;
					for (int i = 1; i < node_count; i++)
						if ((new_visited_bit_mask & (((long long)1) << i)) != 0)
							total_diff += store_diff[i];

					int new_saved_money = total_diff - (new_len + pair_distance[i][0]);

					if (new_saved_money > saved_money)
						saved_money = new_saved_money;
				}
			}
		}

		if (saved_money <= 0)
			cout << "Don't leave the house" << endl;
		else
			printf("Daniel can save $%.2lf\n", ((double)saved_money) / 100);
	} // while (test_count--)
}

int main()
{
	algorithm();

	return 0;
}