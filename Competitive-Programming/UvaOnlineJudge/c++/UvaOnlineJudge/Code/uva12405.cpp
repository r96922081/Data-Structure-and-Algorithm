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
	int tc_count;
	cin >> tc_count;

	for (int tc_index = 1; tc_index <= tc_count; tc_index++)
	{
		int size = 0;
		cin >> size;
		scanf("\n");

		bool skip = false;
		bool set_scarecrow = false;
		int scarecrow_count = 0;

		char temp;
		for (int i = 0; i < size; i++)
		{
			cin >> temp;

			if (skip)
			{
				skip = false;
				continue;
			}

			if (set_scarecrow)
			{
				skip = true;
				scarecrow_count++;
				set_scarecrow = false;
			}
			else
			{
				if (temp == '.')
				{
					set_scarecrow = true;
				}
			}
		}

		if (set_scarecrow)
			scarecrow_count++;

		scanf("\n");

		printf("Case %d: %d\n", tc_index, scarecrow_count);
	}
}

int main12405()
{
	algorithm();
	return 0;
}