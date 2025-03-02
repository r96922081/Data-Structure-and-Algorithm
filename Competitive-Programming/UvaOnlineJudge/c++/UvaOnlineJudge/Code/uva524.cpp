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

static set<int> primes;

static set<int> unused;

static int answer[16];

static int test_case = 1;

static void find_primes(int max)
{
	primes.clear();

	vector<bool> candidate(max + 1, true);

	for (int i = 2; i <= max; i++)
	{
		if (candidate[i] == false)
			continue;

		primes.insert(i);

		for (int j = i; j <= max; j += i)
			candidate[j] = false;
	}
}

static void find_answer(int index, int max)
{
	int size = unused.size();

	if (size == 0)
	{
		if (primes.find(answer[index - 1] + 1) != primes.end())
		{
			cout << "1";
			for (int i = 1; i < index; i++)
				cout << " " << answer[i];

			cout << endl;
		}

		return;
	}

	int* unused2 = new int[size];

	int i = 0;
	for (set<int>::iterator it = unused.begin(); it != unused.end(); it++, i++)
		unused2[i] = *it;

	for (int i = 0; i < size; i++)
	{
		int number = unused2[i];

		if (primes.find(number + answer[index - 1]) == primes.end())
			continue;

		answer[index] = number;

		unused.erase(number);
		find_answer(index + 1, max);
		unused.insert(number);
	}


	delete[] unused2;
}

static void algorithm()
{
	answer[0] = 1;

	for (;;)
	{
		int n;
		if (scanf("%d", &n) != 1)
			return;

		if (test_case != 1)
			cout << endl;

		printf("Case %d:\n", test_case);
		find_primes(n * 2 - 1);

		unused.clear();
		for (int i = 2; i <= n; i++)
			unused.insert(i);

		find_answer(1, n);

		test_case++;
	}
}

int main524()
{
	algorithm();
	return 0;
}