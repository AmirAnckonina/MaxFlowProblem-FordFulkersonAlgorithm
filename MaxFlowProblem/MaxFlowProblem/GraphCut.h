#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

struct GraphCut
{
	list<int> Sgrp;
	list<int> Tgrp;
	int cutFlow = 0;

	void PrintCut();
};

