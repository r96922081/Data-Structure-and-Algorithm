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

using namespace std;

int main10646()
{
	int T = 0;
	scanf("%d", &T);

	for (int i = 1; i <= T; i++)
	{
		vector<string> all_poker;
		for (int j = 0; j < 52; j++)
		{
			char poker[3];
			scanf("%s", poker);
			all_poker.insert(all_poker.begin(), poker);
		}

		int Y = 0;

		for (int j = 0; j < 3; j++)
		{
			char X_char = all_poker[25].at(0);
			int X = 0;
			if ('2' <= X_char && X_char <= '9')
				X = X_char - '2' + 2;
			else
				X = 10;
			Y += X;			

			all_poker.erase(all_poker.begin() + 25);
			all_poker.erase(all_poker.begin() + 25, all_poker.begin() + 25 + (10 - X));
		}

		cout << "Case ";
		cout << i << ": ";
		cout<< all_poker[all_poker.size() - 1 - (Y - 1)] << endl;
	}


	return 0;
}