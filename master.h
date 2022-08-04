#pragma once
#include "person.h"
#include "client.h"
#include "menu.h"


class Master : public Person
{
	int experience;
	int workroom;
	Time start;
	Time end;

public:
	Master();
	Master(const Master& obj);

	int GetExperience();
	void SetExperience(int);

	int GetWorkroom();
	void SetWorkRoom(int);

	Time& GetStart();
	void SetStart(Time);

	Time& GetEnd();
	void SetEnd(Time);

	void AddRecord();
	void ShowRecords();
	void DeleteRecord();
	void EditRecord();
	void SearchRecord();
	void SortRecord();
	void FilterRecord();
	void EditAccount();
	virtual void Menu();

	static void ShowPersons();
	static void ShowPersons(Master*, int);

	friend ostream& operator<<(ostream& o, Master obj);
	friend istream& operator>>(istream& i, Master& obj);
};