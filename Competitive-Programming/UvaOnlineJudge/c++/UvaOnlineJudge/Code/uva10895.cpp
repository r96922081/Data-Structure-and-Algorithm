#include <cstdio>
#include "stdlib.h"
#include "string.h"
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

//////////////////// auxiliary functions /////////////////////
static class UnionFind
{
private:
	vector<int> parent;
	vector<int> rank;

public:
	UnionFind(int count) : parent(vector<int>(count, 0)), rank(vector<int>(count, 0))
	{
		for (int i = 0; i < count; i++)
			parent[i] = i;
	}

	int Find(int key)
	{
		if (parent[key] != key)
			parent[key] = Find(parent[key]);

		return parent[key];
	}

	void Union(int key1, int key2)
	{
		int u1 = Find(key1);
		int u2 = Find(key2);

		if (rank[u1] > rank[u2])
		{
			parent[u2] = u1;
		}
		else
		{
			parent[u1] = u2;
			if (rank[u1] == rank[u2])
				rank[u2]++;
		}
	}

	bool IsSameComponent(int key1, int key2)
	{
		return Find(key1) == Find(key2);
	}
};

typedef pair<int, int> ii;
typedef vector<ii> vii;

char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static void algorithm()
{
	int m;
	int n;

	while (scanf("%d %d", &m, &n) == 2)
	{
		vector<map<int, int>> transposed_adjaceny_list(n, map<int, int>());

		for (int row = 0; row < m; row++)
		{
			int non_zero_element_count = 0;
			scanf("%d", &non_zero_element_count);

			vector<int> non_zero_columns;
			for (int i = 0; i < non_zero_element_count; i++)
			{
				int column = 0;
				scanf("%d", &column);
				non_zero_columns.push_back(column - 1);
			}

			for (int i = 0; i < non_zero_element_count; i++)
			{
				int value;
				scanf("%d", &value);
				int transposed_column = row;
				int transposed_row = non_zero_columns[i];
				transposed_adjaceny_list[transposed_row].insert(pair<int, int>(transposed_column, value));
			}
		}

		printf("%d %d\n", n, m);
		for (int row = 0; row < n; row++)
		{
			auto row_info = transposed_adjaceny_list[row];
			printf("%d", row_info.size());
			for (auto it = row_info.begin(); it != row_info.end(); it++)
			{
				printf(" %d", it->first + 1);
			}
			printf("\n");
			for (auto it = row_info.begin(); it != row_info.end(); it++)
			{
				if (it != row_info.begin())
					printf(" ");
				printf("%d", it->second);
			}
			printf("\n");
		}
	}
}

int main10895()
{
	//extern void UnitTest();
	//UnitTest();
	algorithm();
	return 0;
}

static void Check(bool expr)
{
	if (!expr)
	{
		int a = 1;
		int b = 2;
		int c = a / b;
		assert(false);
	}

}

///////////////////// UT //////////////////////

static void UnitTest()
{

}

//////////////////// auxiliary functions /////////////////////

static char to_lower(char c)
{
	if ('a' <= c && c <= 'z')
		return c;
	else
		return c - 'A' + 'a';
}

static string to_lower2(string s)
{
	string ret = "";
	for (int i = 0; i < s.size(); i++)
	{
		ret += to_lower(s[i]);
	}

	return ret;
}