#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "date.h"

Date::Date() {
	time_t t = time(0);
	tm current = *localtime(&t);
	day = current.tm_mday;
	month = current.tm_mon + 1;
	year = current.tm_year + 1900;
}

Date::Date(int d, int m, int y)
{
	if (CheckDate(d, m, y))
	{
		day = d;
		month = m;
		year = y;
	}
}

Date::Date(const Date& D)
{
	day = D.day;
	month = D.month;
	year = D.year;
}

bool Date::CheckDate(int d, int m, int y)
{
	if (d < 1 || d>31 || m < 1 || m > 12)
	{
		return false;
	}
	else if (y != 2022)
	{
		cout << "Запись ведется только на 2022 год" << endl;
		return false;
	}
	else if (d > 28 && m == 2)
	{
		return false;
	}
	return true;
}

int Date::GetDay()
{
	return day;
}

int Date::GetMonth()
{
	return month;
}

int Date::GetYear()
{
	return year;
}

void Date::SetDay(int d)
{
	if (d >= 1 && d <= 31)
		day = d;
}

void Date::SetMonth(int m)
{
	if (m >= 1 && m <= 12)
		month = m;
}

void Date::SetYear(int y)
{
	year = y;
}

ostream& operator<<(ostream& os, const Date& D)
{
	os << (D.day < 10 ? "0" : "") << D.day << "." << (D.month < 10 ? "0" : "") << D.month << "." << D.year;
	return os;
}

istream& operator>>(istream& is, Date& D)
{
	char c;
	is >> D.day >> c >> D.month >> c >> D.year;
	return is;
}

bool Date::operator<(Date d) {
	if (year == d.year) {
		if (month == d.month) {
			return day < d.day;
		}
		return month < d.month;
	}
	return year < d.year;
}

bool Date::operator>(Date d) {
	if (year == d.year) {
		if (month == d.month) {
			return day > d.day;
		}
		return month > d.month;
	}
	return year > d.year;
}

bool Date::operator==(Date d)
{
	return year == d.year && month == d.month && day == d.day;
}

bool Date::operator>=(Date d)
{
	return *this > d || *this == d;
}

bool Date::operator<=(Date d)
{
	return *this < d || *this == d;
}

Date InputDate()
{
	Date date;
	cout << "Введите дату в формате дд.мм.гггг" << endl;
	string str;
	bool correct = true;
	do
	{
		correct = true;
		cin >> str;
		if (str.length() != 10)
		{
			correct = false;
		}
		else
		{
			char d[3];
			d[0] = str[0];
			d[1] = str[1];
			d[2] = '\0';
			for (int i = 0; i < strlen(d); i++)
			{
				if (d[i] < '0' || d[i]>'9') correct = false;
			}

			char m[3];
			m[0] = str[3];
			m[1] = str[4];
			m[2] = '\0';
			for (int i = 0; i < strlen(m); i++)
			{
				if (m[i] < '0' || m[i]>'9') correct = false;
			}

			char y[5];
			y[0] = str[6];
			y[1] = str[7];
			y[2] = str[8];
			y[3] = str[9];
			y[4] = '\0';
			for (int i = 0; i < strlen(y); i++)
			{
				if (y[i] < '0' || y[i]>'9') correct = false;
			}

			if (correct)
			{
				int day = atoi(d);
				int month = atoi(m);
				int year = atoi(y);

				if (day < 1 || day>31)
				{
					correct = false;
				}
				else if (month < 1 || month>12)
				{
					correct = false;
				}
				else if (year != 2022)
				{
					correct = false;
					cout << "Запись ведется только на 2022 год" << endl;
				}
				else if (month == 2 && day > 28)
				{
					correct = false;
					cout << "В феврале 28 дней" << endl;
				}
				else
				{
					date.SetDay(day);
					date.SetMonth(month);
					date.SetYear(year);
				}
			}
		}
		if (!correct)
		{
			cout << "Дата введена некорректно, попробуйте ещё раз" << endl;
		}
	} while (!correct);

	return date;
}