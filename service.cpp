#include "service.h"
#include <string>

Service::Service()
{
	name = "---";
	cost = 0;
}

Service::Service(const Service& obj)
{
	name = obj.name;
	cost = obj.cost;
}

Service& Service::operator=(const Service& obj)
{
	name = obj.name;
	cost = obj.cost;
	return *this;
}

void Service::ShowServices(Service*& arr, int& n)
{
	system("cls");
	if (n == 0)
	{
		cout << "Нет ни одной услуги" << endl;
		return;
	}
	cout << "|****************************************************|" << endl;
	cout << "| № |          Название услуги          | Цена, руб. |" << endl;
	cout << "|****************************************************|" << endl;
	for (int i = 0; i < n; i++)
	{
		printf("|%3d|%35s|  %6.2lf    |\n", i + 1, arr[i].name.c_str(), arr[i].cost);
		cout << "|****************************************************|" << endl;
	}
}

istream& operator>>(istream& in, Service& o)
{
	in >> o.cost;
	getline(in, o.name);
	getline(in, o.name);

	return in;
}

ostream& operator<<(ostream& in,const Service& o)
{
	in << o.cost << endl << o.name << endl;
	return in;
}

ostream& operator<<(ostream& in, Service o)
{
	in << o.cost << endl << o.name << endl;
	return in;
}