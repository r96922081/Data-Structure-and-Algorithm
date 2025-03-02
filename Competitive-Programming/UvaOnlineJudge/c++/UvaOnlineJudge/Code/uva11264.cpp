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
	int test_case = 0;
	cin >> test_case;
	while (test_case--)
	{
		int n;
		cin >> n;
		vector<unsigned long long> v;
		unsigned long long temp;


		while (n--)
		{
			cin >> temp;
			v.push_back(temp);
		}

		if (v.size() == 1)
		{
			cout << 1 << endl;
			continue;
		}

		unsigned long long sum = v[0];
		int answer = 2;

		for (int i = 1; i < v.size() - 1; i++)
		{
			unsigned long long next_sum = sum + v[i];
			if (next_sum < v[i + 1])
			{
				answer++;
				sum = next_sum;
			}
		}

		cout << answer << endl;
	}
}

int main11264()
{
	algorithm();
	return 0;
}