package main

import "fmt"

func main() {
    fmt.Println("P220")
}

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

class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) 
	{
		multiset<long long> s;

		if (nums.size() == 0)
			return false;

		if (k == 0)
		{
			return false;
		}

		for (int i = 0; i < nums.size(); i++)
		{
			int remove = i - k - 1;
			if (remove >= 0)
			{
				auto it = s.find(nums[remove]);
				s.erase(it);
			}

			s.insert(nums[i]);
			auto it = s.find(nums[i]);

			if (it != s.begin())
			{
				auto it2 = it--;
				if (abs(*it2 - *it) <= t)
				{
					return true;
				}
					
				it++;
			}

			it++;
			auto it2 = it;
			it--;
			if (it2 != s.end())
			{
				if (abs(*it2 - *it) <= t)
				{
					return true;
				}
					
			}
		}

		return false;
	}
};

void check2(bool b) {
	if (!b)
	{
		cout << "error" << endl;
	}
}

int main()
{
	Solution s;
	int a1[] = { 3,6,0,4 };
	vector<int> v1(a1, a1 + 4);
	check2(s.containsNearbyAlmostDuplicate(v1, 2, 2) == true);

	int a2[] = { 1,0,1,1 };
	vector<int> v2(a2, a2 + 4);
	check2(s.containsNearbyAlmostDuplicate(v2, 1, 2) == true);

	int a3[] = { 1,5,9,1,5,9 };
	vector<int> v3(a3, a3 + 6);
	check2(s.containsNearbyAlmostDuplicate(v3, 2, 3) == false);

	int a4[] = { 1, 2 };
	vector<int> v4(a4, a4 + 2);
	check2(s.containsNearbyAlmostDuplicate(v4, 0, 1) == false);
	
	int a5[] = { -1, 2147483647 };
	vector<int> v5(a5, a5 + 2);
	check2(s.containsNearbyAlmostDuplicate(v5, 1, 2147483647) == false);

	return 0;
}
