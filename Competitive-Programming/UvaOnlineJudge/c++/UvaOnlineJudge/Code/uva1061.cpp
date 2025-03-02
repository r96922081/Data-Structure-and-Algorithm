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


static struct cmp
{
	set<char> cmp1;
	set<char> cmp2;
	string result;
};

static string get_answer(const set<string>& answer_blood, const set<string>& answer_rh)
{
	if (answer_blood.size() == 0 || answer_rh.size() == 0)
		return "IMPOSSIBLE";

	string answer = "";
	if (answer_blood.size() != 1 || answer_rh.size() != 1)
		answer = "{";

	bool first = true;

	for (auto blood = answer_blood.begin(); blood != answer_blood.end(); blood++)
	{
		for (auto rh = answer_rh.begin(); rh != answer_rh.end(); rh++)
		{
			if (!first)
				answer += ", ";
			answer += *blood + *rh;
			first = false;
		}
	}

	if (answer_blood.size() != 1 || answer_rh.size() != 1)
		answer += "}";

	return answer;
}

int main1061()
{
	string line = "";

	auto combination_to_blood =
		map<string, string>{ {"AA", "A"},{ "AB", "AB" }, { "AO", "A" }, 
							{ "BB", "B" },{ "BO", "B" }, { "OO", "O" }};

	auto blood_to_combination =
		map<string, vector<string>>{ { "A", vector<string> {"AA", "AO"} },{ "AB", vector<string> {"AB"} },
		{ "B", vector<string> {"BB", "BO"} }, { "O", vector<string> {"OO"} } };

	int test_index = 0;
	while (getline(cin, line))
	{
		char p1_char[255];
		char p2_char[255];	
		char p3_char[255];
		test_index++;
		sscanf(line.c_str(), "%s %s %s", p1_char, p2_char, p3_char);

		string p1 = p1_char;
		string p2 = p2_char;
		string child = p3_char;

		if (p1 == "E")
			break;

		if (child == "?")
		{
			string p1_rh = p1.substr(p1.size() - 1);
			string p1_blood = p1.substr(0, p1.size() - 1);
			string p2_rh = p2.substr(p2.size() - 1);
			string p2_blood = p2.substr(0, p2.size() - 1);

			set<string> answer_rh;
			if (p1_rh == "-" && p2_rh == "-")
			{
				answer_rh.insert("-");
			}
			else
			{
				answer_rh.insert("+");
				answer_rh.insert("-");
			}
			
			set<string> answer_blood;

			vector<string> p1_combinations = blood_to_combination[p1_blood];
			vector<string> p2_combinations = blood_to_combination[p2_blood];

			
			for (int i = 0; i < p1_combinations.size(); i++)
			{
				string p1_combination = p1_combinations[i];
				for (int j = 0; j < p2_combinations.size(); j++)
				{
					string p2_combination = p2_combinations[j];
					
					for (int k = 0; k < p1_combination.size(); k++)
					{
						for (int l = 0; l < p2_combination.size(); l++)
						{
							string combination = "";
							combination += p1_combination[k];
							combination += p2_combination[l];

							if (combination[0] > combination[1])
							{
								char temp = combination[0];
								combination[0] = combination[1];
								combination[1] = temp;
							}
								
							answer_blood.insert(combination_to_blood[combination]);
						}
					}
				}
			}

			string answer = get_answer(answer_blood, answer_rh);

			cout << "Case " << test_index << ": " << p1 << " " << p2 << " " << answer << endl;
		}
		else
		{
			string child_rh = child.substr(child.size() - 1);
			string child_blood = child.substr(0, child.size() - 1);
			vector<string> child_combinations = blood_to_combination[child_blood];

			string p = p1;
			if (p1 == "?")
				p = p2;

			string p_rh = p.substr(p.size() - 1);
			string p_blood = p.substr(0, p.size() - 1);
			vector<string> p_combinations = blood_to_combination[p_blood];

			set<string> answer_rh;

			if (child_rh == "-")
			{
				answer_rh.insert("+");
				answer_rh.insert("-");
			}
			else
			{
				if (p_rh == "-")
					answer_rh.insert("+");
				else
				{
					answer_rh.insert("+");
					answer_rh.insert("-");
				}
			}

			set<string> answer_blood;

			for (int i = 0; i < child_combinations.size(); i++)
			{
				string child_combination = child_combinations[i];

				for (int j = 0; j < child_combination.size(); j++)
				{
					for (int k = 0; k < p_combinations.size(); k++)
					{
						string p_combination = p_combinations[k];

						for (int l = 0; l < p_combination.size(); l++)
						{
							if (child_combination[j] == p_combination[l])
							{
								string remain_single_combination = "";
								remain_single_combination += child_combination[(j + 1) % 2];

								for (auto m = combination_to_blood.begin(); m != combination_to_blood.end(); m++)
								{
									if (m->first.find(remain_single_combination) != m->first.npos)
										answer_blood.insert(m->second);
								}
							}
						}
					}
				}
			}

			string answer = get_answer(answer_blood, answer_rh);

			if (p1 == "?")
				p1 = answer;
			else
				p2 = answer;

			cout << "Case " << test_index << ": " << p1 << " " << p2 << " " << child << endl;
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