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

vector<char> all_score;
int all_ball_down[12][3];

int main584()
{
	while (true)
	{
		all_score.clear();
		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 3; j++)
				all_ball_down[i][j] = 0;

		char space;
		do
		{
			char score;
			scanf("%c", &score);
			if (score == 'G')
				return 0;

			all_score.push_back(score);

			scanf("%c", &space);
		} while (space != '\n');

		int frame_index = 1;
		int order_in_frame = 0;
		int current_frame_score = 0;

		for (int i = 0; i < all_score.size(); i++)
		{
			if (all_score[i] == '/')
			{
				all_ball_down[frame_index][order_in_frame] = 10 - all_ball_down[frame_index][order_in_frame - 1];

				if (frame_index != 10)
				{
					frame_index++;
					order_in_frame = 0;
				}
				else
				{
					order_in_frame++;
				}
			}
			else if (all_score[i] == 'X')
			{
				all_ball_down[frame_index][order_in_frame] = 10;

				if (frame_index != 10)
				{
					frame_index++;
					order_in_frame = 0;
				}
				else
				{
					order_in_frame++;
				}
			}
			else
			{
				all_ball_down[frame_index][order_in_frame] = all_score[i] - '0';
				order_in_frame++;

				if (frame_index != 10 && order_in_frame == 2)
				{
					frame_index++;
					order_in_frame = 0;
				}
			}				
		}

		int game_score = 0;

		for (int i = 1; i <= 9; i++)
		{
			if (all_ball_down[i][0] == 10)
			{
				game_score += 10;
				if (i < 9)
				{
					game_score += all_ball_down[i + 1][0];
					if (all_ball_down[i + 1][0] == 10)
					{
						game_score += all_ball_down[i + 2][0];
					}
					else
					{
						game_score += all_ball_down[i + 1][1];
					}
				}
				else
				{
					game_score += all_ball_down[10][0];
					game_score += all_ball_down[10][1];
				}
			}
			else
			{
				game_score += all_ball_down[i][0] + all_ball_down[i][1];
				if (all_ball_down[i][0] + all_ball_down[i][1] == 10)
					game_score += all_ball_down[i + 1][0];
			}
		}

		if (all_ball_down[10][0] == 10)
		{
			game_score += 10 + all_ball_down[10][1] + all_ball_down[10][2];
		}
		else if (all_ball_down[10][0] + all_ball_down[10][1] == 10)
		{
			game_score += 10 + all_ball_down[10][2];
		}
		else
		{
			game_score += all_ball_down[10][0] + all_ball_down[10][1];
		}

		cout << game_score << endl;
	}

	return 0;
}