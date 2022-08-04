#pragma once
#include "person.h"
#include "Date.h"
#include "Time.h"
#include "FIO.h"
#include "service.h"
#include <fstream>

class Record
{
	Time time;
	Date date;
	FIO client;
	FIO master;
	Service serv;
	int workroom;

public:
	Record();
	Record(const Record&);
	Record(FIO&, FIO&, Date, Time, string, int);

	Time GetTime();
	void SetTime(Time);

	Date GetDate();
	void SetDate(Date);

	FIO GetMaster();
	void SetMaster(FIO);

	FIO GetClient();
	void SetClient(FIO);

	Service GetServ();
	void SetServ(Service);

	int GetWorkroom();
	void SetWorkroom(int);

	static bool CheckRecordsByDoctor(Record*, int, Record&);
	static bool CheckRecordsByPacient(Record*, int, Record&);

	static void ShowRecords(Record*, int);

	friend istream& operator>>(istream&, Record&);
	friend ostream& operator<<(ostream&, const Record&);

	Record& operator=(const Record&);
};