#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const int max_deprecation_count = 100;
int deprecations_start_month[max_deprecation_count + 1];
double deprecations[max_deprecation_count + 1];

int main10114()
{
	int loan_month = 0;
	double down_payment;
	double loan;
	int deprecation_count;
	double car_price;

	scanf("%d %lf %lf %d", &loan_month, &down_payment, &loan, &deprecation_count);

	while (loan_month > 0)
	{
		double pay_per_month = loan / loan_month;

		int i = 0;
		for (; i < deprecation_count; i++)
		{
			scanf("%d %lf", &deprecations_start_month[i], &deprecations[i]);
		}
		deprecations_start_month[i] = 101;
		deprecations[i] = deprecations[i - 1];

		car_price = (loan + down_payment) * (1 - deprecations[0]);

		int current_month = 1;
		int start_month_index = 1;
		double deprecation = deprecations[0];

		while (true)
		{
			if (loan < car_price)
			{
				printf("%d month%s\n", current_month - 1, (current_month - 1) == 1 ? "" : "s");
				break;
			}				

			if (current_month == deprecations_start_month[start_month_index])
			{
				deprecation = deprecations[start_month_index];
				++start_month_index;
			}
				
			loan -= pay_per_month;
			car_price *= (1 - deprecation);

			current_month++;
		}

		scanf("%d %lf %lf %d", &loan_month, &down_payment, &loan, &deprecation_count);
	}

	return 0;
}