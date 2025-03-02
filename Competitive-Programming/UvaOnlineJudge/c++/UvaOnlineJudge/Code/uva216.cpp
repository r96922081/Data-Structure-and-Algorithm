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

using namespace std;

static struct node
{
	int x;
	int y;
	double get_distance(node& b){ return sqrt(pow(x - b.x, 2) + pow(y - b.y, 2)) + 16; }
};

node node_array[8];
double node_distance[8][8];

static struct path
{
	path(int node) { id = (1 << node); length = 0; the_path.push_back(node); }
	void add_node(int node) { id |= (1 << node); length += node_distance[the_path.back()][node]; the_path.push_back(node); }
	vector<int> the_path;
	int id;
	bool operator==(path& b) { return id == b.id; }
	path* clone() { path* ret = new path(the_path[0]); ret->id = id; ret->the_path = the_path; ret->length = length; return ret; }
	double length;
};

vector<path> all_path_0[8];
vector<path> all_path_1[8];

// <int, double> => id, distance
map<int, double> all_distance[8];

static void algorithm()
{
	int node_count;
	int test_index = 0;

	while (cin >> node_count, node_count != 0)
	{ 
		test_index++;

		for (int i = 0; i < node_count; i++)
			cin >> node_array[i].x >> node_array[i].y;

		for (int i = 0; i < node_count; i++)
			for (int j = 0; j < node_count; j++)
				node_distance[i][j] = node_array[i].get_distance(node_array[j]);

		for (int i = 0; i < node_count; i++)
		{
			path path(i);

			all_path_0[i].clear();
			all_path_0[i].push_back(path);

			all_path_1[i].clear();
		}

		vector<path>(*last_all_path)[8] = &all_path_0;

		for (int z = 0; z < node_count - 1; z++)
		{
			vector<path>(*current_all_path)[8] = &all_path_0;
			vector<path>(*next_all_path)[8] = &all_path_1;

			if (z % 2 == 1)
			{
				current_all_path = &all_path_1;
				next_all_path = &all_path_0;
			}

			for (int i = 0; i < 8; i++)
			{
				(*next_all_path)[i].clear();
				all_distance[i].clear();
			}

			for (int i = 0; i < node_count; i++)
			{
				for (int j = 0; j < node_count; j++)
				{
 					if (i == j)
						continue;

					for (int k = 0; k < (*current_all_path)[i].size(); k++)
					{
						path* p1 = (*current_all_path)[i][k].clone();

						if ((p1->id & (1 << j)) != 0)
						{
							delete p1;
							continue;
						}

						p1->add_node(j);

						auto it = all_distance[j].find(p1->id);
						if (it != all_distance[j].end() && it->second < p1->length)
						{
							delete p1;
							continue;
						}

						all_distance[j].insert(pair<int, double>(p1->id, p1->length));

						(*next_all_path)[j].push_back(*p1);

						delete p1;
					}
				}
			}

			last_all_path = next_all_path;
		}

		path min_path = (*last_all_path)[0][0];

		for (int i = 0; i < node_count; i++)
		{
			vector<path>& path_vector = (*last_all_path)[i];

			for (int j = 0; j < path_vector.size(); j++)
			{
				path& p = path_vector[j];
				if (p.length < min_path.length)
					min_path = p;
			}
		}

		printf("**********************************************************\n");
		printf("Network #%d\n", test_index);
		for (int i = 0; i < min_path.the_path.size() - 1; i++)
		{
			node& a = node_array[min_path.the_path[i]];
			node& b = node_array[min_path.the_path[i + 1]];
			printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n", a.x, a.y, b.x, b.y, node_distance[min_path.the_path[i]][min_path.the_path[i+1]]);
		}
			
		printf("Number of feet of cable required is %.2lf.\n", min_path.length);
	}
}

int main216()
{
	algorithm();
	return 0;
}