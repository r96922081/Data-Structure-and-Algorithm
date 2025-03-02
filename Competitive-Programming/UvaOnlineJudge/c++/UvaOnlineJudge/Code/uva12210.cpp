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
	for (int test_index = 1;; test_index++)
	{
		int male_count, female_count;
		cin >> male_count >> female_count;

		if (male_count == 0)
			break;

		int temp;
		int min_male = numeric_limits<int>::max();

		for (int i = 0; i < male_count; i++)
			cin >> temp, min_male = min(min_male, temp);

		for (int i = 0; i < female_count; i++)
			cin >> temp;
		
		if (female_count >= male_count)
			printf("Case %d: 0\n", test_index);
		else
			printf("Case %d: %d %d\n", test_index, male_count - female_count, min_male);
	}
}

int main12210()
{
	algorithm();
	return 0;
}