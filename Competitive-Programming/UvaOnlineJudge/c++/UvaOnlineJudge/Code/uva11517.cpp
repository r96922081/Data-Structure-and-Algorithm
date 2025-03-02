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
#include <list>
#include <iterator>

using namespace std;

const int max_price = 20001;

int coin_count[max_price];

static void algorithm()
{
	int test_count;
	cin >> test_count;

	while (test_count--)
	{
		memset(coin_count, 0, sizeof(coin_count));

		int target_price = 0;
		cin >> target_price;

		int type_count;
		cin >> type_count;

		for (int i = 0; i < type_count; i++)
		{
			int price;
			cin >> price;

			for (int j = target_price - 1; j >= 0; j--)
			{
				if ((j == 0) || (coin_count[j] != 0))
				{
					if (coin_count[j + price] == 0 || (coin_count[j + price] > coin_count[j] + 1))
						coin_count[j + price] = coin_count[j] + 1;
				}
			}
		}

		for (int i = target_price;; i++)
		{
			if (coin_count[i] != 0)
			{
				cout << i << " " << coin_count[i] << endl;
				break;
			}
		}
	}
}

int main11517()
{
	algorithm();

	return 0;
}