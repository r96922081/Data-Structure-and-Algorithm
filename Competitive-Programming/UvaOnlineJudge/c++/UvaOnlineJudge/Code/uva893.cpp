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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static bool IsLeapYear(int y)
{
	if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
		return true;
	else
		return false;
}

static int days_each_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main893()
{
	int days_for_400_years = 365 * 400 + 24 * 3 + 25;
	int days_for_100_years_wo_considering_leap = 365 * 100 + 24;

	while (true)
	{
		int remain_days;
		int day;
		int month;
		int year;

		scanf("%d %d %d %d", &remain_days, &day, &month, &year);
		if (remain_days == 0 && day == 0 && month == 0 && year == 0)
			return 0;

		if (remain_days > days_for_400_years)
		{
			year += 400 * (remain_days / days_for_400_years);
			remain_days %= days_for_400_years;
		}

		while (remain_days > days_for_100_years_wo_considering_leap + 1)
		{
			if (year % 400 > 301 || year % 400 == 0)
			{
				remain_days -= days_for_100_years_wo_considering_leap + 1;
				year += 100;
			}
			else
			{
				remain_days -= days_for_100_years_wo_considering_leap;
				year += 100;
			}
		}

		int days_for_this_month = days_each_month[month];

		if (month == 2 && IsLeapYear(year))
			days_for_this_month = 29;

		if (remain_days <= days_for_this_month - day)
		{
			day += remain_days;
			remain_days = 0;
		}
		else
		{
			if (month == 12)
			{
				month = 1;
				year += 1;
			}
			else
			{
				month += 1;
			}

			remain_days -= (days_for_this_month - day) + 1;
			day = 1;
		}

		while (remain_days > 0)
		{
			int days_for_this_month = days_each_month[month];

			if (month == 2 && IsLeapYear(year))
				days_for_this_month = 29;

			if (remain_days <= days_for_this_month - day)
			{
				day += remain_days;
				remain_days = 0;
			}
			else
			{
				if (month == 12)
				{
					month = 1;
					year += 1;
				}
				else
				{
					month += 1;
				}

				remain_days -= days_for_this_month;
			}
		}

		printf("%d %d %d\n", day, month, year);
	}



	return 0;
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