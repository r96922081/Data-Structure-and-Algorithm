package main

import "fmt"

func main() {
    fmt.Println("P133")
}

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

class Node {
public:
	int val;
	vector<Node*> neighbors;

	Node() {}

	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};

class Solution {
public:
	void cloneNode(Node* oldNode, Node* newNode, map<Node*, Node*>& nodeMapping)
	{
		for (auto it = oldNode->neighbors.begin(); it != oldNode->neighbors.end(); it++)
		{
			vector<Node*> neighbors;
			Node* oldNeighbor = *it;
			auto it2 = nodeMapping.find(oldNeighbor);
			if (it2 == nodeMapping.end())
			{
				Node* newNeighbor = new Node(oldNeighbor->val, neighbors);
				newNode->neighbors.push_back(newNeighbor);
				nodeMapping.insert(pair<Node*, Node*>(oldNeighbor, newNeighbor));
				cloneNode(oldNeighbor, newNeighbor, nodeMapping);
			}
			else
			{
				newNode->neighbors.push_back(it2->second);
			}
		}
	}

	Node * cloneGraph(Node* oldNode){
		if (oldNode == NULL) {
			return NULL;
		}

		map<Node*, Node*> nodeMapping;
		vector<Node*> neighbors;
		Node* newNode = new Node(oldNode->val, neighbors);
		nodeMapping.insert(pair<Node*, Node*>(oldNode, newNode));

		cloneNode(oldNode, newNode, nodeMapping);
		
		return newNode;
	}
};

int main()
{
	Node n1(1, vector<Node*>());
	Node n2(2, vector<Node*>());
	Node n3(3, vector<Node*>());

	n1.neighbors.push_back(&n2);
	n1.neighbors.push_back(&n3);

	n2.neighbors.push_back(&n1);
	n2.neighbors.push_back(&n3);

	n3.neighbors.push_back(&n1);
	n3.neighbors.push_back(&n2);

	Solution s;
	Node * ret = s.cloneGraph(&n1);

	return 0;
}
