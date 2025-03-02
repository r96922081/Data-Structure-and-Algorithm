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

const int max_price = 302;

int value[max_price][max_price];

static void algorithm()
{
	int test_count;
	cin >> test_count;

	while (test_count--)
	{
		memset(value, 0, sizeof(value));

		int type_count;
		cin >> type_count;

		int target_price = 0;
		cin >> target_price;

		for (int i = 0; i < type_count; i++)
		{
			int x, y;
			cin >> x >> y;

			for (int j = 0; j < max_price; j++)
			{
				if (j + x >= max_price)
					continue;

				for (int k = 0; k < max_price; k++)
				{
					if (k + y >= max_price)
						continue;

					if ((j == 0 && k == 0) || value[j][k] != 0)
					{
						if (value[j + x][k + y] == 0 || value[j][k] + 1 < value[j + x][k + y])
							value[j + x][k + y] = value[j][k] + 1;
					}
				}
			}
		}

		int answer = -1;

		for (int i = 0; i < max_price; i++)
		{
			for (int j = 0; j < max_price; j++)
			{
				if (value[i][j] == 0)
					continue;

				if (i * i + j * j == target_price * target_price)
				{
					if (answer == -1 || value[i][j] < answer)
						answer = value[i][j];
				}
			}
		}

		if (answer == -1)
			cout << "not possible" << endl;
		else
			cout << answer << endl;
	}
}

int main10306()
{
	algorithm();

	return 0;
}