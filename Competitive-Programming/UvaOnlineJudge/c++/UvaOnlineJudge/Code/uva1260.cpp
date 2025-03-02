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
	int test_case_count;
	scanf("%d", &test_case_count);

	for (int ti = 0; ti < test_case_count; ti++)
	{
		int n = 0;
		scanf("%d", &n);

		vector<int> A;
		int temp;
		int sum = 0;

		for (int i = 0; i < n; i++)
		{
			scanf("%d", &temp);
			A.push_back(-1);
			int j;
			
			for (j = A.size() - 1; j > 0; j--)
			{
				if (temp < A[j - 1])
				{
					A[j] = A[j - 1];
				}
				else
				{
					break;
				}
			}

			A[j] = temp;
			sum += j;
		}

		cout << sum << endl;
	}
}

int main1260()
{
	algorithm();
	return 0;
}