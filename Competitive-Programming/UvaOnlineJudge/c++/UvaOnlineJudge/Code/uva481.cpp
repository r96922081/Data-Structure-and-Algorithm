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

using namespace std;

// best increasing sequence
vector<vector<int>> bit_vector;

static void algorithm()
{
	int value;
	
	cin >> value;
	vector<int> v;
	v.push_back(value);
	bit_vector.push_back(v);

	while (cin >> value)
	{
		bool used = false;

		int left = 0;
		int right = bit_vector.size() - 1;
		bool found = false;

		while (left <= right)
		{
			int mid = (left + right) / 2;
			vector<int>& bis = bit_vector[mid];
			if (value > bis.back())
			{
				if (mid == right)
				{
					found = true;
					break;
				}
				else
				{
					if (bit_vector[mid + 1].back() > value)
					{
						found = true;
						left = mid;
						break;
					}
					else
					{
						left = mid + 1;
					}
				}
			}
			else
			{
				right = mid - 1;
			}
		}

		if (!found)
			bit_vector.front()[0] = value;
		else
		{
			vector<int> bis2 = bit_vector[left];
			bis2.push_back(value);

			if (left == (bit_vector.size() - 1))
			{
				bit_vector.push_back(bis2);
			}
			else
			{
				bit_vector[left + 1] = bis2;
			}
		}
	}

	vector<int>& answer = bit_vector.back();
	cout << answer.size() << endl;
	cout << "-" << endl;

	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << endl;
}

int main481()
{
	algorithm();
	return 0;
}