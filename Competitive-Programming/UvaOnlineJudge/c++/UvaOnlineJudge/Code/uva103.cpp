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

using namespace std;

static struct TreeNode
{
	TreeNode(int box_index, vector<int> box_size) : box_index(box_index), box_size(box_size) {}

	int box_index;
	vector<int> box_size;
	list<TreeNode*> children;
};

static bool Bigger(TreeNode* a, TreeNode* b)
{
	for (int i = 0; i < a->box_size.size(); i++)
		if (a->box_size[i] < b->box_size[i])
			return false;

	return true;
}

static vector<int> max_depth(TreeNode* a)
{
	vector<int> ret;

	for (auto it = a->children.begin(); it != a->children.end(); it++)
	{
		vector<int> child_answer = max_depth(*it);
		
		if (child_answer.size() > ret.size())
			ret = child_answer;
	}

	ret.insert(ret.begin(), a->box_index);

	return ret;
}

static bool compatible(TreeNode* a, TreeNode* b)
{
	return Bigger(a, b) || Bigger(b, a);
}

// insert B to A
static void InsertNode(TreeNode* a_parent, TreeNode* a, TreeNode* b)
{
	if (Bigger(b, a))
	{
		for (auto it = a->children.begin(); it != a->children.end(); it++)
		{
			TreeNode* child = *it;
			if (compatible(child, b))
			{
				InsertNode(a, child, b);
				return;
			}
		}

		a->children.push_back(b);

		return;
	}
	else if (Bigger(a, b))
	{
		a_parent->children.remove(a);
		a_parent->children.push_back(b);
		b->children.push_back(a);
	}
}

static void algorithm()
{
	int box_count, dimension;

	while (cin >> box_count >> dimension)
	{
		vector<int> v(dimension, 0);

		TreeNode root(0, v);
		vector<TreeNode*> all_node;

		for (int i = 0; i < box_count; i++)
		{
			vector<int> v;

			for (int j = 0; j < dimension; j++)
			{
				int temp;
				cin >> temp;
				v.push_back(temp);
			}

			sort(v.begin(), v.end());
			TreeNode *node = new TreeNode(i + 1, v);
			all_node.push_back(node);
			InsertNode(NULL, &root, node);
		}

		vector<int> ret = max_depth(&root);
		ret.erase(ret.begin());

		cout << ret.size() << endl;
		cout << ret[0];

		for (int i = 1; i < ret.size(); i++)
			cout << " " << ret[i];

		cout << endl;

		for (auto it = all_node.begin(); it != all_node.end(); it++)
			delete *it;
	}
}

int main103()
{
	algorithm();
	return 0;
}