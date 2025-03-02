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

static void myremove(string& s, char c)
{
	auto end_pos = std::remove(s.begin(), s.end(), c);
	s.erase(end_pos, s.end());
}

int main10945()
{
	string line;

	while(getline(cin, line), line != "DONE")
	{
		myremove(line, '.');
		myremove(line, ',');
		myremove(line, '!');
		myremove(line, '?');
		myremove(line, ' ');
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);

		if (IsPalindrome(line))
			cout << "You won\'t be eaten!" << endl;
		else
			cout << "Uh oh.." << endl;
	}

	return 0;
}