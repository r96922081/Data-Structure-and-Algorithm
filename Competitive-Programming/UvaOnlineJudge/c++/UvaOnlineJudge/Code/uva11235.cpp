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

static class SegmentTree
{
	// index are zero-based
	// key must be greater than or equal to 0

public:
	SegmentTree(const vector<int>& orignal_array)
	{
		A = orignal_array;
		tree = vector<int>(A.size() * 4);

		BuildTree(1, 0, A.size() - 1);
	}

	int Min(int left, int right)
	{
		return Min(1, left, right, 0, A.size() - 1);
	}

	void Update(int index, int key)
	{
		A[index] = key;
		return Update(1, index, 0, A.size() - 1);
	}


private:
	void Update(int index, int updated_index, int left, int right)
	{
		if (updated_index < left || right < updated_index)
			return;

		if (left == right)
			return;

		Update(index * 2, updated_index, left, (left + right) / 2);
		Update(index * 2 + 1, updated_index, (left + right) / 2 + 1, right);

		int left_min = tree[index * 2];
		int right_min = tree[index * 2 + 1];

		if (tree[left_min] != -1 && tree[right_min] != -1)
			tree[index] = A[left_min] < A[right_min] ? left_min : right_min;
	}

	int BuildTree(int index, int left, int right)
	{
		if (left == right)
		{
			tree[index] = left;
			return left;
		}

		size_t left_min = BuildTree(index * 2, left, (left + right) / 2);
		size_t right_min = BuildTree(index * 2 + 1, (left + right) / 2 + 1, right);

		int min = 0;

		if (A[left_min] <= A[right_min])
			min = left_min;
		else
			min = right_min;

		tree[index] = min;
		return min;
	}

	int Min(int index, int q_l, int q_r, int l, int r)
	{
		if (l > q_r || r < q_l)
			return -1;

		if (q_l <= l && r <= q_r)
			return tree[index];

		int l_min = Min(index * 2, q_l, q_r, l, (l + r) / 2);
		int r_min = Min(index * 2 + 1, q_l, q_r, (l + r) / 2 + 1, r);

		if (r_min == -1)
			return l_min;
		else if (l_min == -1)
			return r_min;

		if (A[l_min] <= A[r_min])
			return l_min;
		else
			return r_min;
	}

	vector<int> A;
	vector<int> tree;
};

/*
static class BinaryIndexTree
{
public:
	BinaryIndexTree(int max_int);
	int RangeSumQuery(int begin, int end);
	int RSQ(int begin, int end);
	void Adjust(int index, int adjust_value);

private:
	int RangeSumQuery(int index);
	int LeastSignificantOne(int n);
	int LSOne(int n);
	vector<int> tree;
	int max_int;
};
*/

static class BinaryIndexTree
{
public:
	BinaryIndexTree(int max_int) : tree(vector<int>(1 + max_int, 0)), max_int(max_int) {}

	int RangeSumQuery(int begin, int end)
	{
		return RangeSumQuery(end) - RangeSumQuery(begin - 1);
	}

	int RSQ(int begin, int end)
	{
		return RangeSumQuery(begin, end);
	}

	void Adjust(int index, int adjust_value)
	{
		for (; index <= max_int; index += LSOne(index))
			tree[index] += adjust_value;
	}

private:
	int RangeSumQuery(int index)
	{
		int sum = 0;
		for (; index >= 1; index -= LSOne(index))
			sum += tree[index];

		return sum;
	}

	int LeastSignificantOne(int n)
	{
		return n & -n;
	}

	int LSOne(int n)
	{
		return LeastSignificantOne(n);
	}
	vector<int> tree;
	int max_int;
};

char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static struct NumberInfo
{
	NumberInfo() : leaf_index(0), start(0), end(0) {}
	int leaf_index;
	int start;
	int end;
};

static void algorithm()
{
	int n = 0;
	while (scanf("%d", &n), n != 0)
	{
		vector<int> all_numbers;
		all_numbers.push_back(-999999999);
		map<int, NumberInfo> all_number_info;
		int query_count = 0;
		scanf("%d", &query_count);

		int leaf_index = 0;
		int prev_number = 0;
		scanf("%d", &prev_number);
		all_numbers.push_back(prev_number);
		int number = prev_number;
		int start = 1;		

		for (int i = 2; i <= n; i++)
		{
			scanf("%d", &number);
			all_numbers.push_back(number);

			if (number != prev_number)
			{
				NumberInfo ni;
				ni.start = start;
				ni.end = i - 1;
				ni.leaf_index = leaf_index;
				all_number_info.insert(pair<int, NumberInfo>(prev_number, ni));

				start = i;
				prev_number = number;
				leaf_index++;
			}
		}

		NumberInfo ni;
		ni.start = start;
		ni.end = n;
		ni.leaf_index = leaf_index;
		all_number_info.insert(pair<int, NumberInfo>(number, ni));

		vector<int> v;
		for (auto it = all_number_info.begin(); it != all_number_info.end(); it++)
		{
			int count = it->second.end - it->second.start + 1;
			v.push_back(100000 - count);
		}

		SegmentTree st(v);

		for (int i = 0; i < query_count; i++)
		{
			int start_seg;
			int end_seg;
			scanf("%d %d", &start_seg, &end_seg);

			int start_num = all_numbers[start_seg];
			NumberInfo& ni1 = all_number_info[start_num];
			int end_num = all_numbers[end_seg];
			NumberInfo& ni2 = all_number_info[end_num];
			if (ni1.leaf_index == ni2.leaf_index)
			{
				cout << end_seg - start_seg + 1 << endl;
				continue;
			}

			int start_num_count = ni1.end - ni1.start + 1;
			start_num_count = 100000 - start_num_count;

			st.Update(ni1.leaf_index, 100000 - (ni1.end - start_seg + 1));
			v[ni1.leaf_index] = 100000 - (ni1.end - start_seg + 1);

			int end_num_count = ni2.end - ni2.start + 1;
			end_num_count = 100000 - end_num_count;

			st.Update(ni2.leaf_index, 100000 - (end_seg - ni2.start + 1));
			v[ni2.leaf_index] = 100000 - (end_seg - ni2.start + 1);

			int min_node_index = st.Min(ni1.leaf_index, ni2.leaf_index);
			cout << 100000 - v[min_node_index] << endl;

			st.Update(ni1.leaf_index, start_num_count);
			v[ni1.leaf_index] = start_num_count;

			st.Update(ni2.leaf_index, end_num_count);
			v[ni2.leaf_index] = end_num_count;
		}
	}
}

int main11235()
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
	extern void TestSegmentTree();
	TestSegmentTree();
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
	for (size_t i = 0; i < s.size(); i++)
	{
		ret += to_lower(s[i]);
	}

	return ret;
}