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
#include <tuple>

using namespace std;

vector<string> split(const char *str, char c = ' ');
vector<string> split(string str, char c = ' ');
char to_lower(char c);
string to_lower2(string s);

char all_char_c5[][5][7] = {
	{ ".***..", "*...*.", "*****.", "*...*.", "*...*." },//A
	{ "****..", "*...*.", "****..", "*...*.", "****.." },//B
	{ ".****.", "*...*.", "*.....", "*.....", ".****." },//C
	{ "****..", "*...*.", "*...*.", "*...*.", "****.." },//D
	{ "*****.", "*.....", "***...", "*.....", "*****." },//E
	{ "*****.", "*.....", "***...", "*.....", "*....." },//F
	{ ".****.", "*.....", "*..**.", "*...*.", ".***.." },//G
	{ "*...*.", "*...*.", "*****.", "*...*.", "*...*." },//H
	{ "*****.", "..*...", "..*...", "..*...", "*****." },//I
	{ "..***.", "...*..", "...*..", "*..*..", ".**..." },//J
	{ "*...*.", "*..*..", "***...", "*..*..", "*...*." },//K
	{ "*.....", "*.....", "*.....", "*.....", "*****." },//L
	{ "*...*.", "**.**.", "*.*.*.", "*...*.", "*...*." },//M
	{ "*...*.", "**..*.", "*.*.*.", "*..**.", "*...*." },//N
	{ ".***..", "*...*.", "*...*.", "*...*.", ".***.." },//O
	{ "****..", "*...*.", "****..", "*.....", "*....." },//P
	{ ".***..", "*...*.", "*...*.", "*..**.", ".****." },//Q
	{ "****..", "*...*.", "****..", "*..*..", "*...*." },//R
	{ ".****.", "*.....", ".***..", "....*.", "****.." },//S
	{ "*****.", "*.*.*.", "..*...", "..*...", ".***.." },//T
	{ "*...*.", "*...*.", "*...*.", "*...*.", ".***.." },//U
	{ "*...*.", "*...*.", ".*.*..", ".*.*..", "..*..." },//V
	{ "*...*.", "*...*.", "*.*.*.", "**.**.", "*...*." },//W
	{ "*...*.", ".*.*..", "..*...", ".*.*..", "*...*." },//X
	{ "*...*.", ".*.*..", "..*...", "..*...", "..*..." },//Y
	{ "*****.", "...*..", "..*...", ".*....", "*****." },//Z
	{ "......", "......", "......", "......", "......" },//BLANK
};

char page[61][61];

static bool C1CheckCol(int col)
{
	if (1 <= col && col <= 60)
		return true;
	else
		return false;
}

static bool C5CheckRowCol(int row, int col)
{
	if (row < 1 || 60 < row || col < 1 || 60 < col)
		return false;
	else
		return true;
}

static void PrintC1(string command, string font, int row, string str, string arg3)
{
	if (command == ".P")
	{
		int col = atoi(arg3.c_str());
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ')
				continue;

			if (C1CheckCol(col + i))
				page[row][col + i] = str[i];
		}
	}
	else if (command == ".L")
	{
		int col = 1;

		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ')
				continue;

			if (C1CheckCol(col + i))
				page[row][col + i] = str[i];
		}
	}
	else if (command == ".R")
	{
		int col = 60;

		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ')
				continue;

			if (C1CheckCol(60 - (str.size() - 1 - i)))
				page[row][60 - (str.size() - 1 - i)] = str[i];
		}
	}
	else if (command == ".C")
	{
		int col = 0;
		char c = ' ';
		if (str.size() % 2 == 0)
		{
			int mid_size = str.size() / 2;

			for (int i = 0; i < str.size(); i++)
			{
				c = str[i];
				if (c == ' ')
					continue;

				if (i < mid_size)
				{
					col = 30 - (mid_size - i - 1);
				}
				else
				{
					col = 31 + (i - mid_size);
				}

				if (C1CheckCol(col))
				{
					page[row][col] = c;
				}
			}
		}
		else
		{
			int mid_size = str.size() / 2;
			if (str[mid_size] != ' ')
				page[row][31] = str[mid_size];

			for (int i = 0; i < mid_size; i++)
			{
				c = str[i];
				if (c != ' ')
				{
					col = 31 - (mid_size - i);
					if (C1CheckCol(col))
					{
						page[row][col] = c;
					}
				}

				c = str[mid_size + (mid_size - i)];
				if (c != ' ')
				{
					col = 31 + mid_size - i;
					if (C1CheckCol(col))
					{
						page[row][col] = c;
					}
				}
			}
		}
	}
}

static void PrintC5LeftToRight(int row, int col, string str)
{
	for (int i = 0; i < str.size(); i++, col += 6)
	{
		if (str[i] == ' ')
			continue;

		auto c5 = all_char_c5[str[i] - 'A'];
		for (int i = 0; i < 5; i++)
		{
			int current_row = row + i;
			for (int j = 0; j < 6; j++)
			{
				if (c5[i][j] == '.')
					continue;

				int current_col = col + j;
				if (C5CheckRowCol(current_row, current_col))
					page[current_row][current_col] = c5[i][j];
			}
		}
	}
}

static void PrintC5RightToLeft(int row, int col, string str)
{
	for (int i = 0; i < str.size(); i++, col -= 6)
	{
		char c = str[str.size() - 1 - i];
		if (c == ' ')
			continue;

		auto c5 = all_char_c5[c - 'A'];
		for (int i = 0; i < 5; i++)
		{
			int current_row = row + i;
			for (int j = 5; j >= 0; j--)
			{
				if (c5[i][j] == '.')
					continue;

				int current_col = col - (5 - j);
				if (C5CheckRowCol(current_row, current_col))
					page[current_row][current_col] = c5[i][j];
			}
		}
	}
}

static void PrintC5(string command, string font, int row, string str, string arg3)
{
	if (command == ".P" || command == ".L")
	{
		int col = 1;
		
		if (command == ".P")
			col = atoi(arg3.c_str());

		PrintC5LeftToRight(row, col, str);
	}
	else if (command == ".R")
	{
		int col = 60;
		PrintC5RightToLeft(row, col, str);
	}
	else if (command == ".C")
	{
		if (str.size() % 2 == 0)
		{
			string front = str.substr(0, str.size() / 2);
			string back = str.substr(str.size() / 2);
			PrintC5LeftToRight(row, 31, back);
			PrintC5RightToLeft(row, 30, front);
		}
		else
		{
			int mid = str.size() / 2;

			char c = str[mid];
			auto c5 = all_char_c5[c - 'A'];

			if (c != ' ')
			{
				for (int i = 0; i < 5; i++)
				{
					int current_row = row + i;

					for (int j = 0; j < 3; j++)
					{
						int col = 28 + j;

						if (C5CheckRowCol(current_row, col))
						{
							char c2 = c5[i][j];
							if (c2 == '.')
								continue;
							
							page[current_row][col] = c2;
						}						
					}

					for (int j = 0; j < 3; j++)
					{
						int col = 31 + j;

						if (C5CheckRowCol(current_row, col))
						{
							char c2 = c5[i][3 + j];
							if (c2 == '.')
								continue;

							page[current_row][col] = c2;
						}
					}
				}
			}

			if (str.size() != 1)
			{
				string front = str.substr(0, mid);
				string back = str.substr(mid + 1);
				PrintC5LeftToRight(row, 34, back);
				PrintC5RightToLeft(row, 27, front);
			}
		}
	}
}

int main403()
{
	for (int i = 0; i < 61; i++)
		for (int j = 0; j < 61; j++)
			page[i][j] = '.';

	string line;
	while (getline(cin, line))
	{
		if (line == ".EOP")
		{
			for (int i = 1; i < 61; i++)
			{
				for (int j = 1; j < 61; j++)
					cout << page[i][j];
				cout << endl;
			}

			cout << endl;

			for (int i = 0; i < 60; i++)
				cout << "-";

			cout << endl << endl;

			for (int i = 0; i < 61; i++)
				for (int j = 0; j < 61; j++)
					page[i][j] = '.';

			continue;
		}

		string str = line.substr(line.find('|') + 1, line.size() - line.find('|') - 2);
		line = line.substr(0, line.find('|'));

		vector<string> args = split(line, ' ');
		string command = args[0];
		string font = args[1];
		string row_str = args[2];
		int row = atoi(row_str.c_str());
		string arg3 = "";
		if (command == ".P")
			arg3 = args[3];

		if (font == "C1")
			PrintC1(command, font, row, str, arg3);
		else
			PrintC5(command, font, row, str, arg3);

	}

	return 0;
}













//////////////////// auxiliary function /////////////////////

static vector<string> split(const char *str, char c)
{
	vector<string> result;

	do
	{
		const char *begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(string(begin, str));
	} while (0 != *str++);

	return result;
}

static vector<string> split(string str, char c)
{
	return split(str.c_str(), c);
}

static char to_lower(char c)
{
	if ('a' <= c && c <= 'z')
		return c;
	else
		return c - 'A' + 'a';
}

static string to_lower2(string s)
{
	string ret = "";
	for (int i = 0; i < s.size(); i++)
	{
		ret += to_lower(s[i]);
	}

	return ret;
}