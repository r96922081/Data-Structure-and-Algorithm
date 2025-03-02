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

		map<int, int> inputs;

		int temp;
		int max_occurrence = 1;

		while (count--)
		{
			cin >> temp;
			map<int, int>::iterator it = inputs.find(temp);
			if (it != inputs.end())
			{
				it->second++;
				max_occurrence = max(max_occurrence, it->second);
			}
			else
			{
				inputs.insert(pair<int, int>(temp, 1));
			}

		}

		vector<vector<int>> min_heap(max_occurrence, vector<int>());

		for (auto it = inputs.begin(); it != inputs.end(); it++)
		{
			int number = it->first;
			int occurrence = it->second;

			for (int i = occurrence - 1; i >= 0; i--)
			{
				vector<int> target = min_heap[i];
				target.push_back(number);
				int j = i;
				for (; j < min_heap.size() - 1; j++)
				{
					vector<int>& be_compared_target = min_heap[j + 1];
					if (target.size() <= be_compared_target.size())
						break;

					min_heap[i] = be_compared_target;
				}

				min_heap[j] = target;
			}
		}

		cout << max_occurrence << endl;
		for (auto it = min_heap.begin(); it != min_heap.end(); it++)
		{
			vector<int>& target = *it;
			int i = 0;
			cout << target[i];
			i++;

			for (; i < target.size(); i++)
				cout << " " << target[i];

			cout << endl;
		}
	}
}

int main11100()
{
	algorithm();
	return 0;
}