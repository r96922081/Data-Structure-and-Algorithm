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


static struct Car
{
	int index;
	int unloaded_time;
	int arrived_time;
};

static struct InputCar
{
	int index;
	string side;
	int arrived_time;
};

static void UpdateWaitingCars(queue<InputCar>& input_cars, int current_time, queue<Car>& waiting_cars_in_left_bank, queue<Car>& waiting_cars_in_right_bank)
{
	while (!input_cars.empty() && input_cars.front().arrived_time <= current_time)
	{
		InputCar c = input_cars.front();
		input_cars.pop();
		Car c2;
		c2.index = c.index;
		c2.arrived_time = c.arrived_time;
		if (c.side == "left")
			waiting_cars_in_left_bank.push(c2);
		else
			waiting_cars_in_right_bank.push(c2);
	}
}

static void LoadCars(string ferry_side, vector<Car>& cars_in_ferry, int ferry_capacity, queue<Car>& waiting_cars_in_left_bank, queue<Car>& waiting_cars_in_right_bank)
{
	if (ferry_side == "left")
	{
		while (waiting_cars_in_left_bank.size() != 0 && cars_in_ferry.size() < ferry_capacity)
		{
			cars_in_ferry.push_back(waiting_cars_in_left_bank.front());
			waiting_cars_in_left_bank.pop();
		}
	}
	else
	{
		while (waiting_cars_in_right_bank.size() != 0 && cars_in_ferry.size() < ferry_capacity)
		{
			cars_in_ferry.push_back(waiting_cars_in_right_bank.front());
			waiting_cars_in_right_bank.pop();
		}
	}
}

static void Unload(vector<Car>& cars_in_ferry, int current_time, vector<Car>& result)
{
	for (auto it = cars_in_ferry.begin(); it != cars_in_ferry.end();)
	{
		Car c = *it;
		c.unloaded_time = current_time;
		result.push_back(c);
		it = cars_in_ferry.erase(it);
	}
}

static void CrossRiver(string& ferry_side, int& current_time, int time_to_cross_river)
{
	if (ferry_side == "left")
		ferry_side = "right";
	else
		ferry_side = "left";

	current_time += time_to_cross_river;
}

static int algorithm()
{
	int N;

	scanf("%d", &N);

	while (N--)
	{
		int ferry_capacity, time_to_cross_river, m;
		scanf("%d %d %d", &ferry_capacity, &time_to_cross_river, &m);

		queue<Car> waiting_cars_in_left_bank;
		queue<Car> waiting_cars_in_right_bank;
		vector<Car> cars_in_ferry;
		vector<Car> result;

		queue<InputCar> input_cars;
		for (int i = 0; i < m; i++)
		{
			InputCar c;
			c.index = i;
			char side[6];
			scanf("%d %s", &c.arrived_time, side);
			c.side = side;

			input_cars.push(c);
		}

		string ferry_side = "left";
		int current_time = 0;

		while (true)
		{
			Unload(cars_in_ferry, current_time, result);

			UpdateWaitingCars(input_cars, current_time, waiting_cars_in_left_bank, waiting_cars_in_right_bank);

			LoadCars(ferry_side, cars_in_ferry, ferry_capacity, waiting_cars_in_left_bank, waiting_cars_in_right_bank);

			if (cars_in_ferry.size() == 0)
			{
				if (input_cars.size() == 0 && waiting_cars_in_left_bank.size() == 0 && waiting_cars_in_right_bank.size() == 0)
				{
					break;
				}
				else
				{
					if (waiting_cars_in_left_bank.size() != 0 || waiting_cars_in_right_bank.size() != 0)
					{
						LoadCars(ferry_side, cars_in_ferry, ferry_capacity, waiting_cars_in_left_bank, waiting_cars_in_right_bank);
					}
					else
					{
						current_time = input_cars.front().arrived_time;
					}

					UpdateWaitingCars(input_cars, current_time, waiting_cars_in_left_bank, waiting_cars_in_right_bank);
					LoadCars(ferry_side, cars_in_ferry, ferry_capacity, waiting_cars_in_left_bank, waiting_cars_in_right_bank);
				}
			}

			CrossRiver(ferry_side, current_time, time_to_cross_river);
		}

		sort(result.begin(), result.end(), [](const Car& a, const Car& b) 
			{
				if (a.index < b.index)
					return true;
				else
					return false;
			}
		);

		for (auto it = result.begin(); it != result.end(); it++)
		{
			cout << it->unloaded_time << endl;
		}

		if (N != 0)
			cout << endl;
	}

	return 0;
}

int main10901()
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