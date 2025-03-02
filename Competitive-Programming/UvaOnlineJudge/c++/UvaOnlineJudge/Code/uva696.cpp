#include <cstdio>
#include "stdlib.h"
#include "string.h"
#include <limits>
#include <cstddef>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main696()
{
	while (true)
	{
		int M, N, m, n;
		scanf("%d %d", &M, &N);
		if (M == 0)
			break;

		if (M < N)
		{
			m = M;
			n = N;
		}
		else
		{
			m = N;
			n = M;
		}

		if (m == 1)
		{
			printf("%d knights may be placed on a %d row %d column board.\n", m * n, M, N);
		}
		else if (m == 2)
		{
			printf("%d knights may be placed on a %d row %d column board.\n", 4 * (n / 4) + 2 * (n % 4 >= 2 ? 2 : n % 4), M, N);
		}
		else
		{
			printf("%d knights may be placed on a %d row %d column board.\n", (m * n + 1) / 2, M, N);
		}
	}

	return 0;
}