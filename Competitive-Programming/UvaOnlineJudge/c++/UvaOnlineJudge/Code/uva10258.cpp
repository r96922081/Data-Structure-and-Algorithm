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

static struct Score
{
	int contestant;
	int ac_count;
	int penality;
};

static struct Problem
{
	Problem(bool ac, int penality) : penality(penality), ac(ac) {}
	int penality;
	bool ac;
};

static int algorithm()
{

	int T = 0;
	scanf("%d\n", &T);
	
	for (int ti = 0; ti < T; ti++)
	{ 
		if (ti > 0)
			cout << endl;

		string line = "";
		
		map<int, map<int, Problem>> stats;

		while (getline(cin, line), line != "")
		{
			int contestant;
			int problem;
			int time;
			char L;
			sscanf(line.c_str(), "%d %d %d %c", &contestant, &problem, &time, &L);

			bool ac = true;
			int penality = time;

			if (L == 'R' || L == 'U' || L == 'E')
			{
				ac = false;
				penality = 0;
			}
			else if (L == 'I')
			{
				ac = false;
				penality = 20;
			}

			if (stats.find(contestant) == stats.end())
			{
				map<int, Problem> problem_stats;

				problem_stats.insert(pair<int, Problem>(problem, Problem(ac, penality)));

				stats.insert(pair<int, map<int, Problem>>(contestant, problem_stats));
			}
			else
			{
				map<int, Problem>& problem_stats = stats.find(contestant)->second;

				auto it2 = problem_stats.find(problem);

				if (it2 == problem_stats.end())
				{
					problem_stats.insert(pair<int, Problem>(problem, Problem(ac, penality)));
				}
				else
				{
					Problem& p = it2->second;

					if (!p.ac)
					{
						p.penality += penality;
						p.ac = ac;
					}
				}
			}
		}

		vector<Score> all_score;

		for (auto it = stats.begin(); it != stats.end(); it++)
		{
			Score s;
			s.ac_count = 0;
			s.penality = 0;

			map<int, Problem>& problem_stats = it->second;
			s.contestant = it->first;

			for (auto it2 = problem_stats.begin(); it2 != problem_stats.end(); it2++)
			{
				if (it2->second.ac)
				{
					s.ac_count++;
					s.penality += it2->second.penality;
				}
			}

			all_score.push_back(s);
		}

		std::sort(all_score.begin(), all_score.end(), [](Score a, Score b)
		{
			if (a.ac_count > b.ac_count)
				return true;
			else if (a.ac_count < b.ac_count)
				return false;
			else
			{
				if (a.penality < b.penality)
					return true;
				else if (a.penality > b.penality)
					return false;
				else
				{
					return a.contestant < b.contestant;
				}
			}
		});

		for (auto it = all_score.begin(); it != all_score.end(); it++)
		{
			printf("%d %d %d\n", it->contestant, it->ac_count, it->penality);
		}
	}

	return 0;
}

int main10258()
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