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

vector<vector<int>> window1;
bool window2[5][26];
int k = 0;
int current_selection = -1;
const int max_selection = 6 * 6 * 6 * 6 * 6 - 1;
int selection[5];
set<int> past_selection;

static bool get_next_selection()
{
	current_selection++;

	if (current_selection == max_selection)
		return false;

	int temp_selection = current_selection;
	
	for (int i = 0; i < 5; i++)
	{
		selection[4 - i] = window1[4 - i][temp_selection % 6];
		temp_selection /= 6;
	}

	return true;
}

static bool algorithm2()
{
	int current_k = 0;
	while (true)
	{
		if (get_next_selection() == false)
			return false;

		if (window2[4][selection[4]] && window2[3][selection[3]] &&
			window2[2][selection[2]] && window2[1][selection[1]] &&
			window2[0][selection[0]])
		{
			int current_selection = selection[4] * 26 * 26 * 26 * 26 +
									selection[3] * 26 * 26 * 26 +
									selection[2] * 26 * 26 +
									selection[1] * 26 +
									selection[0];

			if (past_selection.find(current_selection) != past_selection.end())
				continue;

			past_selection.insert(current_selection);

			current_k++;

			if (current_k == k)
			{
				printf("%c%c%c%c%c\n", selection[0] + 'A', selection[1] + 'A', selection[2] + 'A', selection[3] + 'A', selection[4] + 'A');
				return true;
			}
		}
	}
}

static void algorithm()
{
	int test_case_count;
	cin >> test_case_count;

	while (test_case_count--)
	{
		cin >> k;
		scanf("\n");
		string line;
		window1.clear();

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 26; j++)
				window2[i][j] = false;

		for (int i = 0; i < 6; i++)
		{
			getline(cin, line);
			for (int j = 0; j < 5; j++)
			{
				if (i == 0)
				{
					vector<int> temp;
					window1.push_back(temp);
				}

				window1[j].push_back(line[j] - 'A');
			}
		}

		for (int i = 0; i < 5; i++)
			sort(window1[i].begin(), window1[i].end());

		for (int i = 0; i < 6; i++)
		{
			getline(cin, line);
			for (int j = 0; j < 5; j++)
				window2[j][line[j] - 'A'] = true;
		}

		current_selection = -1;
		past_selection.clear();

		if (algorithm2() == false)
			cout << "NO" << endl;
	}
}

int main1262()
{
	algorithm();
	return 0;
}