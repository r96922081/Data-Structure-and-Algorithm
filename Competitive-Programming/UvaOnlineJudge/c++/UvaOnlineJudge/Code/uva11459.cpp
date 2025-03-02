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

int snake_tail[101];
vector<int> players;

int main11459()
{
	int T = 0;
	scanf("%d", &T);

	while (T--)
	{
		players.clear();
		for (int i = 0; i < 101; i++)
			snake_tail[i] = -1;

		int player_count, snake_count, die_count;
		scanf("%d %d %d", &player_count, &snake_count, &die_count);

		while (snake_count--)
		{
			int head, tail;
			scanf("%d %d", &head, &tail);
			snake_tail[head] = tail;
		}

		for (int i = 0; i < player_count; i++)
			players.push_back(1);

		bool game_end = false;
		for (int i = 0; i < die_count; i++)
		{
			int die_number;
			scanf("%d", &die_number);
			if (game_end)
				continue;

			int player = i % player_count;

			int new_pos = players[player] + die_number;
			if (snake_tail[new_pos] != -1)
				new_pos = snake_tail[new_pos];

			if (new_pos >= 100)
				new_pos = 100;

			players[player] = new_pos;

			if (new_pos == 100)
				game_end = true;;
		}

		for (int i = 0; i < player_count; i++)
			cout << "Position of player " << (i + 1) << " is " << players[i] << ".\n";
	}
	return 0;
}