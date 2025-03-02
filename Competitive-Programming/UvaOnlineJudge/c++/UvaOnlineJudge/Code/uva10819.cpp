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

int max_favor[10201];

static void algorithm()
{
	int m, n;
	while (scanf("%d%d", &m, &n) == 2)
	{
		int original_m = m;

		if (m >= 1801)
			m += 200;

		memset(max_favor, 0, (m + 1) * sizeof(int));

		vector<int> price_vector;
		vector<int> favor_vector;

		for (int i = 0; i < n; i++)
		{
			int price;
			cin >> price;
			int favor;
			cin >> favor;

			for (int j = m - price; j >= 0; j--)
			{
				if (j == 0 || max_favor[j] != 0)
					max_favor[j + price] = max(max_favor[j + price], max_favor[j] + favor);
			}
		}


		int answer = 0;

		if (1801 <= original_m && original_m <= 1999)
		{
			for (int i = 0; i <= m; i++)
			{
				if (original_m < i && i < 2001)
					continue;

				if (max_favor[i] > answer)
					answer = max_favor[i];
			}
		}
		else
		{
			for (int i = 0; i <= m; i++)
				answer = max(answer, max_favor[i]);
		}

		cout << answer << endl;
	}
}

int main10819()
{
	algorithm();

	return 0;
}