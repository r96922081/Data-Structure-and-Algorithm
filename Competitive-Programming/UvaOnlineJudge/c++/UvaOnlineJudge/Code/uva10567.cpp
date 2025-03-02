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

vector<int> indexes[52];
int next_index = 0;
int start_index = 0;
int end_index = 0;

static int char_to_int(char c)
{
	if ('a' <= c && c <= 'z')
		return c - 'a';
	else
		return c - 'A' + 26;
}

static void algorithm()
{
	char c;
	int index = 0;

	while (scanf("%c", &c), c != '\n')
	{
		indexes[char_to_int(c)].push_back(index++);
	}

	int query_count;
	cin >> query_count;
	scanf("\n");

	while (query_count--)
	{
		int next_index = 0;
		bool first = true;
		bool matched = true;

		while (scanf("%c", &c), c != '\n')
		{
			int number = char_to_int(c);
			if (first)
			{
				first = false;
				if (indexes[number].size() == 0)
				{
					matched = false;
					break;
				}

				start_index = indexes[number][0];
				end_index = start_index;
				next_index = end_index + 1;
			}
			else
			{
				vector<int>& positions = indexes[number];
				int left = 0;
				int right = positions.size() - 1;
				int matched_index = -1;

				while (left <= right)
				{
					int mid = (left + right) / 2;
					int mid_value = positions[mid];

					if (next_index <= mid_value && (mid == 0 || positions[mid - 1] < next_index))
					{
						matched_index = mid_value;
						break;
					}

					if (mid_value < next_index)
						left = mid + 1;
					else
						right = mid - 1;
				}

				if (matched_index == -1)
				{
					matched = false;
					break;
				}
				else
				{
					end_index = matched_index;
					next_index = end_index + 1;
				}
			}
		}

		if (!matched)
		{
			cout << "Not matched" << endl;
			string line;
			getline(cin, line);
		}
		else
			cout << "Matched " << start_index << " " << end_index << endl;
	}
}

int main10567()
{
	algorithm();
	return 0;
}