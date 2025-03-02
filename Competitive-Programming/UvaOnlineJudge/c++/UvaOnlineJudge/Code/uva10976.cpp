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
	unsigned long long k;
	while (scanf("%lld", &k) == 1)
	{
		vector<unsigned long long> Y;
		vector<unsigned long long> X;

		for (unsigned long long y = k; y <= 2 * k; y++)
		{
			unsigned long long yk = y * k;
			unsigned long long y_k = y - k;
			if (y_k != 0 && yk % y_k == 0)
			{
				X.push_back(yk / y_k);
				Y.push_back(y);
			}
		}

		cout << X.size() << endl;

		for (int i = 0; i < X.size(); i++)
			printf("1/%lld = 1/%lld + 1/%lld\n", k, X[i], Y[i]);
	}
}

int main10976()
{
	algorithm();
	return 0;
}