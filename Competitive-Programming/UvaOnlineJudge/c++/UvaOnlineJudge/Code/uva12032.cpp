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

static bool can(vector<int> v, int distance)
{
	for (int i = 0; i < v.size(); i++)
	{
		int d2 = v[i];
		if (i > 0)
			d2 -= v[i - 1];

		if (d2 > distance)
			return false;
		else if (d2 == distance)
			distance--;
	}

	return true;
}

static void algorithm()
{
	int test_count = 0;
	cin >> test_count;

	for (int test = 1; test <= test_count; test++)
	{
		int n;
		cin >> n;
		vector<int> v;

		int temp;

		int left = 0;
		int prev = 0;

		for (int i = 0; i < n; i++)
		{
			cin >> temp;
			if (i == 0)
			{
				left = temp;
			}
			else
			{
				if (temp - prev > left)
					left = temp - prev;
			}

			v.push_back(temp);
			prev = temp;
		}

		int right = left + n - 1;

		while (left < right)
		{
			int mid = (left + right) / 2;

			if (can(v, mid))
			{
				right = mid;
			}
			else
			{
				left = mid + 1;
			}
		}

		printf("Case %d: %d\n", test, left);
	}
}

int main12032()
{
	algorithm();
	return 0;
}