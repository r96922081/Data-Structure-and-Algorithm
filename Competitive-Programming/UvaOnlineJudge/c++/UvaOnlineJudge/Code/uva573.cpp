#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main573()
{
	int H_int;
	int U_int;
	double H = 0;
	double U = 0;
	int D = 0;
	int F = 0;

	scanf("%d %d %d %d", &H_int, &U_int, &D, &F);
	while (H_int != 0)
	{
		double H = H_int;
		double U = U_int;
		double P = 0;
		double decrease_U = (U * F) / 100.0;

		for (int i = 1;;i++)
		{
			P += U;
			if (P > H)
			{
				printf("success on day %d\n", i);
				break;
			}

			P -= D;
			if (P < 0)
			{
				printf("failure on day %d\n", i);
				break;
			}

			U -= decrease_U;
			if (U <= 0)
			{
				U = 0;
				decrease_U = 0;
			}
		}

		scanf("%d %d %d %d", &H_int, &U_int, &D, &F);
	}

	return 0;
}