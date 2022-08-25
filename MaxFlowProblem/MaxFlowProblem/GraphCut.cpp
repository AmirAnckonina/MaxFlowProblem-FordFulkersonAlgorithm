#include "GraphCut.h"

void GraphCut::PrintCut()
{
	cout << "S = ";
	string SgrpStr, TgrpStr;
	list<int>::iterator itr;

	for (itr = Sgrp.begin(); itr != Sgrp.end(); itr++)
	{
		SgrpStr += (to_string(*itr) + (", "));
		
	}

	SgrpStr[SgrpStr.length() - 2] = '.';
	cout << SgrpStr;

	cout << "T = ";
	for (itr = Tgrp.begin(); itr != Tgrp.end(); itr++)
	{
		TgrpStr += (to_string(*itr) + (", "));
	}

	TgrpStr[TgrpStr.length() - 2] = '.';
	cout << TgrpStr;
}
