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

int days_each_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main11947()
{

	int T;
	scanf("%d", &T);

	for (int ti = 1; ti <= T; ti++)
	{
		int day;
		int month;
		int year;

		scanf("%2d%2d%4d", &month, &day, &year);

		int days_for_this_month = days_each_month[month];

		if (month == 2 && IsLeapYear(year))
			days_for_this_month = 29;

		for (int i = 0; i < 40; i++)
		{
			if (day + 7 <= days_for_this_month)
			{
				day += 7;
			}
			else
			{
				day = 7 - (days_for_this_month - day);
				month += 1;
				if (month == 13)
				{
					month = 1;
					year += 1;
				}

				days_for_this_month = days_each_month[month];

				if (month == 2 && IsLeapYear(year))
					days_for_this_month = 29;
			}
		}

		string zodiac_sign = "";


		printf("%d %02d/%02d/%04d ", ti, month, day, year);

		int mm = month;
		int dd = day;

		if ((mm == 1 && dd >= 21) || (mm == 2 && dd <= 19))
			puts("aquarius");
		else if ((mm == 2 && dd >= 20) || (mm == 3 && dd <= 20))
			puts("pisces");
		else if ((mm == 3 && dd >= 21) || (mm == 4 && dd <= 20))
			puts("aries");
		else if ((mm == 4 && dd >= 21) || (mm == 5 && dd <= 21))
			puts("taurus");
		else if ((mm == 5 && dd >= 22) || (mm == 6 && dd <= 21))
			puts("gemini");
		else if ((mm == 6 && dd >= 22) || (mm == 7 && dd <= 22))
			puts("cancer");
		else if ((mm == 7 && dd >= 23) || (mm == 8 && dd <= 21))
			puts("leo");
		else if ((mm == 8 && dd >= 22) || (mm == 9 && dd <= 23))
			puts("virgo");
		else if ((mm == 9 && dd >= 23) || (mm == 10 && dd <= 23))
			puts("libra");
		else if ((mm == 10 && dd >= 24) || (mm == 11 && dd <= 22))
			puts("scorpio");
		else if ((mm == 11 && dd >= 23) || (mm == 12 && dd <= 22))
			puts("sagittarius");
		else
			puts("capricorn");
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