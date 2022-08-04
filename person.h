#pragma once
#include <string>
#include "account.h"
#include "record.h"
#include "input.h"
#include "FIO.h"
class Person : public Account
{
protected:
	FIO fio;
public:
	Person() :Account() {};
	virtual void AddRecord() = 0;
	virtual void ShowRecords() = 0;
	virtual void DeleteRecord() = 0;
	virtual void EditRecord() = 0;
	virtual void SearchRecord() = 0;
	virtual void SortRecord() = 0;
	virtual void FilterRecord() = 0;
	virtual void EditAccount() = 0;
	virtual void Menu() = 0;

	void SetFIO(FIO _fio) { fio = _fio; }
	FIO GetFIO() { return fio; }
};
