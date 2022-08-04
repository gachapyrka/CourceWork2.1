#pragma once
#include <iostream>
#include <string>

using namespace std;

struct FIO
{
	string F;
	string I;
	string O;

	FIO()
	{
		F = "Unnamed";
		I = F;
		O = F;
	}

	bool operator==(FIO o)
	{
		return F == o.F && I == o.I && O == o.O;
	}
};

ostream& operator<<(ostream& o, const FIO& a);
istream& operator>>(istream& i, FIO& a);

FIO InputFIO();

bool proverka(char p_str);