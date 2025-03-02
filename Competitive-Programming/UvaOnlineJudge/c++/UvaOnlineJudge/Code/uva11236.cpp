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
	// 100A = a
	// idea: assume a <= b <= c <= d

	for (int a = 1; a <= 2000 && 4 * a <= 2000; a++)
	{
		for (int b = a; b <= 2000 && (a + b * 3) <= 2000; b++)
		{
			for (int c = b; c <= 2000 && (a + b + c * 2) <= 2000; c++)
			{
				// Solve the equation 100A + 100B + 100C + 100D = ABCD * 100
				// a + b + c + d = abcd * 10^-6  =>
				// 10^6 (a + b + c + d) = abcd

				long long X = 1000000 * a;
				X += 1000000 * b;
				X += 1000000 * c;
				long long Y = a * b * c - 1000000;
				
				if (Y <= 0)
					continue;

				if (X % Y != 0)
					continue;

				long long d = X / Y;

				if (d < c)
					continue;

				if (d > 2000)
					continue;

				if (a + b + c + d > 2000)
					continue;

				printf("%.2lf %.2lf %.2lf %.2lf\n",
					a / 100.0, b / 100.0,
					c / 100.0, d / 100.0);
			}
		}
	}

}

int main11236()
{
	algorithm();
	return 0;
}