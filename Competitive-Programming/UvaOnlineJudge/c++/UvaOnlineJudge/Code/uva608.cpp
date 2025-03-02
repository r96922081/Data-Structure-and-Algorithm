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

using namespace std;

//////////////////// auxiliary functions /////////////////////
vector<string> split(const char *str, char c = ' ');
vector<string> split(string str, char c = ' ');
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////


static struct cmp
{
	set<char> cmp1;
	set<char> cmp2;
	string result;
};

int main608()
{
	int T = 0;
	scanf("%d\n", &T);

	while (T--)
	{
		cmp compares[3];
		string weight = "";

		for (int i = 0; i < 3; i++)
		{
			compares[i].cmp1.clear();
			compares[i].cmp2.clear();
			compares[i].result = "";

			string line = "";
			getline(cin, line);
			auto s = split(line.c_str());
			compares[i].cmp1.insert(s[0].begin(), s[0].end());
			compares[i].cmp2.insert(s[1].begin(), s[1].end());
			compares[i].result = s[2];
		}

		while (true)
		{
			bool break_while = false;

			for (int i = 0; i < 3; i++)
			{
				if (compares[i].result == "even")
				{
					set<char> v;
					v.insert(compares[i].cmp1.begin(), compares[i].cmp1.end());
					v.insert(compares[i].cmp2.begin(), compares[i].cmp2.end());

					for (auto it = v.begin(); it != v.end(); it++)
					{
						for (int k = 0; k < 3; k++)
						{
							compares[k].cmp1.erase(*it);
							compares[k].cmp2.erase(*it);
						}
					}
				}
				else
				{
					cmp& cmp_a = compares[i];

					for (int j = 1; j <= 2; j++)
					{
						cmp& cmp_b = compares[(i + j) % 3];
						if (cmp_b.result == "even")
							break;

						set<char> set_a;
						set_a.insert(cmp_a.cmp1.begin(), cmp_a.cmp1.end());
						set_a.insert(cmp_a.cmp2.begin(), cmp_a.cmp2.end());

						set<char> set_b;
						set_b.insert(cmp_b.cmp1.begin(), cmp_b.cmp1.end());
						set_b.insert(cmp_b.cmp2.begin(), cmp_b.cmp2.end());

						vector<char> v1(12);

						auto it = set_difference(set_a.begin(), set_a.end(), set_b.begin(), set_b.end(), v1.begin());
						v1.resize(it - v1.begin());

						if (cmp_a.result == cmp_b.result)
						{
							vector<char> v2(12);
							auto it = set_intersection(cmp_a.cmp1.begin(), cmp_a.cmp1.end(), cmp_b.cmp2.begin(), cmp_b.cmp2.end(), v2.begin());
							v2.resize(it - v2.begin());

							vector<char> v3(12);
							it = set_intersection(cmp_a.cmp2.begin(), cmp_a.cmp2.end(), cmp_b.cmp1.begin(), cmp_b.cmp1.end(), v3.begin());
							v3.resize(it - v3.begin());

							v1.insert(v1.begin(), v2.begin(), v2.end());
							v1.insert(v1.begin(), v3.begin(), v3.end());
						}
						else
						{
							vector<char> v2(12);
							auto it = set_intersection(cmp_a.cmp1.begin(), cmp_a.cmp1.end(), cmp_b.cmp1.begin(), cmp_b.cmp1.end(), v2.begin());
							v2.resize(it - v2.begin());

							vector<char> v3(12);
							it = set_intersection(cmp_a.cmp2.begin(), cmp_a.cmp2.end(), cmp_b.cmp2.begin(), cmp_b.cmp2.end(), v3.begin());
							v3.resize(it - v3.begin());

							v1.insert(v1.begin(), v2.begin(), v2.end());
							v1.insert(v1.begin(), v3.begin(), v3.end());
						}

						for (auto it = v1.begin(); it != v1.end(); it++)
						{
							for (int k = 0; k < 3; k++)
							{
								compares[k].cmp1.erase(*it);
								compares[k].cmp2.erase(*it);
							}
						}
					}
				}

				char answer = ' ';

				for (int i = 0; i < 3; i++)
				{
					if (compares[i].cmp1.size() == 0 && compares[i].cmp2.size() == 1)
					{
						if (compares[i].result == "up")
							weight = "light";
						else
							weight = "heavy";

						answer = *compares[i].cmp2.begin();
						break;
					}
					else if (compares[i].cmp1.size() == 1 && compares[i].cmp2.size() == 0)
					{
						if (compares[i].result == "up")
							weight = "heavy";
						else
							weight = "light";

						answer = *compares[i].cmp1.begin();
						break;
					}
				}

				if (answer != ' ')
				{
					cout << answer << " is the counterfeit coin and it is " << weight << ".\n";
					break_while = true;
					break;
				}
			}
				
			if (break_while)
				break;
		}
	}

	return 0;
}













//////////////////// auxiliary functions /////////////////////

static vector<string> split(const char *str, char c)
{
	vector<string> result;

	do
	{
		const char *begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(string(begin, str));
	} while (0 != *str++);

	return result;
}

static vector<string> split(string str, char c)
{
	return split(str.c_str(), c);
}

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