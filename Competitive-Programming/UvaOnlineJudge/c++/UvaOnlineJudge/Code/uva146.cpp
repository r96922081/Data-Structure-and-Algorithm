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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static string next_perm(string s)
{
	for (int i = 1; i < s.size(); i++)
	{
		char currnet_lead = s[s.size() - 1 - i];
		char new_lead = 'z' + 1;

		string rest = "";

		for (int j = 0; j < i; j++)
		{
			if (s[s.size() - 1 - j] > currnet_lead && s[s.size() - 1 - j] < new_lead)
			{
				rest += currnet_lead;
				new_lead = s[s.size() - 1 - j];
			}
			else
			{
				rest += s[s.size() - 1 - j];
			}
		}

		if (new_lead == 'z' + 1)
			continue;

		sort(rest.begin(), rest.end());

		string ret = s.substr(0, s.size() - 1 - i);
		ret += new_lead;
		ret += rest;

		return ret;
	}


	return "";
}

static int algorithm()
{
	while (true)
	{
		string line = "";
		getline(cin, line);
		if (line == "#")
			break;

		string next = next_perm(line);
		if (next == "")
			cout << "No Successor" << endl;
		else
			cout << next << endl;
	}

	return 0;
}

int main146()
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