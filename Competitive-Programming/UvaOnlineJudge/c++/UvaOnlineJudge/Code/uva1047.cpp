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

int max_count = -1;
int answer[20];

static void algorithm2(int built_index, int built_count, int* selection, vector<int>& tower, vector<vector<int>>& tower_to_overlapping, vector<int>& overlapped_area)
{
	if (built_index == built_count)
	{
		vector<int> overlapped_area_copy = overlapped_area;
		int served_count = 0;

		for (int i = 0; i < built_count; i++)
		{
			int selection_index = selection[i];
			served_count += tower[selection_index];

			for (int j = 0; j < tower_to_overlapping[selection_index].size(); j++)
			{
				served_count += overlapped_area_copy[tower_to_overlapping[selection_index][j]];
				overlapped_area_copy[tower_to_overlapping[selection_index][j]] = 0;
			}
		}

		if (served_count > max_count)
		{
			max_count = served_count;

			for (int j = 0; j < built_count; j++)
				answer[j] = selection[j];
		}
		return;
	}

	int last_tower = tower.size() - 1;
	int i = 1;
	if (built_index > 0)
		i = selection[built_index - 1] + 1;
	for (; i <= last_tower - (built_count - built_index) + 1; i++)
	{
		selection[built_index] = i;
		algorithm2(built_index + 1, built_count, selection, tower, tower_to_overlapping, overlapped_area);
	}
}

static void algorithm()
{
	int tower_count;
	int built_count;
	int test_index = 1;

	while (cin >> tower_count >> built_count, tower_count != 0)
	{
		max_count = -1;

		printf("Case Number  %d\n", test_index++);

		int temp;
		vector<int> tower;
		tower.push_back(-1);

		for (int i = 0; i < tower_count; i++)
		{
			cin >> temp;
			tower.push_back(temp);
		}

		int overlapped_area_count;
		cin >> overlapped_area_count;

		vector<int> overlapped_area;
		vector<vector<int>> tower_to_overlapping(tower_count + 1, vector<int>());

		for (int i = 0; i < overlapped_area_count; i++)
		{
			int overlapped_tower_count;
			cin >> overlapped_tower_count;
			vector<int> overlapped_tower;
			
			for (int j = 0; j < overlapped_tower_count; j++)
			{
				cin >> temp;
				tower_to_overlapping[temp].push_back(i);
				overlapped_tower.push_back(temp);
			}

			int customer_count;
			cin >> customer_count;
			overlapped_area.push_back(customer_count);

			for (int j = 0; j < overlapped_tower.size(); j++)
			{
				tower[overlapped_tower[j]] -= customer_count;
			}
		}

		int* selection = new int[built_count];
		algorithm2(0, built_count, selection, tower, tower_to_overlapping, overlapped_area);
		delete[] selection;

		printf("Number of Customers: %d\n", max_count);
		cout << "Locations recommended:";

		for (int i = 0; i < built_count; i++)
			cout << " " << answer[i];

		cout << endl;
		cout << endl;
	}
}

int main1047()
{
	algorithm();
	return 0;
}