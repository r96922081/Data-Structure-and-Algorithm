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

static struct DisjointElement {
	int val;
	DisjointElement* parent;
	int rank;
};

class DisjointSet
{
public:
	DisjointSet(int n)
	{
		Reset(n);
	}

	int Add()
	{
		elements.push_back(new DisjointElement());
		int index = elements.size() - 1;
		elements[index]->val = index;
		elements[index]->rank = 1;
		elements[index]->parent = NULL;
		return index;
	}

	void Reset(int size)
	{
		elements.resize(size);
		for (int i = 0; i < size; i++)
		{
			elements[i] = new DisjointElement();
			elements[i]->val = i;
			elements[i]->rank = 1;
			elements[i]->parent = NULL;
		}
	}

	~DisjointSet()
	{
		for (auto it = elements.begin(); it != elements.end(); it++)
		{
			delete *it;
		}
	}

	DisjointElement* Find(int n)
	{
		DisjointElement* e = elements[n];
		if (e->parent == NULL)
			return e;

		e->parent = Find(e->parent->val);
		return e->parent;
	}

	void Union(int m, int n)
	{
		DisjointElement* e1 = Find(m);
		DisjointElement* e2 = Find(n);
		if (e1 == e2)
			return;

		if (e1->rank >= e2->rank)
		{
			if (e1->rank == e2->rank)
				e1->rank++;

			e2->parent = e1;
		}
		else
		{
			e1->parent = e2;
		}
	}

	vector<DisjointElement*> elements;
};


static struct edge {
	int node1;
	int node2;
	long long length;
};

static struct node {
	long long x;
	long long y;
};

static struct group_struct {
	group_struct() :disjoint_set(0) {}
	map<int, int> mapping_to_disjoint_set;
	DisjointSet disjoint_set;
};

static bool sort_function(edge a, edge b) 
{
	return a.length < b.length;
}

int main11228()
{
	int test_count;
	cin >> test_count;
	for (int ti = 1; ti <= test_count; ti++)
	{
		int node_count, r;
		cin >> node_count >> r;

		int r_square = pow(r, 2);

		vector<node> all_node(node_count, node());

		for (int i = 0; i < node_count; i++)
		{
			cin >> all_node[i].x >> all_node[i].y;
		}

		vector<edge> all_edge;
		for (int i = 0; i < node_count; i++)
		{
			for (int j = i + 1; j < node_count; j++)
			{
				edge e;
				e.node1 = i;
				e.node2 = j;
				e.length = pow(all_node[i].x - all_node[j].x, 2) + pow(all_node[i].y - all_node[j].y, 2);
				all_edge.push_back(e);
			}
		}

		sort(all_edge.begin(), all_edge.end(), sort_function);

		DisjointSet disjoint_set(node_count);

		for (auto it = all_edge.begin(); it != all_edge.end(); it++)
		{
			if (it->length <= r_square)
			{
				disjoint_set.Union(it->node1, it->node2);
			}
		}

		group_struct group_of_groups;
		map<int, group_struct*> groups;

		for (int i = 0; i < node_count; i++)
		{
			auto it1 = group_of_groups.mapping_to_disjoint_set.find((disjoint_set.Find(i))->val);
			
			if (it1 == group_of_groups.mapping_to_disjoint_set.end())
			{
				group_of_groups.mapping_to_disjoint_set.insert(pair<int,int>((disjoint_set.Find(i))->val, group_of_groups.disjoint_set.Add()));
				groups.insert(pair<int, group_struct*>((disjoint_set.Find(i))->val, new group_struct()));
			}

			group_struct* group = groups.find((disjoint_set.Find(i))->val)->second;
			group->mapping_to_disjoint_set.insert(pair<int, int>(i, group->disjoint_set.Add()));
		}

		int total_group_edges = 0;
		double total_len_within_group = 0;
		double total_len_between_group = 0;

		for (auto it = all_edge.begin(); it != all_edge.end(); it++)
		{
			edge e = *it;
			DisjointElement *set1 = disjoint_set.Find(e.node1);
			DisjointElement *set2 = disjoint_set.Find(e.node2);

			int group_index1 = group_of_groups.mapping_to_disjoint_set.find(set1->val)->second;
			int group_index2 = group_of_groups.mapping_to_disjoint_set.find(set2->val)->second;

			if (group_of_groups.disjoint_set.Find(group_index1) != group_of_groups.disjoint_set.Find(group_index2))
			{
				group_of_groups.disjoint_set.Union(group_index1, group_index2);
				total_len_between_group += sqrt(e.length);
			}

			group_struct* group1 = groups.find(set1->val)->second;
			group_struct* group2 = groups.find(set2->val)->second;

			if (group1 == group2)
			{
				int ds_index1 = group1->mapping_to_disjoint_set.find(e.node1)->second;
				int ds_index2 = group1->mapping_to_disjoint_set.find(e.node2)->second;

				if (group1->disjoint_set.Find(ds_index1) != group1->disjoint_set.Find(ds_index2))
				{
					group1->disjoint_set.Union(ds_index1, ds_index2);
					total_len_within_group += sqrt(e.length);
				}
			}
		}

		int total_len_within_group_int = floor(total_len_within_group);
		if (total_len_within_group - total_len_within_group_int >= 0.5)
			total_len_within_group_int++;

		int total_len_between_group_int = floor(total_len_between_group);
		if (total_len_between_group - total_len_between_group_int >= 0.5)
			total_len_between_group_int++;

		printf("Case #%d: %d %d %d\n", ti, groups.size(),
			total_len_within_group_int,
			total_len_between_group_int);

		for (auto it = groups.begin(); it != groups.end(); it++)
			delete it->second;
	}

	return 0;
}