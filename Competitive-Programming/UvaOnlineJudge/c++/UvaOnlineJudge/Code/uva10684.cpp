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

using namespace std;

// y_pos, x_pos, y_width, x_width
long long max_suffix[20][20][20][20];

// z_pos, y_pos, x_pos, y_width, x_width
long long sum[20][20][20][20][20];

long long matrix[20][20][20];
long long max_rectangle;

static void algorithm()
{
	int number_count;

	while (cin >> number_count, number_count != 0)
	{
		int max_sum = 0;
		int max_suffix = 0;

		for (int i = 0; i < number_count; i++)
		{
			int new_number;
			cin >> new_number;

			int new_value = max_suffix + new_number;
			max_sum = max(max_sum, new_value);

			max_suffix += new_number;
			if (max_suffix < 0)
				max_suffix = 0;
		}

		if (max_sum == 0)
			cout << "Losing streak." << endl;
		else
			printf("The maximum winning streak is %d.\n", max_sum);
	}
}

int main10684()
{
	algorithm();
	return 0;
}