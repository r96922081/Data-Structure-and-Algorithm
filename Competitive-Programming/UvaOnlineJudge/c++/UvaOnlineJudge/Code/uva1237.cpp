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

static void algorithm()
{
	int test_case_count = 0;
	scanf("%d\n", &test_case_count);

	for (int ti = 0; ti < test_case_count; ti++)
	{
		if (ti >= 1)
			cout << endl;

		int db_count;
		scanf("%d", &db_count);

		vector<string> name;
		vector<int> L;
		vector<int> H;

		char temp[21];
		int l;
		int h;

		for (int i = 0; i < db_count; i++)
		{
			scanf("%s %d %d", temp, &l, &h);

			name.push_back(temp);
			L.push_back(l);
			H.push_back(h);
		}

		int query_count = 0;
		scanf("%d", &query_count);

		bool end = false;

		for (int qi = 0; qi < query_count; qi++)
		{
			string answer = "";
			int price = 0;
			scanf("%d", &price);

			for (int i = 0; i < L.size(); i++)
			{
				if (L[i] <= price && price <= H[i])
				{
					if (answer != "")
					{
						answer = "";
						break;
					}
					else
						answer = name[i];
				}
			}

			if (answer == "")
				cout << "UNDETERMINED" << endl;
			else
				cout << answer << endl;
		}
	}
}

int main1237()
{
	algorithm();
	return 0;
}