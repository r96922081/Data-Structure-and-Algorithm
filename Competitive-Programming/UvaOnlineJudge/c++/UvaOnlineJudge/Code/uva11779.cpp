#include <cstdio>
#include "stdlib.h"
#include "string.h"
#include <limits>
#include <cstddef>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

int main11779()
{
	int T = 0;
	scanf("%d", &T);

	for (int i = 1; i <= T; i++)
	{
		int max = 0;
		int N = 0;
		scanf("%d", &N);

		while (N--)
		{
			int speed = 0;
			scanf("%d", &speed);

			if (speed > max)
				max = speed;
		}

		printf("Case %d: %d\n", i, max);
	}

	return 0;
}