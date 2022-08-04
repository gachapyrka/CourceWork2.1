#pragma once
#include "person.h"
#include "record.h"
#include "master.h"
#include "menu.h"

class Client : public Person
{
	int age;

public:
	Client();
	Client(const Client&);

	void AddRecord();
	void ShowRecords();
	void DeleteRecord();
	void EditRecord();
	void SearchRecord();
	void SortRecord();
	void FilterRecord();
	void EditAccount();
	virtual void Menu();

	void SetAge(int);
	int GetAge();

	static void ShowPersons();
	static void ShowPersons(Client*, int);

	friend ostream& operator<<(ostream& o, Client obj);
	friend istream& operator>>(istream& i, Client& obj);

	~Client();
};
