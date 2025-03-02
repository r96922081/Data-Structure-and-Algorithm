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

// sum, count
long long answer_count[51][51];

static void algorithm()
{
	int n, k, m;
	while (scanf("%d%d%d", &n, &k, &m) == 3)
	{
		memset(answer_count, 0, sizeof(answer_count));

		for (int i = 1; i <= m; i++)
			answer_count[i][1] = 1;


		for (int i = 2; i <= k; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				for (int l = 1; l <= m; l++)
				{
					if (answer_count[j][i - 1] != 0 && (j + l <= n))
					{
						answer_count[j + l][i] += answer_count[j][i - 1];
					}
				}
			}
		}

		cout << answer_count[n][k] << endl;
	}
}

int main10721()
{
	algorithm();

	return 0;
}