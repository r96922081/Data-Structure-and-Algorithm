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


enum PendingOp
{
	PendingOp_0,
	PendingOp_1,
	PendingOp_inverse,
	PendingOp_nothing,
};

class SegmentTreeSum
{
public:
	SegmentTreeSum(vector<int>& orignal_array);
	int Sum(int left, int right);
	void Update(int index, int key);

protected:
	int BuildTree(int index, int left, int right);
	int Sum(int index, int q_l, int q_r, int l, int r);
	void Update(int index, int updated_index, int left, int right, int key);

	vector<int>& A;
	vector<int> tree;
};

class LazySegmentTreeSum : public SegmentTreeSum
{
public:
	LazySegmentTreeSum(vector<int>& orignal_array);
	int UpdateRange(int updated_left, int updated_right, PendingOp op);
	int UpdateRange(int index, int left, int right, int updated_left, int updated_right, PendingOp carry, PendingOp op);
	int Query(int left, int right);

private:
	vector<PendingOp> carrys;
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
	int N;
	scanf("%d", &N);

	for (int Ni = 0; Ni < N; Ni++)
	{
		printf("Case %d:\n", Ni + 1);
		int M;
		scanf("%d", &M);

		vector<int> pirates;

		for (int Mi = 0; Mi < M; Mi++)
		{
			int T;
			scanf("%d\n", &T);

			string pattern;
			getline(cin, pattern);

			for (int Ti = 0; Ti < T; Ti++)
			{
				for (int i = 0; i < pattern.size(); i++)
				{
					pirates.push_back(pattern[i] - '0');
				}
			}
		}

		LazySegmentTreeSum st(pirates);

		int Q;
		scanf("%d\n", &Q);

		int query_count = 0;

		for (int Qi = 0; Qi < Q; Qi++)
		{
			char type;
			int a;
			int b;
			scanf("%c %d %d\n", &type, &a, &b);

			if (type == 'F')
			{
				st.UpdateRange(a, b, PendingOp_1);			
			}
			else if (type == 'E')
			{
				st.UpdateRange(a, b, PendingOp_0);
			}
			else if (type == 'I')
			{
				st.UpdateRange(a, b, PendingOp_inverse);
			}
			else
			{
				int sum = st.Query(a, b);
				printf("Q%d: %d\n", ++query_count, sum);
			}
		}
	}
}

int main11402()
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

SegmentTreeSum::SegmentTreeSum(vector<int>& orignal_array) : A(orignal_array)
{
	tree = vector<int>(A.size() * 4, 0);

	BuildTree(1, 0, A.size() - 1);
}

int SegmentTreeSum::Sum(int left, int right)
{
	return Sum(1, left, right, 0, A.size() - 1);
}

void SegmentTreeSum::Update(int index, int key)
{
	A[index] = key;
	return Update(1, index, 0, A.size() - 1, key);
}

LazySegmentTreeSum::LazySegmentTreeSum(vector<int>& original_array) : SegmentTreeSum(original_array)
{
	carrys = vector<PendingOp>(A.size() * 4, PendingOp_nothing);
}

int LazySegmentTreeSum::Query(int left, int right)
{
	UpdateRange(1, 0, A.size() - 1, left, right, PendingOp_nothing, PendingOp_nothing);
	return Sum(left, right);
}

int LazySegmentTreeSum::UpdateRange(int updated_left, int updated_right, PendingOp op)
{
	return UpdateRange(1, 0, A.size() - 1, updated_left, updated_right, PendingOp_nothing, op);
}

int LazySegmentTreeSum::UpdateRange(int index, int left, int right, int updated_left, int updated_right, PendingOp carry, PendingOp op)
{
	if (carry != PendingOp_nothing)
	{
		if (carry == PendingOp_0)
			tree[index] = 0;
		else if (carry == PendingOp_1)
			tree[index] = right - left + 1;
		else if (carry == PendingOp_inverse)
			tree[index] = (right - left + 1) - tree[index];

		if (carry == PendingOp_inverse)
		{
			if (carrys[index] == PendingOp_inverse)
				carrys[index] = PendingOp_nothing;
			else if (carrys[index] == PendingOp_1)
				carrys[index] = PendingOp_0;
			else if (carrys[index] == PendingOp_0)
				carrys[index] = PendingOp_1;
			else
				carrys[index] = PendingOp_inverse;
		}
		else
		{
			carrys[index] = carry;
		}
	}

	if (updated_right < left || right < updated_left)
		return tree[index];

	if (updated_left <= left && right <= updated_right)
	{
		if (op == PendingOp_0)
			tree[index] = 0;
		else if (op == PendingOp_1)
			tree[index] = right - left + 1;
		else if (op == PendingOp_inverse)
			tree[index] = (right - left + 1) - tree[index];

		if (op != PendingOp_nothing)
		{
			if (op == PendingOp_inverse)
			{
				if (carrys[index] == PendingOp_inverse)
					carrys[index] = PendingOp_nothing;
				else if (carrys[index] == PendingOp_1)
					carrys[index] = PendingOp_0;
				else if (carrys[index] == PendingOp_0)
					carrys[index] = PendingOp_1;
				else
					carrys[index] = PendingOp_inverse;
			}
			else
			{
				carrys[index] = op;
			}
		}

		return tree[index];
	}		

	int left_sum = UpdateRange(index * 2, left, (left + right) / 2, updated_left, updated_right, carrys[index], op);
	int right_sum = UpdateRange(index * 2 + 1, (left + right) / 2 + 1, right, updated_left, updated_right, carrys[index], op);

	tree[index] = left_sum + right_sum;
	carrys[index] = PendingOp_nothing;

	return tree[index];
}

void SegmentTreeSum::Update(int index, int updated_index, int left, int right, int key)
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

	tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

int SegmentTreeSum::BuildTree(int index, int left, int right)
{
	if (A.size() <= left)
		return 0;

	if (left == right)
	{
		tree[index] = A[left];
		return A[left];
	}

	int left_sum = BuildTree(index * 2, left, (left + right) / 2);
	int right_sum = BuildTree(index * 2 + 1, (left + right) / 2 + 1, right);

	tree[index] = left_sum + right_sum;
	return tree[index];
}

int SegmentTreeSum::Sum(int index, int q_l, int q_r, int l, int r)
{
	if (l > q_r || r < q_l)
		return 0;

	if (q_l <= l && r <= q_r)
		return tree[index];

	int left_sum = Sum(index * 2, q_l, q_r, l, (l + r) / 2);
	int right_sum = Sum(index * 2 + 1, q_l, q_r, (l + r) / 2 + 1, r);

	return left_sum + right_sum;
}