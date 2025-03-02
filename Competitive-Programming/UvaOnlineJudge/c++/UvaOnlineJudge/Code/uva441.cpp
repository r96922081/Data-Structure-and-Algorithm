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
	bool first = true;

	while (cin >> count, count != 0)
	{
		if (!first)
			cout << endl;

		first = false;

		int temp;
		vector<int> S;

		for (int i = 0; i < count; i++)
			cin >> temp, S.push_back(temp);

		sort(S.begin(), S.end());
		int s[6];
		int size = S.size();

		for (int i = 0; i < size - 5; i++)
		{
			s[0] = S[i];
			for (int j = i + 1; j < size - 4; j++)
			{
				s[1] = S[j];
				for (int k = j + 1; k < size - 3; k++)
				{
					s[2] = S[k];
					for (int l = k + 1; l < size - 2; l++)
					{
						s[3] = S[l];
						for (int m = l + 1; m < size - 1; m++)
						{
							s[4] = S[m];
							for (int n = m + 1; n < size; n++)
							{
								s[5] = S[n];
								for (int o = 0; o < 6; o++)
								{
									if (o > 0)
										cout << " ";
									cout << s[o];
								}
								cout << endl;
							}
						}
					}
				}
			}
		}
	}
}

int main441()
{
	algorithm();
	return 0;
}