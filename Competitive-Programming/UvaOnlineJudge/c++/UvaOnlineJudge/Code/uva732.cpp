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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static void alg2(const string& target, int ti, const string& source, int si, string answer, vector<string>& answers, stack<char> s)
{
	auto s2 = s;

	if (s.size() > 0 && s.top() == target[ti])
	{
		s.pop();
		alg2(target, ti + 1, source, si, answer + "o", answers, s);
	}

	if (si < source.size())
	{ 
		s2.push(source[si]);
		alg2(target, ti, source, si + 1, answer + "i", answers, s2);
	}
	else
	{
		if (s2.size() == 0 && ti == target.size())
			answers.push_back(answer);
	}

}

static int algorithm()
{
	while (true)
	{
		string source = "";
		string target = "";
		if (!getline(cin, source))
			break;

		getline(cin, target);

		string answer = "";
		vector<string> answers;
		stack<char> s;

		alg2(target, 0, source, 0, answer, answers, s);

		sort(answers.begin(), answers.end());

		cout << "[" << endl;
		for (int i = 0; i < answers.size(); i++)
			for (int j = 0; j < answers[i].size(); j++)
			{
				cout << answers[i][j];
				if (j == answers[i].size() - 1)
					cout << endl;
				else
					cout << " ";
			}
		cout << "]" << endl;
	}

	return 0;
}

int main732()
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