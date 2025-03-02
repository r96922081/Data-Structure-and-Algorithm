package main

import "fmt"

func main() {
    fmt.Println("P138")
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
	Node* next;
	Node* random;

	Node() {}

	Node(int _val, Node* _next, Node* _random) {
		val = _val;
		next = _next;
		random = _random;
	}
};

class Solution {
public:
	Node * copyRandomList(Node* head) {
		if (head == NULL) {
			return NULL;
		}

		map<Node*, Node*> nodeMapping;
		nodeMapping.insert(pair<Node*, Node*>(NULL, NULL));

		for (Node* node = head; node != NULL; node = node->next)
		{
			Node* newNode = new Node(NULL, NULL, NULL);
			nodeMapping.insert(pair<Node*, Node*>(node, newNode));
		}

		for (Node* node = head; node != NULL; node = node->next)
		{
			Node* newNode = (nodeMapping.find(node))->second;
			newNode->val = node->val;
			newNode->next = (nodeMapping.find(node->next))->second;
			newNode->random = (nodeMapping.find(node->random))->second;
		}

		return (nodeMapping.find(head))->second;
	}
};

int main()
{	
	Node* n1 = new Node(1, NULL, NULL);
	Node* n2 = new Node(2, NULL, NULL);
	n1->next = n2;
	n1->random = n2;
	n2->random = n2;

	Solution s;
	s.copyRandomList(n1);

	return 0;
}
