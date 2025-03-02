#pragma once

#include <vector>

using namespace std;

char to_lower(char c);
string to_lower2(string s);
vector<string> split(const string& str, const string& delim);

/*
class UnionFind
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
};

class SegmentTree
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

class BinaryIndexTree
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