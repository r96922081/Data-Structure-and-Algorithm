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

static int algorithm()
{
	int operation_count;

	while (scanf("%d", &operation_count) == 1)
	{
		stack<unsigned char> simulating_stack;
		queue<unsigned char> simulating_queue;
		priority_queue<unsigned char> simulating_priority_queue;

		int operation_type = 0;
		unsigned char element = 0;

		set<int> candidate_data_struct { 0, 1, 2 };

		for (int i = 0; i < operation_count; i++)
		{
			scanf("%d%*[ ]%hhu", &operation_type, &element);
			if (candidate_data_struct.size() == 0)
				continue;

			for (auto it = candidate_data_struct.begin(); it != candidate_data_struct.end();)
			{
				if (operation_type == 1)
				{
					if (*it == 0)
						simulating_stack.push(element);
					else if (*it == 1)
						simulating_queue.push(element);
					else
						simulating_priority_queue.push(element);
				}
				else
				{
					if (*it == 0)
					{
						if (simulating_stack.size() == 0)
						{
							it = candidate_data_struct.erase(it);
							continue;
						}

						int top_element = simulating_stack.top();
						if (top_element != element)
						{
							it = candidate_data_struct.erase(it);
							continue;
						}
						simulating_stack.pop();
					}
					else if (*it == 1)
					{
						if (simulating_queue.size() == 0)
						{
							it = candidate_data_struct.erase(it);
							continue;
						}

						int top_element = simulating_queue.front();
						if (top_element != element)
						{
							it = candidate_data_struct.erase(it);
							continue;
						}
						simulating_queue.pop();
					}
					else
					{
						if (simulating_priority_queue.size() == 0)
						{
							it = candidate_data_struct.erase(it);
							continue;
						}

						int top_element = simulating_priority_queue.top();
						if (top_element != element)
						{
							it = candidate_data_struct.erase(it);
							continue;
						}
						simulating_priority_queue.pop();
					}
				}

				it++;
			}
		}

		if (candidate_data_struct.size() == 0)
			cout << "impossible" << endl;
		else if (candidate_data_struct.size() > 1)
			cout << "not sure" << endl;
		else if (*candidate_data_struct.begin() == 0)
			cout << "stack" << endl;
		else if (*candidate_data_struct.begin() == 1)
			cout << "queue" << endl;
		else
			cout << "priority queue" << endl;
	}

	return 0;
}

int main11995()
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