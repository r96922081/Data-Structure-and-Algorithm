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
	int test_case_count = 0;
	cin >> test_case_count;

	while (test_case_count--)
	{
		int A, B, C;
		cin >> A >> B >> C;

		bool found_solution = false;

		for (int X = -60; !found_solution; X++)
		{
			if (3 * X > A || X * X * X > B)
				break;

			for (int Y = X + 1; !found_solution; Y++)
			{
				if (X + 2 * Y > A || X * Y * Y > B)
					break;

				int Z = A - X - Y;
				if (Z <= Y)
					continue;

				if (X * Y * Z == B && X * X + Y * Y + Z * Z == C)
				{
					found_solution = true;
					cout << X << " " << Y << " " << Z << endl;
					break;
				}
			}
		}

		if (!found_solution)
			cout << "No solution." << endl;
	}
}

int main11565()
{
	algorithm();
	return 0;
}