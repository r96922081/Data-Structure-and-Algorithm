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

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static bool used[1000001];
static bool modulus2[1000001];
static bool modulus3[1000001];

static bool TestSegConflict(int start1, int end1, int start2, int end2)
{
	if (start1 >= 1000000 || start2 >= 1000000)
		return false;

	if (end1 > 1000000)
		end1 = 1000000;

	if (end2 > 1000000)
		end2 = 1000000;

	if ((start1 < end2 && end1 > start2) || (start2 < end1 && end2 > start1))
		return true;
	else
		return false;
}

static bool TestConflict(vector<pair<int, int>>& one_time_jobs, vector<tuple<int, int, int>>& repeated_jobs)
{
	// case1 one_time vs. one_time
	for (int i = 0; i < one_time_jobs.size(); i++)
	{
		auto one_time_job = one_time_jobs[i];
		if (used[one_time_job.first])
			return true;
		if (used[one_time_job.second])
			return true;

		for (int j = one_time_job.first + 1; j < one_time_job.second; j++)
			used[j] = true;
	}

	// case2 repeated vs. one_time
	for (int i = 0; i < one_time_jobs.size(); i++)
	{
		auto one_time_job = one_time_jobs[i];
		
		for (int j = 0; j < repeated_jobs.size(); j++)
		{
			auto repeated_job = repeated_jobs[j];

			int start1 = one_time_job.first;
			int end1 = one_time_job.second;

			if (end1 <= get<0>(repeated_job))
				continue;

			int n = (start1 - get<0>(repeated_job)) / get<2>(repeated_job);

			if (n <= 0)
			{
				if (TestSegConflict(start1, end1, get<0>(repeated_job), get<1>(repeated_job)))
					return true;

				continue;
			}

			int start2 = n * get<2>(repeated_job) + get<0>(repeated_job);
			int end2 = n * get<2>(repeated_job) + get<1>(repeated_job);
			if (TestSegConflict(start1, end1, start2, end2))
				return true;

			int start3 = start2 + get<2>(repeated_job);
			int end3 = end2 +get<2>(repeated_job);
			if (TestSegConflict(start1, end1, start3, end3))
				return true;
		}
	}

	// case3 repeated vs. self!
	for (int i = 0; i < repeated_jobs.size(); i++)
	{
		if ((get<1>(repeated_jobs[i]) - get<0>(repeated_jobs[i])) > get<2>(repeated_jobs[i]))
			return true;
	}

	// case4 repeated vs. repeated
	for (int i = 0; i < repeated_jobs.size(); i++)
	{
		int start1 = get<0>(repeated_jobs[i]);
		int end1 = get<1>(repeated_jobs[i]);
		int interval1 = get<2>(repeated_jobs[i]);

		for (int j = i + 1; j < repeated_jobs.size(); j++)
		{
			memset(modulus2, 0, sizeof(bool) * 1000001);
			memset(modulus3, 0, sizeof(bool) * 1000001);

			int start2 = get<0>(repeated_jobs[j]);
			int end2 = get<1>(repeated_jobs[j]);
			int interval2 = get<2>(repeated_jobs[j]);
			int diff2 = end2 - start2;

			int start3 = start1;
			int end3 = end1;
			int interval3 = interval1;
			int diff3 = end3 - start3;

			if (TestSegConflict(start2, end2, start3, end3))
				return true;

			while (start2 < 1000000 || start3 < 1000000)
			{
				if (start2 <= start3)
				{
					if ((start3 - start2) > interval2)
					{
						start2 = start3 - ((start3 - start2) % interval2);
						end2 = start2 + diff2;
					}

					if (TestSegConflict(start2, end2, start3, end3))
						return true;

					if (modulus2[start3 - start2])
						break;

					modulus2[start3 - start2] = true;

					start2 += interval2;
					end2 += interval2;
				}
				else
				{
					if ((start2 - start3) > interval3)
					{
						start3 = start2 - ((start2 - start3) % interval3);
						end3 = start3 + diff3;
					}

					if (TestSegConflict(start2, end2, start3, end3))
						return true;

					if (modulus3[start2 - start3])
						break;

					modulus3[start2 - start3] = true;

					start3 += interval3;
					end3 += interval3;
				}
			}
		}
	}

	return false;
}

static int algorithm()
{
	int dimension = 0;
	while (true)
	{
		memset(used, 0, sizeof(bool) * 1000001);

		int m, n;
		scanf("%d %d", &m, &n);

		if (m == 0 && n == 0)
			break;
		
		vector<pair<int, int>> one_time_jobs;
		for (int i = 0; i < m; i++)
		{
			int start_time;
			int end_time;
			scanf("%d %d", &start_time, &end_time);
			one_time_jobs.push_back(pair<int, int>(start_time, end_time));
		}

		vector<tuple<int, int, int>> repeated_jobs;
		for (int i = 0; i < n; i++)
		{
			int start_time;
			int end_time;
			int interval;
			scanf("%d %d %d", &start_time, &end_time, &interval);
			repeated_jobs.push_back(tuple<int, int, int>(start_time, end_time, interval));
		}

		if (TestConflict(one_time_jobs, repeated_jobs))
			cout << "CONFLICT" << endl;
		else
			cout << "NO CONFLICT" << endl;
	}

	return 0;
}

int main11926()
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