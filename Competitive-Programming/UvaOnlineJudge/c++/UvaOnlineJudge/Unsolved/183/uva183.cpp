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

int matrix[256][256];
char s[65536];
int s_index;
int output_index;

void BtoD_2(int begin_row, int end_row, int begin_col, int end_col)
{
	if (begin_row > end_row || begin_col > end_col)
		return;

	int type = matrix[begin_row][begin_col];

	for (int i = begin_row; i <= end_row && type != -1; i++)
	{
		for (int j = begin_col; j <= end_col && type != -1; j++)
		{
			if (type != matrix[i][j])
			{
				type = -1;
			}
		}
	}

	if (output_index != 0 && output_index % 50 == 0)
		cout << endl;

	if (type != -1)
	{
		cout << type;
		output_index++;
	}
	else
	{
		cout << "D";
		output_index++;

		int mid_row = (begin_row + end_row) / 2;
		int mid_col = (begin_col + end_col) / 2;
		BtoD_2(begin_row, mid_row, begin_col, mid_col);
		BtoD_2(begin_row, mid_row, mid_col + 1, end_col);
		BtoD_2(mid_row + 1, end_row, begin_col, mid_col);
		BtoD_2(mid_row + 1, end_row, mid_col + 1, end_col);
	}
}

void BtoD(int row_count, int col_count)
{
	output_index = 0;
	printf("D%4d%4d\n", row_count, col_count);
	BtoD_2(0, row_count - 1, 0, col_count - 1);
	cout << endl;
}

void DtoB_2(int begin_row, int end_row, int begin_col, int end_col)
{
	if (begin_row > end_row || begin_col > end_col)
		return;

	if (s_index != 0 && s_index % 50 == 0)
		scanf("\n");

	char temp;
	scanf("%c", &temp);

	s_index++;

	if (temp != 'D')
	{
		int type = temp - '0';
		for (int i = begin_row; i <= end_row; i++)
			for (int j = begin_col; j <= end_col; j++)
				matrix[i][j] = type;
	}
	else
	{
		int mid_row = (begin_row + end_row) / 2;
		int mid_col = (begin_col + end_col) / 2;
		DtoB_2(begin_row, mid_row, begin_col, mid_col);
		DtoB_2(begin_row, mid_row, mid_col + 1, end_col);
		DtoB_2(mid_row + 1, end_row, begin_col, mid_col);
		DtoB_2(mid_row + 1, end_row, mid_col + 1, end_col);
	}
}

void DtoB(int row_count, int col_count)
{
	s_index = 0;
	printf("B%4d%4d\n", row_count, col_count);
	DtoB_2(0, row_count - 1, 0, col_count - 1);

	int idx = 0;
	for (int i = 0; i < row_count; i++)
	{
		for (int j = 0; j < col_count; j++)
		{
			if (i != 0 && j != 0 && (i * col_count + j) % 50 == 0)
				cout << endl;

			cout << matrix[i][j];
		}
	}
	cout << endl;
	scanf("\n");
}

void algorithm()
{
	char type;

	while (scanf("%c", &type), type != '#')
	{
		int row;
		int col;
		cin >> row >> col;

		string s2;
		s_index = 0;

		if (type == 'B')
		{
			getline(cin, s2);

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					if ((i * col + j) % 50 == 0 && i != 0 && j != 0)
					{
						scanf("\n");
					}

					char temp;
					scanf("%c", &temp);

					matrix[i][j] = temp - '0';
				}
			}

			scanf("\n");

			BtoD(row, col);
		}
		else
		{
			scanf("\n");
			DtoB(row, col);
		}
	}
}

int main()
{
	algorithm();
	return 0;
}