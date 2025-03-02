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

static void dfs(int currentNode, vector<vector<int>>& adjList, vector<bool>& visited, vector<int>& topologicalOrder)
{
	if (visited[currentNode])
		return;

	visited[currentNode] = true;
	for (int i = 0; i < adjList[currentNode].size(); i++)
	{
		int nextNode = adjList[currentNode][i];
		dfs(nextNode, adjList, visited, topologicalOrder);
	}

	topologicalOrder.push_back(currentNode);
}

static void algorithm()
{
	int nodeCount;
	int edgeCount;

	while (cin >> nodeCount >> edgeCount, nodeCount != 0)
	{
		// 1-based
		vector<vector<int>> adjList(nodeCount + 1);
		vector<bool> visited(nodeCount + 1, false);
		vector<int> topologicalOrder;


		int a, b;
		for (int i = 0; i < edgeCount; i++)
		{
			cin >> a >> b;
			adjList[b].push_back(a);
		}

		for (int i = 1; i <= nodeCount; i++)
		{
			if (visited[i] == false)
			{
				dfs(i, adjList, visited, topologicalOrder);
			}
		}

		cout << topologicalOrder[0];
		for (int i = 1; i < topologicalOrder.size(); i++)
			printf(" %d", topologicalOrder[i]);
		cout << endl;
	}
}

int main10305()
{
	algorithm();

	return 0;
}