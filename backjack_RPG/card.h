#pragma once
#include <iostream>
class card{
private:
	int enamy_card;
	int hero_card;
	int card[52];
	int enamy_score = 0;
	int hero_score = 0;
	int a, i, x, j, k, c = 0;
	char yes_no;
	bool same;

public:
	int winer;
	int pick_card();
};

