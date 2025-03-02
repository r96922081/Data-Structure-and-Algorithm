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
#include <functional>

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static struct task
{
	int id;
	int period;
	int next_time_to_execute;
};

class CompareFunction
{
public:
	bool operator() (const task& A, const task& B)
	{
		bool ret = false;

		if (A.next_time_to_execute < B.next_time_to_execute)
			ret = true;
		else if ((A.next_time_to_execute == B.next_time_to_execute) && A.id < B.id)
			ret = true;
		else
			ret = false;

		return !ret;
	}
};

static int algorithm()
{
	priority_queue<task, vector<task>, CompareFunction> task_heap;

	string line = "";
	while (getline(cin, line), line != "#")
	{
		stringstream ss;
		ss << line;

		int id = 0;
		int period = 0;
		sscanf(line.c_str(), "Register%*[ \n]%d%*[ \n]%d%*[ \n]", &id, &period);

		task t;
		t.id = id;
		t.period = period;
		t.next_time_to_execute = period;

		task_heap.push(t);
	}

	int output_count = 0;
	scanf("%d", &output_count);

	for (int i = 0; i < output_count; i++)
	{
		task task_a = task_heap.top();
		task_heap.pop();
		cout << task_a.id << endl;
		task_a.next_time_to_execute += task_a.period;
		task_heap.push(task_a);
	}

	return 0;
}

int main1203()
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