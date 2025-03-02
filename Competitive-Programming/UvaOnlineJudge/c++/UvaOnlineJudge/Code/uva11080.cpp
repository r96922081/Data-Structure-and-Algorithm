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
	int testCase;
	cin >> testCase;

	while (testCase--)
	{
		int nodeCount, edgeCount;
		cin >> nodeCount >> edgeCount;
		vector<vector<int>> adjList(nodeCount, vector<int>());
		for (int i = 0; i < edgeCount; i++)
		{
			int f, t;
			cin >> f >> t;
			adjList[f].push_back(t);
			adjList[t].push_back(f);
		}

		vector<int> color(nodeCount, -1);
		int colorCount[2] = { 0, 0 };
		bool goNextTest = false;
		int answer = 0;

		for (int i = 0; i < nodeCount; i++)
		{
			if (color[i] == -1)
			{
				colorCount[0] = 0;
				colorCount[1] = 0;
				int newColor = 0;

				queue<int> q;
				q.push(i);
				color[i] = newColor;
				colorCount[newColor]++;

				while (!q.empty())
				{
					int thisNode = q.front();
					q.pop();

					for (int j = 0; j < adjList[thisNode].size(); j++)
					{
						int nextNode = adjList[thisNode][j];
						if (color[nextNode] == -1)
						{
							color[nextNode] = 1 - color[thisNode];
							colorCount[color[nextNode]]++;
							q.push(nextNode);
						} else {
							if (color[nextNode] == color[thisNode])
							{
								cout << -1 << endl;
								goNextTest = true;
								break;
							}
						}
					}

					if (goNextTest)
						break;
				}

				if (colorCount[1] == 0)
					answer++;
				else
					answer += colorCount[0] < colorCount[1] ? colorCount[0] : colorCount[1];

				if (goNextTest)
					break;
			}
		}

		if (goNextTest)
			continue;

		cout << answer << endl;
	}
}

int main11080()
{
	algorithm();

	return 0;
}