#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main11727()
{
	int t;
	scanf("%d", &t);
	int a, b, c;

	for (int i = 1; i <= t; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		printf("Case %d: ", i);
		
		if (a > b)
		{
			int temp = a;
			a = b;
			b = temp;
		}

		if (c > b)
			printf("%d", b);
		else
		{
			if (c > a)
				printf("%d", c);
			else
				printf("%d", a);
		}


		printf("\n");
	}

	return 0;
}