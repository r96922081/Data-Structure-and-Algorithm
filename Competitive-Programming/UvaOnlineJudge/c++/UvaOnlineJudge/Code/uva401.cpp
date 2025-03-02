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

static bool IsPalindrome(string s)
{
	for (int i = 0; i < s.size(); i++)
		if (s[i] != s[s.size() - 1 - i])
			return false;

	return true;
}

map<char, char> mirror_map = { {'A', 'A'}, {'E', '3'}, {'H', 'H'},
{ 'I', 'I' }, { 'J', 'L' },{ 'L', 'J' }, { 'M', 'M' }, { 'O', 'O' },
{ 'S', '2' },{ 'T', 'T' },{ 'U', 'U' },{ 'V', 'V' },{ 'W', 'W' }, 
{ 'X', 'X' },{ 'Y', 'Y' },{ 'Z', '5' },{ '1', '1' },{ '2', 'S' }, 
{ '3', 'E' },{ '5', 'Z' },{ '8', '8' }, };

static bool IsMirror(string s)
{
	int comparing_to = s.size() / 2 - 1;

	if (s.size() % 2 == 1)
		comparing_to++;

	for (int i = 0; i <= comparing_to; i++)
	{
		char c = s[i];
		if (mirror_map.find(c) == mirror_map.end())
			return false;

		if (mirror_map.find(c)->second != s[s.size() - 1 - i])
			return false;
	}

	return true;
}

int main401()
{
	string line;

	while(getline(cin, line))
	{
		bool p = IsPalindrome(line);
		bool m = IsMirror(line);

		if (!p && !m)
			cout << line << " -- " << "is not a palindrome." << endl << endl;
		else if (p && !m)
			cout << line << " -- " << "is a regular palindrome." << endl << endl;
		else if (!p && m)
			cout << line << " -- " << "is a mirrored string." << endl << endl;
		else
			cout << line << " -- " << "is a mirrored palindrome." << endl << endl;
	}

	return 0;
}