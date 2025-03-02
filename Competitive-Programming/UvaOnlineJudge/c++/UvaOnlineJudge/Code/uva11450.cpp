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

using namespace std;

int price_count_array[20];
int price_2d_array[20][20];
int money;
int garment_count;

static void algorithm()
{
	int test_count;
	cin >> test_count;

	while (test_count--)
	{
		cin >> money >> garment_count;

		set<int> remaining_money;
		remaining_money.insert(0);

		for (int i = 0; i < garment_count; i++)
		{
			int price_count;
			cin >> price_count;

			price_count_array[i] = price_count;
			for (int j = 0; j < price_count; j++)
			{
				int price;
				cin >> price;
				price_2d_array[i][j] = price;
			}
		}

		for (int i = 0; i < garment_count; i++)
		{
			set<int> new_remaining_money;

			for (auto it = remaining_money.begin(); it != remaining_money.end(); it++)
			{
				int money1 = *it;
				for (int k = 0; k < price_count_array[i]; k++)
				{
					int money2 = price_2d_array[i][k];
					if (money1 + money2 <= money)
						new_remaining_money.insert(money1 + money2);
				}
			}

			remaining_money = new_remaining_money;
		}

		if (remaining_money.size() == 0)
			cout << "no solution" << endl;
		else
			cout << *remaining_money.rbegin() << endl;
	}
}

int main11450()
{
	algorithm();
	return 0;
}