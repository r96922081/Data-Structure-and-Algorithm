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

static void algorithm()
{
	int test_count;
	cin >> test_count;

	for (int test_index = 1; test_index <= test_count; test_index++)
	{
		int building_count;
		cin >> building_count;

		vector<int> height_vector;
		vector<int> width_vector;
		vector<int> lis_vector;
		vector<int> lds_vector;

		int max_lis = 0;
		int max_lds = 0;

		for (int i = 0; i < building_count; i++)
		{
			int height;
			cin >> height;
			height_vector.push_back(height);
		}

		for (int i = 0; i < building_count; i++)
		{
			int width;
			cin >> width;
			width_vector.push_back(width);
		}

		for (int i = 0; i < building_count; i++)
		{
			int width = width_vector[i];
			int height = height_vector[i];
			int lis = width;
			int lds = width;

			for (int j = i - 1; j >= 0; j--)
			{
				if (height_vector[j] < height)
					lis = max(lis, lis_vector[j] + width);
				else if (height < height_vector[j])
					lds = max(lds, lds_vector[j] + width);
			}

			lis_vector.push_back(lis);
			lds_vector.push_back(lds);

			max_lis = max(max_lis, lis);
			max_lds = max(max_lds, lds);
		}

		if (max_lis >= max_lds)
			printf("Case %d. Increasing (%d). Decreasing (%d).\n", test_index, max_lis, max_lds);
		else
			printf("Case %d. Decreasing (%d). Increasing (%d).\n", test_index, max_lds, max_lis);
	}
}

int main11790()
{
	algorithm();

	return 0;
}