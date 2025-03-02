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

using namespace std;

static int adjacent_mines(int n, int m, int N, int M, vector<string> input)
{
	int ret = 0;

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			int checked_n = n - i;
			int checked_m = m - j;

			if (0 <= checked_n && checked_n < N &&
				0 <= checked_m && checked_m < M &&
				input[checked_n][checked_m] == '*')
				ret++;
		}

	return ret;
}

int main10189()
{
	int M, N;
	int index = 1;

	while (scanf("%d %d\n", &N, &M), M != 0)
	{
		if (index > 1)
			cout << endl;

		cout << "Field #" << index++ << ":" << endl;

		vector<string> input;
		vector<string> answer;

		for (int i = 0; i < N; i++)
		{
			string s;
			getline(cin, s);
			input.push_back(s);
		}

		for (int i = 0; i < N; i++)
		{
			answer.push_back("");
			for (int j = 0; j < M; j++)
			{
				if (input[i][j] == '*')
					answer.back() += '*';
				else
					answer.back() += '0' + adjacent_mines(i, j, N, M, input);
			}
		}

		for (int i = 0; i < N; i++)
			cout << answer[i] << endl;
	}

	return 0;
}