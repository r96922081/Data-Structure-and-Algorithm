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

static void algorithm()
{
	int n = 0;
	int test_index = 0;

	while (scanf("%d", &n), n != 0)
	{
		test_index++;
		cout << "Case " << test_index << ":" << endl;

		vector<int> A;
		int temp = 0;

		for (int i = 0; i < n; i++)
		{
			scanf("%d", &temp);
			A.push_back(temp);
		}

		vector<int> sums;
		for (int i = 0; i < A.size(); i++)
		{
			for (int j = i + 1; j < A.size(); j++)
			{
				sums.push_back(A[i] + A[j]);
			}
		}

		sort(sums.begin(), sums.end());

		int m = 0;
		scanf("%d", &m);

		for (int i = 0; i < m; i++)
		{
			scanf("%d", &temp);

			int left = 0;
			int right = sums.size() - 1;
			int mid = (left + right) / 2;

			while (left <= right)
			{
				int mid_value = sums[mid];

				if (mid != 0 && sums[mid - 1] <= temp && temp <= sums[mid])
				{
					if (temp - sums[mid - 1] < sums[mid] - temp)
					{
						mid = mid - 1;
					}
					break;
				}

				if (mid != sums.size() - 1 && sums[mid] <= temp && temp <= sums[mid + 1])
				{
					if (sums[mid + 1] - temp < temp - sums[mid])
					{
						mid = mid + 1;
					}
					break;
				}

				if (temp < mid_value)
					right = mid - 1;
				else
					left = mid + 1;

				mid = (left + right) / 2;
			}

			printf("Closest sum to %d is %d.\n", temp, sums[mid]);
		}
	}
}

int main10487()
{
	algorithm();
	return 0;
}