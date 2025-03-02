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
	int dragon_count, knight_count;

	while (cin >> dragon_count >> knight_count, dragon_count != 0)
	{
		priority_queue<int, vector<int>, greater<int>> dragons;
		priority_queue<int, vector<int>, greater<int>> knights;

		int temp;
		for (int i = 0; i < dragon_count; i++)
			cin >> temp, dragons.push(temp);

		for (int i = 0; i < knight_count; i++)
			cin >> temp, knights.push(temp);

		int money = 0;

		bool doomed = false;
		while (!dragons.empty())
		{
			int dragon_height = dragons.top();

			while (true)
			{
				if (knights.empty())
				{
					doomed = true;
					break;
				}

				int knight_height = knights.top();
				knights.pop();
				if (knight_height >= dragon_height)
				{
					money += knight_height;
					break;
				}
			}

			dragons.pop();
		}

		if (doomed)
			cout << "Loowater is doomed!" << endl;
		else
			cout << money << endl;
	}
}

int main11292()
{
	algorithm();
	return 0;
}