#include <vector>
#include <cassert>
#include <string>

#include "helper.h"

using namespace std;

char to_lower(char c)
{
	if ('a' <= c && c <= 'z')
		return c;
	else
		return c - 'A' + 'a';
}

string to_lower2(string s)
{
	string ret = "";
	for (size_t i = 0; i < s.size(); i++)
	{
		ret += to_lower(s[i]);
	}

	return ret;
}


vector<string> split(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

/*
static class UnionFind
{
public:
	UnionFind(int count);
	int Find(int key);
	void Union(int key1, int key2);
	bool IsSameComponent(int key1, int key2);
	virtual void AddCount(int adding_count);
private:
	vector<int> parent;
	vector<int> rank;
};*/

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

/*
static class SegmentTree
{
// index are zero-based
// key must be greater than or equal to 0

public:
	SegmentTree(const vector<int>& orignal_array);
	int Min(int left, int right);
	void Update(int index, int key);

private:
	int BuildTree(int index, int left, int right);
	int Min(int index, int q_l, int q_r, int l, int r);
	void Update(int index, int updated_index, int left, int right);

	vector<int> A;
	vector<int> tree;
};
*/

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

void Check(bool expr)
{
	if (!expr)
	{
		int a = 1;
		int b = 2;
		int c = a / b;
		assert(false);
	}
}