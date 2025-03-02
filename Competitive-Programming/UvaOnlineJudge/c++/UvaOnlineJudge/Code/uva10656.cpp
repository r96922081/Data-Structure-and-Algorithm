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
	int count;
	while (cin >> count, count != 0)
	{
		int zero_count = 0;

		bool non_zero_appear = false;

		int n;

		bool first_output = true;

		for (int i = 0; i < count; i++)
		{
			cin >> n;

			if (n != 0)
			{
				if (first_output)
					first_output = false;
				else
					cout << " ";

				cout << n;
			}
		}

		if (first_output)
			cout << "0";

		cout << endl;
	}
}

int main10656()
{
	algorithm();
	return 0;
}