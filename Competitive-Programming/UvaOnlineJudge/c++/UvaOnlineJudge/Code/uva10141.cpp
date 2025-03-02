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

int main10141()
{
	unsigned int n;
	unsigned int p;

	scanf("%d %d\n", &n, &p);

	int rfp_index = 1;

	while (n != 0 || p != 0)
	{
		if (rfp_index != 1)
			cout << endl;

		printf("RFP #%d\n", rfp_index++);

		string winner_str = "";
		int max_met = -1;
		double min_price = std::numeric_limits<double>::max();

		string dummy;
		for (int i = 0; i < n; i++)
			getline(cin, dummy);

		for (int i = 0; i < p; i++)
		{
			string name = "";
			getline(cin, name);

			double price = 0.0;
			scanf("%lf", &price);

			int met = 0;
			scanf("%d\n", &met);

			if (met > max_met || (met == max_met && price < min_price))
			{
				winner_str = name;
				max_met = met;
				min_price = price;
			}

			for (int j = 0; j < met; j++)
				getline(cin, dummy);
		}

		cout << winner_str << endl;

		scanf("%d %d\n", &n, &p);
	}

	return 0;
}