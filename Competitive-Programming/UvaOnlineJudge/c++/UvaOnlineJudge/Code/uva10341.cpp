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

static int get_dest_count(vector<int>& source_sizes, int dest_size)
{
	int dest_count = 1;

	int remain_size = dest_size;

	for (int i = 0; i < source_sizes.size(); i++)
	{
		int size = source_sizes[i];
		if (size <= remain_size)
			remain_size -= size;
		else
		{
			dest_count++;
			remain_size = dest_size - size;
		}
	}

	return dest_count;
}

static void algorithm()
{
	int source_count;
	int target_dest_count;

	while (scanf("%d %d", &source_count, &target_dest_count) == 2)
	{
		int max_source = 0;
		vector<int> source_sizes;
		for (int i = 0; i < source_count; i++)
		{
			int temp;
			cin >> temp;
			source_sizes.push_back(temp);
			max_source = max(max_source, temp);
		}

		if (source_count <= target_dest_count)
		{
			cout << max_source << endl;
			continue;
		}

		int left = max_source;
		int right = 1000000000;
		int min_dest_size = right;

		while (left <= right)
		{
			int mid = (left + right) / 2;
			int dest_count = get_dest_count(source_sizes, mid);

			if (dest_count == target_dest_count)
			{
				min_dest_size = min(min_dest_size, mid);
				right = mid - 1;
			}
			else if (dest_count > target_dest_count)
				left = mid + 1;
			else
				right = mid - 1;
		}

		cout << min_dest_size << endl;
	}
}

int main10341()
{
	algorithm();
	return 0;
}