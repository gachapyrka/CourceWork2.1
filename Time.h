#pragma once
#pragma once

#include <iostream>
#include <ostream>
#include <ctime>

using namespace std;

class Time {
	int hours;
	int minutes;

public:

	Time();
	Time(int, int);
	Time(const Time&);

	bool CheckTime(int, int);

	int GetHours();
	int GetMinutes();

	void SetHours(int);
	void SetMinutes(int);

	bool operator<(Time);
	bool operator>(Time);
	bool operator==(Time);


	friend ostream& operator<<(ostream&, const Time&);
	friend istream& operator>>(istream&, Time&);



};

Time InputTime();