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
	int test_count = 0;
	cin >> test_count;

	for (int ti = 0; ti < test_count; ti++)
	{
		int non_zero_count = 0;
		cin >> non_zero_count;

		vector<vector<int>> distances;

		for (int ni = 0; ni < non_zero_count; ni++)
		{
			int row;
			int col;
			int people;
			cin >> row >> col >> people;
			vector<int> v;

			for (int i = 0; i < 25; i++)
			{
				int row2 = i / 5;
				int col2 = i % 5;

				int distance = abs(row2 - row) + abs(col2 - col);
				v.push_back(distance * people);
			}

			distances.push_back(v);
		}

		int min_sum = 1000000;
		int answer[5];

		for (int i = 0; i < 21; i++)
			for (int j = i + 1; j < 22; j++)
				for (int k = j + 1; k < 23; k++)
					for (int l = k + 1; l < 24; l++)
						for (int m = l + 1; m < 25; m++)
						{
							int sum = 0;
							for (int n = 0; n < distances.size(); n++)
							{
								vector<int>& distance = distances[n];
								int d = distance[i];
								d = min(d, distance[j]);
								d = min(d, distance[k]);
								d = min(d, distance[l]);
								d = min(d, distance[m]);
								sum += d;
							}

							if (sum < min_sum)
							{
								answer[0] = i;
								answer[1] = j;
								answer[2] = k;
								answer[3] = l;
								answer[4] = m;

								min_sum = sum;
							}

						}

		printf("%d %d %d %d %d\n", answer[0], answer[1], answer[2], answer[3], answer[4]);
	}
}

int main10660()
{
	algorithm();
	return 0;
}