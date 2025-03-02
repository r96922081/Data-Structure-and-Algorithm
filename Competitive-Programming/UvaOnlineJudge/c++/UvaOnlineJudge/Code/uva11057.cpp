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

static void algorithm()
{
	int book_count;
	int temp;

	while (scanf("%d", &book_count) == 1)
	{
		vector<int> prices;
		int answer_price1 = 0;
		int answer_price2 = 2000003;

		for (int i = 0; i < book_count; i++)
		{
			cin >> temp;
			prices.push_back(temp);
		}

		int sum;
		cin >> sum;

		sort(prices.begin(), prices.end());

		for (int i = 0; i < prices.size(); i++)
		{
			int price1 = prices[i];
			int price2 = sum - price1;
			bool hit = false;

			int left = i + 1;
			int right = prices.size() - 1;

			while (left <= right)
			{
				int mid = (left + right) / 2;

				int mid_value = prices[mid];

				if (mid_value == price2)
				{
					hit = true;
					break;
				}

				if (mid_value < price2)
					left = mid + 1;
				else
					right = mid - 1;
			}

			if (hit)
			{
				if (price1 > price2)
				{
					temp = price1;
					price1 = price2;
					price2 = temp;
				}

				if (price2 - price1 < answer_price2 - answer_price1)
				{
					answer_price1 = price1;
					answer_price2 = price2;
				}
			}
		}

		printf("Peter should buy books whose prices are %d and %d.\n\n", answer_price1, answer_price2);
	}
}

int main11057()
{
	algorithm();
	return 0;
}