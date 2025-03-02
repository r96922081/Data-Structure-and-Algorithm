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

using namespace std;

long long ways[30001];
int dollars[5] = {1, 5, 10, 25, 50};

static void algorithm()
{
	int sum;
	ways[0] = 1;
	while (cin >> sum)
	{
		memset(ways + 1, 0, sum * sizeof(long long));

		for (int i = 0; i < 5; i++)
		{
			int dollar = dollars[i];

			for (int j = 0; j < sum; j++)
			{
				if (ways[j] != 0)
				{
					ways[j + dollar] += ways[j];
				}
			}
		}

		if (ways[sum] == 1)
			printf("There is only 1 way to produce %d cents change.\n", sum);
		else
			printf("There are %lld ways to produce %d cents change.\n", ways[sum], sum);
	}
}

int main357()
{
	algorithm();
	return 0;
}