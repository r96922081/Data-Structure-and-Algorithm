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


enum PendingOp
{
	PendingOp_0,
	PendingOp_1,
	PendingOp_inverse,
	PendingOp_nothing,
};

class SegmentTreeProdcut
{
public:
	SegmentTreeProdcut(vector<int>& orignal_array);
	int Prodcut(int left, int right);
	void Update(int index, int key);

protected:
	int BuildTree(int index, int left, int right);
	int Prodcut(int index, int q_l, int q_r, int l, int r);
	void Update(int index, int updated_index, int left, int right, int key);

	vector<int>& A;
	vector<int> tree;
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
	int N, K;
	while (scanf("%d %d", &N, &K) == 2)
	{
		vector<int> A;
		A.push_back(0);

		for (int i = 0; i < N; i++)
		{
			int temp;
			scanf("%d", &temp);

			if (temp > 0)
				temp = 1;
			else if (temp < 0)
				temp = -1;

			A.push_back(temp);
		}

		SegmentTreeProdcut st(A);

		scanf("\n");

		for (int i = 0; i < K; i++)
		{
			char c;
			int a, b;
			scanf("%c %d %d\n", &c, &a, &b);
			if (c == 'C')
			{
				if (b > 0)
					st.Update(a, 1);
				else if (b < 0)
					st.Update(a, -1);
				else
					st.Update(a, 0);
			}
			else
			{
				int product = st.Prodcut(a, b);

				if (product > 0)
					cout << "+";
				else if (product < 0)
					cout << "-";
				else
					cout << 0;
			}
		}

		cout << endl;
	}
}

int main12532()
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
	//extern void TestlazySegmentTree();
	//TestlazySegmentTree();
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

SegmentTreeProdcut::SegmentTreeProdcut(vector<int>& orignal_array) : A(orignal_array)
{
	tree = vector<int>(A.size() * 4, 0);

	BuildTree(1, 0, A.size() - 1);
}

int SegmentTreeProdcut::Prodcut(int left, int right)
{
	return Prodcut(1, left, right, 0, A.size() - 1);
}

void SegmentTreeProdcut::Update(int index, int key)
{
	A[index] = key;
	return Update(1, index, 0, A.size() - 1, key);
}

void SegmentTreeProdcut::Update(int index, int updated_index, int left, int right, int key)
{
	if (updated_index < left || right < updated_index)
		return;

	if (left == right)
	{
		if (updated_index == left)
			tree[index] = key;
		return;
	}

	Update(index * 2, updated_index, left, (left + right) / 2, key);
	Update(index * 2 + 1, updated_index, (left + right) / 2 + 1, right, key);

	tree[index] = tree[index * 2] * tree[index * 2 + 1];
}

int SegmentTreeProdcut::BuildTree(int index, int left, int right)
{
	if (A.size() <= left)
		return 1;

	if (left == right)
	{
		tree[index] = A[left];
		return A[left];
	}

	int left_product = BuildTree(index * 2, left, (left + right) / 2);
	int right_product = BuildTree(index * 2 + 1, (left + right) / 2 + 1, right);

	tree[index] = left_product * right_product;
	return tree[index];
}

int SegmentTreeProdcut::Prodcut(int index, int q_l, int q_r, int l, int r)
{
	if (l > q_r || r < q_l)
		return 1;

	if (q_l <= l && r <= q_r)
		return tree[index];

	int left_product = Prodcut(index * 2, q_l, q_r, l, (l + r) / 2);
	int right_product = Prodcut(index * 2 + 1, q_l, q_r, (l + r) / 2 + 1, r);

	return left_product * right_product;
}