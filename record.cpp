#pragma once
#include "record.h"

Record::Record()
{
	workroom = 0;
}

Record::Record(const Record& o)
{
	time = o.time;
	date = o.date;
	client = o.client;
	master = o.master;
	workroom = o.workroom;
	serv.name = o.serv.name;
	serv.cost = o.serv.cost;
}

Record& Record::operator=(const Record& o)
{
	time = o.time;
	date = o.date;
	client = o.client;
	master = o.master;
	workroom = o.workroom;
	serv.name = o.serv.name;
	serv.cost = o.serv.cost;

	return *this;
}

Record::Record(FIO& doc, FIO& pac, Date dat, Time tim, string comp, int room)
{
	master = doc;
	client = pac;
	date = dat;
	time = tim;
	workroom = room;
}

Time Record::GetTime()
{
	return time;
}

void Record::SetTime(Time t)
{
	time = t;
}

Date Record::GetDate()
{
	return date;
}

void Record::SetDate(Date d)
{
	date = d;
}

FIO Record::GetMaster()
{
	return master;
}

void Record::SetMaster(FIO doc)
{
	master = doc;
}

FIO Record::GetClient()
{
	return client;
}

void Record::SetClient(FIO pac)
{
	client = pac;
}

Service Record::GetServ()
{
	return serv;
}

void Record::SetServ(Service s)
{
	serv = s;
}

int Record::GetWorkroom()
{
	return workroom;
}

void Record::SetWorkroom(int room)
{
	workroom = room;
}

bool Record::CheckRecordsByDoctor(Record* arr, int n, Record& o)
{
	bool result = true;
	for (int i = 0; i < n; i++)
	{
		if (arr[i].date == o.date && arr[i].time == o.time && arr[i].master.F == o.master.F && arr[i].master.I == o.master.I && arr[i].master.O == o.master.O)
		{
			result = false;
		}

	}
	return result;
}

bool Record::CheckRecordsByPacient(Record* arr, int n, Record& o)
{
	bool result = true;
	for (int i = 0; i < n; i++)
	{
		if (arr[i].date == o.date && arr[i].time == o.time && arr[i].client.F == o.client.F && arr[i].client.I == o.client.I && arr[i].client.O == o.client.O)
		{
			result = false;
		}
	}
	return result;
}

void Record::ShowRecords(Record* arr, int n)
{
	if (n)
	{
		cout << "|***|*******************|*******************|*********|***********************************|*****************|******************|\n";
		cout << "| № |    ФИО мастера    |    ФИО клиента    | Кабинет |          Название услуги          | Стоимость, руб. |   Время записи   |\n";
		cout << "|***|*******************|*******************|*********|***********************************|*****************|******************|\n";
		for (int i = 0; i < n; i++)
		{
			printf("|%3d|%14s %c.%c.|%14s %c.%c.|  %4d   |%35s|      %6.2lf     | %02d.%02d.%04d %02d:%02d |\n", i + 1, arr[i].master.F.c_str(), arr[i].master.I[0], arr[i].master.O[0], arr[i].client.F.c_str(), arr[i].client.I[0], arr[i].client.O[0], arr[i].workroom, arr[i].serv.name.c_str(), arr[i].serv.cost, arr[i].date.GetDay(), arr[i].date.GetMonth(), arr[i].date.GetYear(), arr[i].time.GetHours(), arr[i].time.GetMinutes());
			cout << "|***|*******************|*******************|*********|***********************************|*****************|******************|\n";
		}
	}
	else
	{
		cout << "Записей нет" << endl;
	}
}

istream& operator>>(istream& i, Record& a)
{
	i >> a.date >> a.time >> a.master >> a.client;
	i >> a.serv.cost;
	getline(i, a.serv.name);
	getline(i, a.serv.name);
	i >> a.workroom;
	return i;
}

ostream& operator<<(ostream& o, const Record& a)
{
	o << a.date << " " << a.time << " " << a.master << " " << a.client << " \n" << a.serv.cost << endl << a.serv.name << "\n " << a.workroom;
	return o;
}