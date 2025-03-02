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

static void algorithm()
{
	int nodeCount;
	int t = 1;
	string temp1;
	string temp2;
	
	while (scanf("%d", &nodeCount) == 1)
	{
		map<string, int> mapping;
		map<int, string> mapping2;
		vector<vector<int>> adjList(nodeCount);
		vector<int> inDegree(nodeCount);
		vector<int> topologicalOrder;

		for (int i = 0; i < nodeCount; i++)
		{
			cin >> temp1;
			mapping.insert(pair<string, int>(temp1, i));
			mapping2.insert(pair<int, string>(i, temp1));
		}

		int edgeCount;
		cin >> edgeCount;

		for (int i = 0; i < edgeCount; i++)
		{
			cin >> temp1 >> temp2;
			adjList[mapping[temp1]].push_back(mapping[temp2]);
			inDegree[mapping[temp2]]++;
		}

		list<int> nonVisitedList;
		for (int i = 0; i < nodeCount; i++)
			nonVisitedList.push_back(i);

		while (nonVisitedList.size() > 0)
		{
			for (auto it = nonVisitedList.begin(); it != nonVisitedList.end(); it++)
			{
				bool breakMe = false;
				int node = *it;
				if (inDegree[node] == 0)
				{
					topologicalOrder.push_back(node);
					nonVisitedList.erase(it);
					for (int i = 0; i < adjList[node].size(); i++)
					{
						int adjNode = adjList[node][i];
						inDegree[adjNode]--;
					}
					breakMe = true;
					break;
				}
				if (breakMe)
					break;
			}
		}


		printf("Case #%d: Dilbert should drink beverages in this order:", t);
		for (int i = 0; i < topologicalOrder.size(); i++)
		{
			cout << " " << mapping2[topologicalOrder[i]];
		}

		printf(".\n\n");

		t++;
	}
}

int main11060()
{
	algorithm();

	return 0;
}