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

bool burned_out[7];

char digits[10][8] = 
{
	"YYYYYYN",
	"NYYNNNN",
	"YYNYYNY",
	"YYYYNNY",
	"NYYNNYY",
	"YNYYNYY",
	"YNYYYYY",
	"YYYNNNN",
	"YYYYYYY",
	"YYYYNYY",
};
char lines[10][7];
int line_count;
int line_index = 0;
int target_value = 0;

static bool algorithm2()
{
	if (line_index == line_count)
		return true;

	char* line = lines[line_index];
	char* target_line = digits[target_value];

	for (int i = 0; i < 7; i++)
	{
		if (line[i] == 'Y')
		{
			if (target_line[i] == 'N')
				return false;

			if (burned_out[i])
				return false;
		}
		else
		{
			if (target_line[i] == 'Y')
				burned_out[i] = true;
		}
	}

	target_value--;
	line_index++;
	algorithm2();
}

static void algorithm()
{
	while (cin >> line_count, line_count != 0)
	{
		scanf("\n");
		string line;

		if (line_count > 10)
		{
			cout << "MISMATCH" << endl;
			for (int i = 0; i < line_count; i++)
				getline(cin, line);

			continue;
		}

		for (int i = 0; i < line_count; i++)
		{
			getline(cin, line);
			for (int j = 0; j < 7; j++)
				lines[i][j] = line[j];
		}

		bool match = false;
		for (int i = 9; i >= line_count - 1; i--)
		{
			for (int j = 0; j < 7; j++)
				burned_out[j] = false;

			line_index = 0;
			target_value = i;
			if (algorithm2())
			{
				match = true;
				break;
			}
		}

		if (match)
			cout << "MATCH" << endl;
		else
			cout << "MISMATCH" << endl;
	}
}

int main416()
{
	algorithm();
	return 0;
}