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

int count_remainder_2d_array[201][20];

static void algorithm()
{
	int number_count;
	int query_count;

	for (int test_case = 1; cin >> number_count >> query_count, number_count != 0; test_case++)
	{
		printf("SET %d:\n", test_case);
		vector<long long> numbers;

		for (int i = 0; i < number_count; i++)
		{
			long long temp;
			cin >> temp;
			numbers.push_back(temp);
		}

		for (int query_index = 0; query_index < query_count; query_index++)
		{
			memset(count_remainder_2d_array, 0, sizeof(int) * 201 * 20);
			count_remainder_2d_array[0][0] = 1;

			int divisor = 0;
			int select_count = 0;

			cin >> divisor >> select_count;

			for (int i = 0; i < number_count; i++)
			{
				long long number = numbers[i];

				for (int count = i; count >= 0; count--)
				{
					for (int prev_remainder = 0; prev_remainder < divisor; prev_remainder++)
					{
						int next_remainder = (prev_remainder + number) % divisor;

						if (next_remainder < 0)
							next_remainder += divisor;

						if (count_remainder_2d_array[count][prev_remainder] != 0)
						{
							count_remainder_2d_array[count + 1][next_remainder] += count_remainder_2d_array[count][prev_remainder];
						}
					}
				}
			}

			printf("QUERY %d: %d\n", query_index + 1, count_remainder_2d_array[select_count][0]);
		}
	}
}

int main10616()
{
	algorithm();
	return 0;
}