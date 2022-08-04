#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Time.h"


Time::Time()
{
	time_t t = time(0);
	tm current = *localtime(&t);
	minutes = current.tm_min;
	hours = current.tm_hour;
}

Time::Time(int h, int m)
{
	if (CheckTime(h, m))
	{
		hours = h;
		minutes = m;
	}
}

Time::Time(const Time& T)
{
	hours = T.hours;
	minutes = T.minutes;
}

bool Time::CheckTime(int h, int m)
{
	if (h < 0 || h>23 || m < 0 || m > 59)
	{
		return false;
	}
	return true;
}

int Time::GetHours()
{
	return hours;
}

int Time::GetMinutes()
{
	return minutes;
}

void Time::SetHours(int h)
{
	if (h >= 0 && h <= 23)
		hours = h;
}

void Time::SetMinutes(int m)
{
	if (m >= 0 && m <= 59)
		minutes = m;
}

ostream& operator<<(ostream& os, const Time& T)
{
	os << (T.hours < 10 ? "0" : "") << T.hours << ":" << (T.minutes < 10 ? "0" : "") << T.minutes;
	return os;
}

istream& operator>>(istream& is, Time& T)
{
	char c;
	is >> T.hours >> c >> T.minutes;
	return is;
}

bool Time::operator<(Time t) {
	if (hours == t.hours)
		return minutes < t.minutes;
	return hours < t.hours;
}

bool Time::operator>(Time t) {
	if (hours == t.hours)
		return minutes > t.minutes;
	return hours > t.hours;
}

bool Time::operator==(Time t) {
	return hours == t.hours && minutes == t.minutes;
}

Time InputTime()
{
	Time time;
	cout << "Введите время в формате чч:мм" << endl;
	string str;
	bool correct = true;
	do
	{
		correct = true;
		cin >> str;
		int l = str.length();
		if (l != 5 && l != 4)
		{
			correct = false;
		}
		else
		{
			char h[3];
			char m[3];
			if (l == 5)
			{
				h[0] = str[0];
				h[1] = str[1];
				h[2] = '\0';
				for (int i = 0; i < strlen(h); i++)
				{
					if (h[i] < '0' || h[i]>'9') correct = false;
				}

				m[0] = str[3];
				m[1] = str[4];
				m[2] = '\0';
				for (int i = 0; i < strlen(m); i++)
				{
					if (m[i] < '0' || m[i]>'9') correct = false;
				}
			}
			else
			{
				h[0] = str[0];
				h[1] = '\0';
				for (int i = 0; i < strlen(h); i++)
				{
					if (h[i] < '0' || h[i]>'9') correct = false;
				}

				m[0] = str[2];
				m[1] = str[3];
				m[2] = '\0';
				for (int i = 0; i < strlen(m); i++)
				{
					if (m[i] < '0' || m[i]>'9') correct = false;
				}

			}

			if (correct)
			{
				int hour = atoi(h);
				int minut = atoi(m);

				if (hour < 0 || hour>23)
				{
					correct = false;
				}
				else if (minut < 0 || minut>59)
				{
					correct = false;
				}
				else
				{
					time.SetHours(hour);
					time.SetMinutes(minut);
				}
			}
		}
		if (!correct)
		{
			cout << "Некорректный ввод, попробуйте ещё раз" << endl;
		}
	} while (!correct);

	return time;
}