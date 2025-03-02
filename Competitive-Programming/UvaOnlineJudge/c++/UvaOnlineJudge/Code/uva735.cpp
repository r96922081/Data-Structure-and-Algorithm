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
	set<int> score;
	for (int i = 0; i <= 20; i++)
		for (int j = 1; j <= 3; j++)
			score.insert(i * j);

	score.insert(50);

	int target_score;
	bool first = true;
	while (true)
	{
		if (first)
			first = false;
		else
			cout << "**********************************************************************" << endl;

		cin >> target_score;
		if (target_score <= 0)
		{
			cout << "END OF OUTPUT" << endl;
			break;
		}

		set<int> combinations;
		int permutation_count = 0;

		for (auto i = score.begin(); i != score.end(); i++)
			for (auto j = score.begin(); j != score.end(); j++)
			{
				int c = target_score - *i - *j;
				if (score.find(c) == score.end())
					continue;

				int a = *i;
				int b = *j;

				int temp;
				if (a > b) temp = a, a = b, b = temp;
				if (b > c) temp = b, b = c, c = temp;
				if (a > b) temp = a, a = b, b = temp;

				int combination = (a << 12) + (b << 6) + c;
				if (combinations.find(combination) != combinations.end())
					continue;

				combinations.insert(combination);

				if (a == b && b == c)
					permutation_count += 1;
				else if (a != b && b != c && a != c)
					permutation_count += 6;
				else
					permutation_count += 3;
			}

		if (combinations.size() == 0)
			cout << "THE SCORE OF " << target_score << " CANNOT BE MADE WITH THREE DARTS." << endl;
		else
		{
			printf("NUMBER OF COMBINATIONS THAT SCORES %d IS %d.\n", target_score, combinations.size());
			printf("NUMBER OF PERMUTATIONS THAT SCORES %d IS %d.\n", target_score, permutation_count);
		}
	}
}

int main735()
{
	algorithm();
	return 0;
}