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

static struct cell
{
	cell(int row, int col) : row(row), col(col) {}
	int row;
	int col;
};

static void algorithm()
{
	int M;

	while (scanf("%d\n", &M) == 1)
	{
		int row = 0;
		int col = 0;

		vector<cell> threes;
		vector<cell> ones;

		int max_distance = 0;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
				char c;
				cin >> c;

				if (c == '1')
					ones.push_back(cell(i, j));
				else if (c == '3')
					threes.push_back(cell(i, j));
			}

			scanf("\n");
		}

		for (int i = 0; i < ones.size(); i++)
		{
			int min_distance = 200;
			for (int j = 0; j < threes.size(); j++)
			{
				int distance = abs(ones[i].col - threes[j].col) +
					abs(ones[i].row - threes[j].row);

				min_distance = min(min_distance, distance);
			}

			max_distance = max(max_distance, min_distance);
		}

		cout << max_distance << endl;
	}
}

int main10102()
{
	algorithm();
	return 0;
}