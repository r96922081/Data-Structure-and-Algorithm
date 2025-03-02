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
	unsigned int N, L, U, M;
	while (cin >> N >> L >> U)
	{
		M = ~N;
		
		bool compare_M = true;
		bool compare_L = true;

		bitset<32> u(U);
		bitset<32> m(M);
		bitset<32> l(L);

		for (int i = 31; i >= 0 && (compare_M || compare_L); i--)
		{
			if (compare_M && compare_L)
			{
				if (u.test(i) && !m.test(i) && !l.test(i))
					compare_M = false;
				else if (u.test(i) && !m.test(i) && l.test(i))
					m.set(i);
				else if (u.test(i) && m.test(i) && !l.test(i))
					compare_L = false;
				else if (!u.test(i) && m.test(i) && !l.test(i))
					m.reset(i);
			}
			else if (compare_M)
			{
				if (u.test(i) && !m.test(i))
					compare_M = false;
				else if (!u.test(i) && m.test(i))
					m.reset(i);
			}
			else if (compare_L)
			{
				if (m.test(i) && !l.test(i))
					compare_L = false;
				else if (!m.test(i) && l.test(i))
					m.set(i);
			}
		}

		cout << m.to_ulong() << endl;
	}
}

int main10718()
{
	algorithm();
	return 0;
}