#include <cstdio>
#include "stdlib.h"
#include "string.h"
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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static bool IsComplete(vector<queue<int>>& station_queues)
{
	for (auto it = station_queues.begin(); it != station_queues.end(); it++)
		if (it->size() != 0)
			return false;

	return true;
}

static int algorithm()
{
	int N;
	scanf("%d", &N);

	for (int Ni = 0; Ni < N; Ni++)
	{
		int stations;
		scanf("%d", &stations);

		int carrier_capacity = 0;
		scanf("%d", &carrier_capacity);

		int queue_capacity = 0;
		scanf("%d", &queue_capacity);

		vector<queue<int>> station_queues;
		station_queues.push_back(queue<int>());

		for (int i = 0; i < stations; i++)
		{
			int count = 0;
			scanf("%d", &count);

			queue<int> q;

			for (int j = 0; j < count; j++)
			{
				int temp = 0;
				scanf("%d", &temp);
				q.push(temp);
			}

			station_queues.push_back(q);
		}

		stack<int> carrier_stack;
		int time = 0;
		int arrived_station = 1;

		while (true)
		{
			while (carrier_stack.size() > 0)
			{
				if (carrier_stack.top() == arrived_station)
				{
					carrier_stack.pop();
					time += 1;
				}
				else if (station_queues[arrived_station].size() < queue_capacity)
				{
					int cargo = carrier_stack.top();
					carrier_stack.pop();
					station_queues[arrived_station].push(cargo);
					time += 1;
				}
				else
				{
					break;
				}
			}

			if (carrier_stack.size() == 0 && IsComplete(station_queues))
				break;

			while (station_queues[arrived_station].size() > 0 && carrier_stack.size() < carrier_capacity)
			{
				int cargo = station_queues[arrived_station].front();
				station_queues[arrived_station].pop();
				time += 1;

				carrier_stack.push(cargo);
			}

			time += 2;
			arrived_station++;
			if (arrived_station == (stations + 1))
				arrived_station = 1;
		}

		cout << time << endl;
	}

	return 0;
}

int main10172()
{	
	//extern void UnitTest();
	//UnitTest();
	return algorithm();
}

static void Check(bool expr)
{
	if (!expr)
	{
		int a = 1;
		int b = 2;
		int c = a / b;
		assert(false);
	}

}

///////////////////// UT //////////////////////

static void UnitTest()
{

}

//////////////////// auxiliary functions /////////////////////

static char to_lower(char c)
{
	if ('a' <= c && c <= 'z')
		return c;
	else
		return c - 'A' + 'a';
}

static string to_lower2(string s)
{
	string ret = "";
	for (int i = 0; i < s.size(); i++)
	{
		ret += to_lower(s[i]);
	}

	return ret;
}