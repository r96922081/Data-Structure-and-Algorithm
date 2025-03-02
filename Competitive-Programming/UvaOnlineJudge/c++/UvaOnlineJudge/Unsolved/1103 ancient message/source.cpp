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

int height, weight;
int input_map[200][200];
int character[200][200];
vector<pair<int, int>> v;
int prev_left_most_x;
int prev_left_most_y;

int x_diff[8] = { 1, 1, -1, -1, 0, 0, -1, 1 };
int y_diff[8] = { -1, 1, -1, 1, -1, 1, 0, 0 };

void find_leftmost_equal_to_value(int input[][200], int& x, int& y, int value)
{
	x = -1;
	y = -1;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < weight; i++)
		{
			if (input[j][i] == value)
			{
				x = i;
				y = j;
				return;
			}
		}
	}
}

bool fill(int x, int y)
{
	bool valid_circle = true;

	v.clear();
	v.resize((height + 1) * (weight + 1));

	int v_write_index = 0;
	int v_read_index = 0;

	v[v_write_index++] = pair<int, int>(x, y);

	character[y][x] = 1;

	while (v_read_index < v_write_index)
	{
		auto front = v[v_read_index++];
		x = front.first;
		y = front.second;
		
		for (int i = 0; i < 8; i++)
		{
			int next_x = x + x_diff[i];
			int next_y = y + y_diff[i];

			if (next_x < 0 || weight <= x || next_y < 0 || height <= y)
			{
				valid_circle = false;
				continue;
			}

			if (character[next_y][next_x] == 0)
			{
				character[next_y][next_x] = 1;
				v[v_write_index++] = pair<int, int>(next_x, next_y);
			}
		}
	}

	return valid_circle;
}

char tell_character()
{
	int count = 0;

	while (true)
	{
		int x, y;
		find_leftmost_equal_to_value(character, x, y, 0);
		if (x == -1)
			break;

		if (fill(x, y))
			count++;
	}

	if (count == 0)
		return 'W';
	if (count == 1)
		return 'A';
	if (count == 2)
		return 'K';
	if (count == 3)
		return 'J';
	if (count == 4)
		return 'S';
	if (count == 5)
		return 'D';

	return 'X';
}

void get_character(int x, int y)
{
	if (input_map[y][x])
	{
		input_map[y][x] = 0;
		character[y][x] = 1;
		for (int i = 0; i < 8; i++)
		{
			int next_x = x + x_diff[i];
			int next_y = y + y_diff[i];

			if (next_x < 0 || weight <= x || next_y < 0 || height <= y)
				continue;

			get_character(next_x, next_y);
		}
	}
}

void print_map()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < weight; j++)
		{
			if (input_map[i][j] == 1)
				printf("*");
			else
				printf(" ");
		}

		printf("\n");
	}

	printf("=================\n\n");
	fflush(stdout);
}

void algorithm()
{
	int H, W;
	int test_count = 0;

	while (cin >> H >> W, H != 0)
	{
		test_count++;
		printf("Case %d: ", test_count);
		scanf("\r\n");
		height = H;
		weight = W * 4;
		memset(input_map, 0, sizeof(int) * 200 * 200);

		for (int h = 0; h < H; h++)
		{
			for (int w = 0; w < W; w++)
			{
				char c;
				scanf("%c", &c);
				int input = 0;
				if ('a' < c)
					input = 10 + c - 'a';
				else
					input = c - '0';

				for (int i = 0; i < 4; i++)
				{
					input_map[h][w * 4 + (3 - i)] = input % 2;
					input >>= 1;
				}
			}

			scanf("\r\n");
		} // end for h

		//print_map();

		int leftmost_x;
		int leftmost_y;

		find_leftmost_equal_to_value(input_map, leftmost_x, leftmost_y, 1);
		multiset<char> answers;
		do 
		{
			get_character(leftmost_x, leftmost_y);
			answers.insert(tell_character());

			memset(character, 0, sizeof(int) * 200 * 200);
			find_leftmost_equal_to_value(input_map, leftmost_x, leftmost_y, 1);
			
			//print_map();
		} while (leftmost_x != -1);

		for (auto it = answers.begin(); it != answers.end(); it++)
		{
			printf("%c", *it);
		}

		printf("\n");
		

	} // end while
}

int main()
{
	algorithm();

	return 0;
}