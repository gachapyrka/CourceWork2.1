#pragma once
#include <iostream>
#include <ostream>

using namespace std;

class Date {
	int day;
	int month;
	int year;

public:

	Date();
	Date(int d, int m, int y);
	Date(const Date& D);

	bool CheckDate(int d, int m, int y);

	int GetDay();
	int GetMonth();
	int GetYear();

	void SetDay(int d);
	void SetMonth(int m);
	void SetYear(int y);

	friend ostream& operator<<(ostream& os, const Date& D);
	friend istream& operator>>(istream& is, Date& D);

	bool operator<(Date d);
	bool operator>(Date d);
	bool operator==(Date d);
	bool operator>=(Date d);
	bool operator<=(Date d);

};

Date InputDate();
