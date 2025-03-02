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
	UN_VISITED,
	WATER,
	VISITED,
}CELL_TYPE;

static struct MyPair {
	MyPair(int x, int y) : x(x), y(y) {}
	int x;
	int y;
	friend bool operator<(const MyPair& l, const MyPair& r)
	{
		if (l.x < r.x)
			return true;
		else if (l.x > r.x)
			return false;
		else
			return l.y < r.y;
	}
};

static int R, C, M, N;
static vector<vector<CELL_TYPE>> game_map;
static vector<int> x_diff;
static vector<int> y_diff;

static bool valid_move(int x, int y)
{
	if (x < 0 || R <= x || y < 0 || C <= y)
		return false;

	if (game_map[x][y] == WATER)
		return false;

	return true;
}

static void algorithm()
{
	int test_count;

	cin >> test_count;

	for (int ti = 1; ti <= test_count; ti++)
	{
		cin >> R >> C >> N >> M;

		int water_count;

		if (N == M)
		{
			x_diff = vector<int>({ M, -M, M, -M });
			y_diff = vector<int>({ M, M, -M, -M });
		}
		else if (N == 0)
		{
			x_diff = vector<int>({ M, -M, 0, 0 });
			y_diff = vector<int>({ 0, 0, M, -M });
		}
		else if (M == 0)
		{
			x_diff = vector<int>({ N, -N, 0, 0 });
			y_diff = vector<int>({ 0, 0, N, -N });
		}
		else
		{
			x_diff = vector<int>({ M, -M, M, -M, N, -N, N, -N });
			y_diff = vector<int>({ N, N, -N, -N, M, M, -M, -M });
		}

		game_map = vector<vector<CELL_TYPE>>(R, vector<CELL_TYPE>(C, UN_VISITED));

		cin >> water_count;

		while (water_count--)
		{
			int x, y;
			cin >> x >> y;
			game_map[x][y] = WATER;
		}

		stack<MyPair> s;
		
		s.push(MyPair(0, 0));

		int even_count = 0;
		int odd_count = 0;

		while (!s.empty())
		{
			MyPair p = s.top();
			s.pop();

			game_map[p.x][p.y] = VISITED;

			int valid_count = 0;

			for (int i = 0; i < x_diff.size(); i++)
			{
				int next_x = p.x + x_diff[i];
				int next_y = p.y + y_diff[i];
				if (valid_move(next_x, next_y))
				{
					valid_count++;

					if (game_map[next_x][next_y] == UN_VISITED)
					{
						game_map[next_x][next_y] = VISITED;
						s.push(MyPair(next_x, next_y));
					}
				}
			}

			if (valid_count % 2 == 0)
				even_count++;
			else
				odd_count++;
		}



		printf("Case %d: %d %d\n", ti, even_count, odd_count);
	}
}

int main11906()
{
	algorithm();

	return 0;
}