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

int xDiff[] = { 1, -1, 0, 0 };
int yDiff[] = { 0, 0, 1, -1 };
int M, N;
int land = -1;


static void DoFloodFill2(int x, int y, vector<vector<int>>& worldMap, int& size)
{
	if (x < 0 || x >= M)
		return;

	if (worldMap[x][y] != land)
		return;

	worldMap[x][y] = -1;
	size++;
	for (int i = 0; i < 4; i++)
	{
		int nextX = x + xDiff[i];

		int nextY = y + yDiff[i];
		if (nextY == N)
			nextY = 0;
		if (nextY == -1)
			nextY = N - 1;

		DoFloodFill2(nextX, nextY, worldMap, size);
	}
}

static int DoFloodFill(int x, int y, vector<vector<int>>& worldMap)
{
	int size = 0;
	DoFloodFill2(x, y, worldMap, size);
	return size;
}

static void algorithm()
{
	bool firstTestCase = true;
	string tempString;
	int X, Y;
	while (scanf("%d%d", &M, &N) == 2)
	{
		getline(cin, tempString);
		if (!firstTestCase)
			getline(cin, tempString);
		firstTestCase = true;
		
		vector<vector<int>> worldMap(M, vector<int>(N, 0));
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%c", &worldMap[i][j]);
			}
			getline(cin, tempString);
		}
		scanf("%d%d", &X, &Y);
		land = worldMap[X][Y];
		getline(cin, tempString);

		DoFloodFill(X, Y, worldMap);
		int maxLandSize = 0;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (worldMap[i][j] == land)
				{
					int thisLandSize = DoFloodFill(i, j, worldMap);
					maxLandSize = max(maxLandSize, thisLandSize);
				}
			}
		}

		cout << maxLandSize << endl;
	}

}

int main11094()
{
	algorithm();

	return 0;
}