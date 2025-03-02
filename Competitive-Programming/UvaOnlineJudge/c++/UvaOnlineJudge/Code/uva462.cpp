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

using namespace std;

bool all_cards[52];
int card_count_in_suit[4];

static int rule_1_to_4(bool* all_cards, int* card_count_in_suit)
{
	int ret = 0;

	for (int i = 0; i < 4; i++)
	{
		int base = i * 13;
		if (all_cards[base + 12])
		{
			ret += 4;
		}
			
		if (all_cards[base + 11])
		{
			ret += 3;
			if (card_count_in_suit[i] == 1)
				ret -= 1;
		}
			
		if (all_cards[base + 10])
		{
			ret += 2;
			if (card_count_in_suit[i] <= 2)
				ret -= 1;
		}
		if (all_cards[base + 9])
		{
			ret += 1;
			if (card_count_in_suit[i] <= 3)
				ret -= 1;
		}
	}

	return ret;
}

static int rule_5_to_7(bool* all_cards, int* card_count_in_suit)
{
	int ret = 0;

	for (int i = 0; i < 4; i++)
	{
		if (card_count_in_suit[i] == 2)
			ret += 1;
		if (card_count_in_suit[i] == 1)
			ret += 2;
		if (card_count_in_suit[i] == 0)
			ret += 2;
	}

	return ret;
}

static bool suit_all_stop(bool* all_cards, int* card_count_in_suit)
{
	for (int i = 0; i < 4; i++)
	{
		int base = i * 13;
		if (all_cards[base + 12])
			continue;
		if (all_cards[base + 11] && card_count_in_suit[i] >= 2)
			continue;
		if (all_cards[base + 10] && card_count_in_suit[i] >= 3)
			continue;

		return false;
	}

	return true;
}

int main462()
{
	while (true)
	{
		for (int j = 0; j < 52; j++)
			all_cards[j] = false;
		for (int j = 0; j < 4; j++)
			card_count_in_suit[j] = 0;

		for (int i = 0; i < 13; i++)
		{
			char card[3];
			if (scanf("%s", card) != 1)
				return 0;

			int card_int = 0;
			if (card[0] == 'A')
				card_int += 12;
			else if (card[0] == 'K')
				card_int += 11;
			else if (card[0] == 'Q')
				card_int += 10;
			else if (card[0] == 'J')
				card_int += 9;
			else
				card_int += card[0] - '2';

			if (card[1] == 'H')
			{
				card_count_in_suit[1]++;
				card_int += 13;
			}

			else if (card[1] == 'D')
			{
				card_count_in_suit[2]++;
				card_int += 26;
			}
			else if (card[1] == 'C')
			{
				card_count_in_suit[3]++;
				card_int += 39;
			}
			else
			{
				card_count_in_suit[0]++;
			}

			all_cards[card_int] = true;
		}

		int point = rule_1_to_4(all_cards, card_count_in_suit);
		int point_5_to_7 = rule_5_to_7(all_cards, card_count_in_suit);
		point += point_5_to_7;

		if (point < 14)
		{
			printf("PASS\n");
		}
		else
		{
			if (point - point_5_to_7 >= 16 && suit_all_stop(all_cards, card_count_in_suit))
			{
				printf("BID NO-TRUMP\n");
			}
			else
			{
				int max_suit = 0;
				int max_count_in_suit = -1;
				for (int i = 0; i < 4; i++)
				{
					if (card_count_in_suit[i] > max_count_in_suit)
					{
						max_count_in_suit = card_count_in_suit[i];
						max_suit = i;
					}
				}

				printf("BID ");
				if (max_suit == 0)
					printf("S\n");
				else if (max_suit == 1)
					printf("H\n");
				else if (max_suit == 2)
					printf("D\n");
				else
					printf("C\n");
			}
		}
	}


	return 0;
}