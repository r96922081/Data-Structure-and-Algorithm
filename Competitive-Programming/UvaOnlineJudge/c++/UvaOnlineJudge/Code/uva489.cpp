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

int main489()
{
	int T = 0;

	while (scanf("%d\n", &T), T != -1)
	{
		string answer = "";
		string guesses = "";
		getline(cin, answer);
		getline(cin, guesses);

		cout << "Round " << T << endl;

		int guess_count = guesses.size();

		unordered_set<char> answer2;
		for (int i = 0; i < answer.size(); i++)
			answer2.insert(answer[i]);

		bool end = false;
		int error_count = 0;

		for (int i = 0; i < guesses.size(); i++)
		{
			auto iter = answer2.find(guesses[i]);
			if (iter != answer2.end())
			{
				answer2.erase(iter);
				if (answer2.size() == 0)
				{
					cout << "You win." << endl;
					end = true;
					break;
				}					
			}
			else
			{
				error_count++;
				if (error_count == 7)
				{
					cout << "You lose." << endl;
					end = true;
					break;
				}
			}
		}

		if (end)
			continue;

		cout << "You chickened out." << endl;
	}

	return 0;
}