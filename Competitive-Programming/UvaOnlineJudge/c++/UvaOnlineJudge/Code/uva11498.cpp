#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main11498()
{
	int t1, t2;
	int x, y;
	int x2, y2;

	while (scanf("%d", &t1) && t1)
	{
		scanf("%d %d", &x, &y);
		while (t1--)
		{
			scanf("%d %d", &x2, &y2);
			if (x == x2 || y == y2)
			{
				printf("divisa\n");
				continue;
			}

			if (y2 > y)
				printf("N");
			else
				printf("S");

			if (x2 > x)
				printf("E\n");
			else
				printf("O\n");
		}
	}

	return 0;
}