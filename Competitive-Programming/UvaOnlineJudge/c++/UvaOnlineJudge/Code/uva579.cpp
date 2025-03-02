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


int main579()
{
	int hr = 0;
	int minute = 0;

	while (true)
	{
		scanf("%d:%2d", &hr, &minute);

		if (hr == 0 && minute == 0)
			return 0;

		hr %= 12;

		double hr_angle = (360.0 * hr / 12) + (30.0 * minute / 60);
		double minute_angle = 360.0 * minute / 60;

		double diff = hr_angle > minute_angle ? hr_angle - minute_angle : minute_angle - hr_angle;
		if (diff > 180)
			diff = 360 - diff;

		diff *= 1000;
		diff = (double)round(diff);
		diff /= 1000;
		printf("%.3lf\n", diff);
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