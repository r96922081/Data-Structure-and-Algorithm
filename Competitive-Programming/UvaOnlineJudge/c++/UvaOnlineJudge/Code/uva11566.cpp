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

const int max_favor_size = 1102;

// pair = count, favor
list<pair<int, int>> max_favor[max_favor_size];

static void algorithm()
{
	int N, x, T, K;

	while (scanf("%d%d%d%d", &N, &x, &T, &K))
	{
		if (N == 0 && x == 0 && T == 0 && K == 0)
			break;

		int total_money = (N + 1) * x;
		for (int i = 0; i < max_favor_size; i++)
		{
			max_favor[i].clear();
		}

		for (int i = 0; i < K; i++)
		{
			int price;
			cin >> price;

			int favor = 0;
			for (int j = 0; j <= N; j++)
			{
				int temp;
				cin >> temp;
				favor += temp;
			}

			for (int k = 0; k < 2; k++)
			{
				for (int l = total_money - (T * (N + 1)) - price; l >= 0; l--)
				{
					if (l == 0)
					{
						pair<int, int> this_pair(1, favor);

						if (((l + (T * (N + 1)) + price) * 11) <= total_money * 10)
						{
							auto m = max_favor[l + price].begin();
							bool add = true;
							while (m != max_favor[l + price].end())
							{
								if (this_pair.second < m->second && this_pair.first >= m->first)
								{
									add = false;
									break;
								}
								else if (this_pair.second >= m->second && this_pair.first <= m->first)
								{
									m = max_favor[l + price].erase(m);
								}
								else
								{
									m++;
								}
							}

							if (add)
							{
								max_favor[l + price].push_back(this_pair);
							}
						}
					}
					else if (max_favor[l].size() != 0)
					{
						for (auto it = max_favor[l].begin(); it != max_favor[l].end(); it++)
						{
							pair<int, int> this_pair(it->first + 1, it->second + favor);
							if (this_pair.first > (N + 1) * 2)
								continue;

							if (((l + (T * (N + 1)) + price) * 11) <= total_money * 10)
							{
								auto m = max_favor[l + price].begin();
								bool add = true;
								while (m != max_favor[l + price].end())
								{
									if (this_pair.second < m->second && this_pair.first >= m->first)
									{
										add = false;
										break;
									}
									else if (this_pair.second >= m->second && this_pair.first <= m->first)
									{
										m = max_favor[l + price].erase(m);
									}
									else
									{
										m++;
									}
								}

								if (add)
								{
									max_favor[l + price].push_back(this_pair);
								}
							}
						}
					}
				}
			}

		}

		int answer = 0;

		for (int i = 0; i <= total_money; i++)
		{
			for (auto it = max_favor[i].begin(); it != max_favor[i].end(); it++)
			{
				if (it->second > answer)
					answer = it->second;
			}
		}

		printf("%.2lf\n", ((double)answer) / (double)(N + 1));
	}
}

int main11566()
{
	algorithm();

	return 0;
}