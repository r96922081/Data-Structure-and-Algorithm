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

int main278()
{
	int T = 0;
	scanf("%d", &T);

	while (T--)
	{
		char c[2];
		int m, n;
		scanf("%s %d %d", &c, &m, &n);

		if (c[0] == 'r' || c[0] == 'Q')
			printf("%d\n", min(m, n));
		else if (c[0] == 'K')
			printf("%d\n", ((m + 1) / 2) * ((n + 1) / 2));
		else
			printf("%d\n", (m * n + 1) / 2);
	}

	return 0;
}