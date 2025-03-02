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
	int test_case_count = 0;
	scanf("%d\n", &test_case_count);

	for (int ti = 0; ti < test_case_count; ti++)
	{
		int n = 0;
		scanf("%d", &n);

		vector<int> a;

		for (int i = 0; i <= n; i++)
		{
			int temp;
			scanf("%d", &temp);
			a.push_back(temp);
		}

		int d = 0;
		scanf("%d", &d);

		int k = 0;
		scanf("%d\n", &k);

		int k2 = 0;
		int index = 0;

		while (k2 < k)
		{
			index++;
			k2 += index * d;
		}

		unsigned long long ans = 0;
		for (int i = 0; i < a.size(); i++)
		{
			unsigned long long poly = 1;

			for (int j = 0; j < i; j++)
			{
				poly *= index;
			}

			ans += a[i] * poly;
		}

		cout << ans << endl;
	}
}

int main927()
{
	algorithm();
	return 0;
}