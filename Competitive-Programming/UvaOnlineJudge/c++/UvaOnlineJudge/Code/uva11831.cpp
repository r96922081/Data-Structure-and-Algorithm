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

typedef enum {
	EMPTY,
	STAR,
	WALL,
	ROBOT,
}cell;

// N = 0, L = 1, S = 2, O = 3
int dir_x[4] = { 0, 1, 0, -1 };
int dir_y[4] = { -1, 0, 1, 0 };

static void algorithm()
{
	int N, M, S;
	string line;
	char c;
	while (cin >> N >> M >> S, N != 0)
	{
		getline(cin, line);
		vector<vector<cell>> game_map(N, vector<cell>(M, EMPTY));
		int dir = 0;
		int current_x;
		int current_y;
		int score = 0;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cin >> c;

				if (c == '.')
				{ 
					game_map[i][j] = EMPTY;
				}
				else if (c == '*')
				{
					game_map[i][j] = STAR;
				}
				else if (c == '#')
				{
					game_map[i][j] = WALL;
				}
				else
				{
					current_x = j;
					current_y = i;

					if (c == 'N')
						dir = 0;
					else if (c == 'L')
						dir = 1;
					else if (c == 'S')
						dir = 2;
					else if (c == 'O')
						dir = 3;
				}
			}

			getline(cin, line);
		}

		for (int i = 0; i < S; i++)
		{
			char order;
			cin >> order;

			if (order == 'D')
				dir = (dir + 1) % 4;
			else if (order == 'E')
			{
				if (dir == 0)
					dir = 3;
				else
					dir = dir - 1;
			}
			else
			{
				int next_x = current_x + dir_x[dir];
				int next_y = current_y + dir_y[dir];

				if (next_x < 0 || M <= next_x || next_y < 0 || N <= next_y)
					continue;
				else if (game_map[next_y][next_x] == WALL)
					continue;
				else
				{
					current_x = next_x;
					current_y = next_y;

					if (game_map[next_y][next_x] == STAR)
					{
						game_map[next_y][next_x] = EMPTY;
						score++;
					}
				}
			}
		}

		cout << score << endl;
	}
}

int main11831()
{
	algorithm();

	return 0;
}