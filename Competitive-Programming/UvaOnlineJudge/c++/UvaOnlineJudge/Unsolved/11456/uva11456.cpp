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

#define nil NULL

using namespace std;

struct Range {
	Range(int start, int end) : start(start), end(end) {}
	int start;
	int end;
};

template <class T>
class MyListNode {
public:
	MyListNode(T* value) : value(value), prev(nil), next(nil) {}
	MyListNode* prev;
	MyListNode* next;
	T* value;
	void clear() { delete value; }
};

template <class T>
class MyList {
public:
	MyList() : head(nil), tail(nil), size(0) {}
	MyListNode<T>* head;
	MyListNode<T>* tail;
	int size;
	void insertBefore(MyListNode<T>* insertBeforeThisNode, MyListNode<T>* insertedNode)
	{
		if (insertBeforeThisNode == nil)
		{
			if (tail != nil)
			{
				tail->next = insertedNode;
				insertedNode->prev = tail;
			}
			else
				head = insertedNode;
			tail = insertedNode;			
		}
		else
		{
			if (insertBeforeThisNode->prev == nil)
				head = insertedNode;

			insertedNode->next = insertBeforeThisNode;
			insertedNode->prev = insertBeforeThisNode->prev;
			if (insertBeforeThisNode->prev != nil)
				insertBeforeThisNode->prev->next = insertedNode;
			insertBeforeThisNode->prev = insertedNode;
		}

		size++;
	}

	void erase(MyListNode<T>* erasedNode)
	{
		delete erasedNode->value;
		if (head == erasedNode)
			head = erasedNode->next;
		if (tail == erasedNode)
			tail = erasedNode->prev;

		if (erasedNode->prev != nil)
			erasedNode->prev->next = erasedNode->next;

		if (erasedNode->next != nil)
			erasedNode->next->prev = erasedNode->prev;

		delete erasedNode;
		size--;
	}

	void clear()
	{
		auto it = head;
		auto prev_it = head;
		while (it != nil)
		{
			prev_it = it;
			it = it->next;

			prev_it->clear();
			delete prev_it;
		}
	}
};

template <class T>
MyListNode<T>* myadvance(MyListNode<T>* node, int n)
{
	if (n >= 0)
	{
		for (int i = 0; i < n; i++)
			node = node->next;
	}
	else
	{
		for (int i = 0; i > n; i--)
			node = node->prev;
	}

	return node;
}

void Check(bool b)
{
	if (!b)
	{
		int a = 1;
		int b = 2;
		int c = a / b;
		assert(0);
	}
}

void AddRangeToSizeN(vector<MyList<Range> >& all_range0, Range& range, int n)
{
	while (all_range0.size() < n)
	{
		all_range0.push_back(MyList<Range>());
	}

	MyList<Range>& all_range = all_range0[n-1];

	bool start_in_first = false;
	MyListNode<Range>* start_it = all_range.head;
	MyListNode<Range>* start_it_prev = nil;

	while (start_it != nil && ((Range*)start_it->value)->start < range.start)
	{
		start_it_prev = start_it;
		start_it = start_it->next;
	}

	if (start_it != nil && ((Range*)start_it->value)->start == range.start)
	{
		if (((Range*)start_it->value)->end <= range.end)
			return;
		
		delete start_it->value;
		start_it->value = new Range(range.start, range.end);
	}

	for (auto end_it = start_it; end_it != nil; end_it = myadvance(end_it, 1))
		if (range.end >= ((Range*)end_it->value)->end)
			return;

	all_range.insertBefore(start_it, new MyListNode<Range>(new Range(range.start, range.end)));

	if (start_it_prev != nil)
	{
		for (auto end_it = start_it_prev; end_it != nil && (range.end <= ((Range*)end_it->value)->end);)
		{
			auto end_it2 = end_it->prev;
			all_range.erase(end_it);
			end_it = end_it2;
		}
	}

	
}

void AddNumber(vector<MyList<Range>>& all_range0, int number)
{
	for (int i = all_range0.size() - 1; i >= 0; i--)
	{
		MyList<Range>& all_range = all_range0[i];

		for (auto it = all_range.tail; it != nil; it = myadvance(it, -1))
		{
			if (number < ((Range*)it->value)->start)
			{
				Range r(number, ((Range*)it->value)->end);
				AddRangeToSizeN(all_range0, r, i + 2);
			}
			else
				break;
		}

		all_range = all_range0[i];
		for (auto it = all_range.head; it != nil; it = myadvance(it, 1))
		{
			if (number > ((Range*)it->value)->end)
			{
				Range r(((Range*)it->value)->start, number);
				AddRangeToSizeN(all_range0, r, i + 2);
			}
			else
				break;
		}
	}

	Range r(number, number);
	AddRangeToSizeN(all_range0, r, 1);
}

void CheckRange(vector<MyList<Range> >& all_range)
{
	for (int i = 1; i < all_range.size(); i++)
	{
		MyList<Range>& all_range2 = all_range[i];
		int prev_start = -1;
		int prev_end = -1;
		for (auto it = all_range2.head; it != nil; it = myadvance(it, 1))
		{
			Check(prev_start < ((Range*)it->value)->start);
			prev_start = ((Range*)it->value)->start;
			Check(prev_end < ((Range*)it->value)->end);
			prev_end = ((Range*)it->value)->end;
		}
	}
}

void ClearAllRange(vector<MyList<Range> >& all_range)
{
	for (auto it = all_range.begin(); it != all_range.end(); it++)
		it->clear();

	all_range.clear();
}

/*
void test1()
{
	vector<MyList<Range> > all_range;
	AddRangeToSizeN(all_range, Range(5, 5), 1);
	AddRangeToSizeN(all_range, Range(18, 18), 1);
	AddRangeToSizeN(all_range, Range(6, 6), 1);
	AddRangeToSizeN(all_range, Range(20, 20), 1);
	AddRangeToSizeN(all_range, Range(1, 1), 1);
	Check(all_range[0].size == 5);
	auto it = all_range[0].head;
	Check(((Range*)it->value)->start == 1);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 5);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 6);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 18);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 20);

	ClearAllRange(all_range);
}

void test2()
{
	vector<MyList<Range> > all_range;
	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(1, 2), 2);
	Check(all_range[1].size == 4);
	CheckRange(all_range);

	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(40, 80), 2);
	Check(all_range[1].size == 4);
	CheckRange(all_range);

	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(40, 41), 2);
	Check(all_range[1].size == 1);

	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(11, 49), 2);
	Check(all_range[1].size == 3);
	auto it = all_range[1].head;
	Check(((Range*)it->value)->start == 11);
	CheckRange(all_range);

	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(21, 49), 2);
	Check(all_range[1].size == 2);
	it = all_range[1].head;
	Check(((Range*)it->value)->start == 21);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 30);
	CheckRange(all_range);

	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(31, 69), 2);
	Check(all_range[1].size == 3);
	it = all_range[1].head;
	it = myadvance(it,2);
	Check(((Range*)it->value)->start == 31);
	CheckRange(all_range);

	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(31, 51), 2);
	Check(all_range[1].size == 2);
	it = all_range[1].head;
	Check(((Range*)it->value)->start == 10);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 31);
	CheckRange(all_range);

	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(9, 51), 2);
	Check(all_range[1].size == 3);
	it = all_range[1].head;
	Check(((Range*)it->value)->start == 10);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 20);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 30);

	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(21, 81), 2);
	Check(all_range[1].size == 3);
	it = all_range[1].head;
	Check(((Range*)it->value)->start == 10);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 20);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 30);

	ClearAllRange(all_range);
	AddRangeToSizeN(all_range, Range(10, 50), 2);
	AddRangeToSizeN(all_range, Range(20, 60), 2);
	AddRangeToSizeN(all_range, Range(30, 70), 2);
	AddRangeToSizeN(all_range, Range(11, 61), 2);
	Check(all_range[1].size == 3);
	it = all_range[1].head;
	Check(((Range*)it->value)->start == 10);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 20);
	it = myadvance(it, 1);
	Check(((Range*)it->value)->start == 30);

	ClearAllRange(all_range);
}

void test3()
{
	vector<MyList<Range> > all_range;
	AddNumber(all_range, 5);
	AddNumber(all_range, 18);
	Check(all_range[1].size == 1);
	AddNumber(all_range, 10);
	AddNumber(all_range, 6);
	AddNumber(all_range, 3);

	ClearAllRange(all_range);
}

void test()
{
	test1();
	test2();
	test3();
}
*/

void algorithm()
{
	int test_count;
	cin >> test_count;

	while (test_count--)
	{
		vector<MyList<Range> > all_range;

		int number_count;
		cin >> number_count;
		while (number_count--)
		{
			int number;
			cin >> number;
			AddNumber(all_range, number);
		}

		cout << all_range.size() << endl;

		ClearAllRange(all_range);
	}
}

int main()
{
	//test();
	algorithm();

	return 0;
}