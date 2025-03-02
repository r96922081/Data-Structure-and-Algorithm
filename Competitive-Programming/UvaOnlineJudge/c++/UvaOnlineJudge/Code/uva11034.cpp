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
	int N;

	scanf("%d", &N);

	while (N--)
	{
		int ferry_length, m;
		scanf("%d %d", &ferry_length, &m);
		ferry_length *= 100;

		queue<int> waiting_cars_in_left_bank;
		queue<int> waiting_cars_in_right_bank;

		for (int i = 0; i < m; i++)
		{
			int car_len = 0;
			char side[6];
			scanf("%d %s", &car_len, side);
			
			if (strcmp(side, "left") == 0)
				waiting_cars_in_left_bank.push(car_len);
			else
				waiting_cars_in_right_bank.push(car_len);
		}

		string ferry_side = "left";
		int crossing_count = 0;

		while (waiting_cars_in_left_bank.size() != 0 || waiting_cars_in_right_bank.size() != 0)
		{
			int remaining_length = ferry_length;

			if (ferry_side == "left")
			{
				while (waiting_cars_in_left_bank.size() > 0 && waiting_cars_in_left_bank.front() <= remaining_length)
				{
					remaining_length -= waiting_cars_in_left_bank.front();
					waiting_cars_in_left_bank.pop();
				}

				ferry_side = "right";
			}
			else
			{
				while (waiting_cars_in_right_bank.size() > 0 && waiting_cars_in_right_bank.front() <= remaining_length)
				{
					remaining_length -= waiting_cars_in_right_bank.front();
					waiting_cars_in_right_bank.pop();
				}

				ferry_side = "left";
			}

			crossing_count++;
		}

		cout << crossing_count << endl;
	}

	return 0;
}

int main11034()
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