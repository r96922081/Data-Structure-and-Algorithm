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
#include <sstream>
#include <cassert>

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

static struct SegmentManager
{
	SegmentManager(int S) : S(S) { Reset(); }
	void Reset() { memset(A, 0, 100001 * sizeof(int)); }
	void Delete(int L, int R, int& left, int& right)
	{
		if ((L > 1 && A[L - 1] != 0) && (R != S && A[R + 1] != 0))
		{
			int temp_R_1 = A[R + 1];
			int temp_L_1 = A[L - 1];
			A[A[L - 1]] = temp_R_1;
			A[A[R + 1]] = temp_L_1;
			
			left = temp_L_1 - 1;
			right = temp_R_1 + 1;
		}
		else if (L > 1 && A[L - 1] != 0)
		{
			int temp = A[L - 1];
			A[A[L - 1]] = R;
			A[R] = temp;
			right = R + 1;
			left = temp - 1;
		}
		else if (R != S && A[R + 1] != 0)
		{
			int temp = A[R + 1];
			A[A[R + 1]] = L;
			A[L] = temp;
			right = temp + 1;
			left = L - 1;
		}
		else
		{
			A[R] = L;
			A[L] = R;
			right = R + 1;
			left = L - 1;
		}
	}
	
	int S;
	int A[100001];
};

static int algorithm()
{
	int S, B;

	while (true)
	{
		scanf("%d %d", &S, &B);

		if (S == 0 && B == 0)
			break;

		SegmentManager s1(S);

		int L, R;
		while (B--)
		{
			scanf("%d %d", &L, &R);
			
			int first_alive_at_left;
			int first_alive_at_right;
			s1.Delete(L, R, first_alive_at_left, first_alive_at_right);

			if (first_alive_at_left < 1 || S < first_alive_at_left)
				printf("* ");
			else
				printf("%d ", first_alive_at_left);

			if (first_alive_at_right < 1 || S < first_alive_at_right)
				printf("*\n");
			else
				printf("%d\n", first_alive_at_right);
		}

		printf("-\n");
	}

	return 0;
}

int main12356()
{	
	//extern void UnitTest();
	//UnitTest();
	return algorithm();
}

static void Check(bool expr)
{
	if (!expr)
	{
		int a = 1;
		int b = 2;
		int c = a / b;
		assert(false);
	}

}

///////////////////// UT //////////////////////

static void UnitTest()
{
}

//////////////////// auxiliary functions /////////////////////

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