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

static int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

int main12060()
{
	for (int ti = 1; ; ti++)
	{
		string line = "";
		getline(cin, line);

		stringstream ss;
		ss << line;

		int n = 0;
		ss >> n;
		if (n == 0)
			break;

		vector<int> all;
		int temp = 0;
		for (int i = 0; i < n; i++)
		{
			ss >> temp;
			all.push_back(temp);
		}

		int sum = 0;
		for (int i = 0; i < all.size(); i++)
			sum += all[i];

		printf("Case %d:\n", ti);

		bool is_negative = false;
		if (sum < 0)
		{
			is_negative = true;
			sum = -sum;
		}

		int int_part = sum / n;
		int numerator = sum % n;
		int denumerator = n;

		if (numerator == 0)
		{
			if (is_negative)
				printf("- ");
			printf("%d\n", int_part);
		}
		else
		{
			int the_gcd = gcd(numerator, denumerator);
			numerator /= the_gcd;
			denumerator /= the_gcd;

			int int_size = to_string(int_part).size();
			int numerator_size = to_string(numerator).size();
			int denumerator_size = to_string(denumerator).size();

			// line1
			if (is_negative)
				printf("  ");
			for (int i = 0; i < int_size && int_part != 0; i++)
				printf(" ");
			for (int i = 0; i < denumerator_size - numerator_size; i++)
				printf(" ");
			printf("%d\n", numerator);

			// line2
			if (is_negative)
				printf("- ");
			if (int_part != 0)
				printf("%d", int_part);
			for (int i = 0; i < denumerator_size; i++)
				printf("-");
			printf("\n");

			// line3
			if (is_negative)
				printf("  ");
			for (int i = 0; i < int_size && int_part != 0; i++)
				printf(" ");
			printf("%d\n", denumerator);
		}
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