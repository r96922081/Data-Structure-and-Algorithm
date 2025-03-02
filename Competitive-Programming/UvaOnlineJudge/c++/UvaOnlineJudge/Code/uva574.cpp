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

using namespace std;

static int ints[12];
static int answer[12];

static struct Answer
{
	vector<int> answer;
};

static struct compare
{
	bool operator() (const Answer &a, const Answer &b) const;
};

bool compare::operator() (const Answer &a, const Answer &b) const
{
	if (a.answer.size() < b.answer.size())
		return true;
	else if (b.answer.size() > a.answer.size())
		return true;
	else
	{
		for (int i = 0; i < a.answer.size(); i++)
		{
			if (a.answer[i] > b.answer[i])
				return true;
			else if (b.answer[i] > a.answer[i])
				return false;
		}

		return false;
	}
}

set<Answer, compare> all_answers;

static void algorithm2(int n_index, int answer_index, int current_sum, int t, int n)
{
	if (current_sum > t)
		return;

	if (current_sum == t)
	{
		Answer a;
		for (int i = 0; i < answer_index; i++)
			a.answer.push_back(answer[i]);

		if (all_answers.find(a) != all_answers.end())
			return;

		all_answers.insert(a);

		cout << answer[0];

		for (int i = 1; i < answer_index; i++)
			printf("+%d", answer[i]);

		cout << endl;

		return;
	}

	if (n_index == n)
		return;

	answer[answer_index] = ints[n_index];
	algorithm2(n_index + 1, answer_index + 1, current_sum + ints[n_index], t, n);
	algorithm2(n_index + 1, answer_index, current_sum, t, n);
}

static void algorithm()
{
	while (true)
	{
		int t, n;
		scanf("%d %d", &t, &n);
		if (n == 0)
			return;

		for (int i = 0; i < n; i++)
			cin >> ints[i];

		printf("Sums of %d:\n", t);

		all_answers.clear();

		algorithm2(0, 0, 0, t, n);

		if (all_answers.size() == 0)
			cout << "NONE" << endl;
	}
}

int main574()
{
	algorithm();
	return 0;
}