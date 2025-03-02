#include <cstdio>
#include <cstdlib>
#include <cstring>
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
#include <queue>
#include <functional>
#include <list>
#include <iterator>

using namespace std;

bool adj_matrix[26][26];
bool variables[26];
vector<int> loop_checking_tree;
vector<vector<int>> answer;

static void dfs(bool variables[26], bool adj_matrix[26][26], vector<int> temp_answer)
{
	bool done = true;
	for (int i = 0; i < 26; i++)
	{
		if (variables[i] == true)
		{
			done = false;
			break;
		}
	}

	if (done)
	{
		answer.push_back(temp_answer);
		return;
	}

	for (int i = 0; i < 26; i++)
	{
		if (variables[i])
		{
			bool no_in_degree = true;

			for (int j = 0; j < 26; j++)
			{
				if (adj_matrix[j][i])
				{
					no_in_degree = false;
					break;
				}
			}

			if (no_in_degree)
			{
				vector<int> temp_answer2 = temp_answer;
				temp_answer2.push_back(i);

				variables[i] = false;
				bool adj_matrix2[26][26];
				memcpy(adj_matrix2, adj_matrix, 26 * 26 * sizeof(bool));
				for (int j = 0; j < 26; j++)
					adj_matrix2[i][j] = false;

				dfs(variables, adj_matrix2, temp_answer2);

				variables[i] = true;
			}
		}
	}
}

static bool has_loop_dfs(int node, vector<bool>& visited)
{
	for (int i = 0; i < 26; i++)
		if (adj_matrix[node][i])
		{
			if (visited[i])
				return true;

			visited[i] = true;

			if (has_loop_dfs(i, visited))
				return true;

			visited[i] = false;
		}
			
	return false;
}

static bool has_loop()
{
	for (int i = 0; i < 26; i++)
	{
		vector<bool> v(26, false);
		v[i] = true;
		if (has_loop_dfs(i, v))
			return true;
		v[i] = false;
	}

	return false;
}

static void algorithm()
{
	int test_count;

	cin >> test_count;

	string line;
	getline(cin, line);
	

	for (int test_index = 0; test_index < test_count; test_index++)
	{
		getline(cin, line);

		if (test_index > 0)
			cout << endl;

		memset(adj_matrix, 0, sizeof(adj_matrix));
		memset(variables, 0, sizeof(variables));
		
		answer.clear();

		getline(cin, line);
		
		for (int i = 0; i < line.size(); i++)
		{
			if ('A' <= line[i] && line[i] <= 'Z')
				variables[line[i] - 'A'] = true;
		}

		getline(cin, line);
		for (int i = 0; i < line.size(); i += 4)
			adj_matrix[line[i] - 'A'][line[i + 2] - 'A'] = true;

		if (has_loop())
		{
			cout << "NO" << endl;
		}
		else
		{
			dfs(variables, adj_matrix, vector<int>());

			for (auto it1 = answer.begin(); it1 != answer.end(); it1++)
			{
				vector<int>& v = *it1;

				for (int i = 0; i < v.size(); i++)
				{
					if (i > 0)
						cout << " ";
					cout << char(v[i] + 'A');
				}
				cout << endl;
			}
		}
	}
}

int main872()
{
	algorithm();

	return 0;
}