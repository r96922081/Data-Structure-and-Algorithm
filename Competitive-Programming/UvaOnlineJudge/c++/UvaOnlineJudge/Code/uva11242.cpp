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
	int f;

	while (cin >> f, f != 0)
	{
		int r;
		cin >> r;

		int temp;
		vector<int> F;
		vector<double> D;

		for (int i = 0; i < f; i++)
			cin >> temp, F.push_back(temp);

		for (int i = 0; i < r; i++)
		{
			cin >> temp;
			for (int j = 0; j < F.size(); j++)
				D.push_back((double)temp / (double)F[j]);
		}

		sort(D.begin(), D.end());

		double max_s = -1;
		for (int i = 0; i < D.size() - 1; i++)
			max_s = max(max_s, D[i + 1] / D[i]);

		printf("%.2lf\n", max_s);
	}	
}

int main11242()
{
	algorithm();
	return 0;
}