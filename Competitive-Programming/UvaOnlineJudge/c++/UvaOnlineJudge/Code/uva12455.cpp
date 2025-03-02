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
	int test_case_count;
	cin >> test_case_count;

	while (test_case_count--)
	{
		int target_sum;
		cin >> target_sum;

		int n;
		cin >> n;

		vector<int> all_int;
		int temp;
		for (int i = 0; i < n; i++)
			cin >> temp, all_int.push_back(temp);

		int max = pow(2, n) - 1;

		bool found = false;

		for (int i = 0; i <= max; i++)
		{
			int temp_sum = 0;
			for (int j = 0; j < n; j++)
				if ((i >> j) % 2 == 1)
					temp_sum += all_int[j];

			if (temp_sum == target_sum)
			{
				found = true;
				break;
			}
		}

		if (found)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}

int main12455()
{
	algorithm();
	return 0;
}