#pragma once
#include <iostream>
#include <fstream>
using namespace std;

struct Service
{
	Service();
	Service(const Service&);
	string name;
	double cost;
	static void ShowServices(Service*&, int&);
	friend istream& operator>>(istream& in, Service& o);
	friend ostream& operator<<(ostream& in, const Service& o);
	Service& operator=(const Service&);
};