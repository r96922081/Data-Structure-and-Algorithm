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
	int n, d, r;

	while (cin >> n >> d >> r, n != 0)
	{
		vector<int> route1, route2;
		int temp;

		for (int i = 0; i < n; i++)
		{
			cin >> temp;
			route1.push_back(temp);
		}

		for (int i = 0; i < n; i++)
		{
			cin >> temp;
			route2.push_back(temp);
		}

		sort(route1.begin(), route1.end());
		sort(route2.begin(), route2.end());

		int overtime_pay = 0;

		for (int i = 0; i < n; i++)
		{
			overtime_pay += max (0, (route1[i] + route2[n - 1 - i] - d)) * r;
		}

		cout << overtime_pay << endl;
	}
}

int main11389()
{
	algorithm();
	return 0;
}