#pragma once
#include "admin.h"
#include "master.h"
#include "client.h"
#include "record.h"
#include <fstream>
#include <string>
using namespace filemanager;

string Admin::defaultLogin = "111";
string Admin::defaultPassword = "111";

Admin::Admin()
{
	login = defaultLogin;
	password = Encrypt(defaultPassword);
}

void Admin::Init()
{
	cout << "������� �����\n";
	cin >> login;
	cout << "������� ������\n";
	cin >> password;
	password = Encrypt(password);
	FileManager<Admin> fm(ADMIN_FILE);
	Admin* a=this;
	fm.Save(a, 1);
}

void Admin::MenuService()
{
	Service* arr = NULL;
	int n = 0;
	ifstream in("services.txt", ios_base::in);
	in >> n;
	arr = new Service[n + 2];
	if (n)
	{
		for (int i = 0; i < n; i++)
		{
			in >> arr[i].cost;
			getline(in, arr[i].name);
			getline(in, arr[i].name);
		}
	}
	in.close();

	bool work = true;
	while (work)
	{
		system("cls");
		cout << "1.�������� ������ �����" << endl;
		cout << "2.�������� ������" << endl;
		cout << "3.������������� ������" << endl;
		cout << "4.������� ������" << endl;
		cout << "5.��������� � �����" << endl;
		char ch;
		cin >> ch;
		switch (ch)
		{
		case '1':
		{
			Service::ShowServices(arr, n);
			system("pause");
			break;
		}
		case '2':
		{
			AddService(arr, n);
			break;
		}
		case '3':
		{
			EditService(arr, n);
			break;
		}
		case '4':
		{
			DelService(arr, n);

			break;
		}
		case '5':
		{
			work = false;
			break;
		}
		default:
		{
			system("cls");
			cout << "������.��������� ����" << endl;
			system("pause");
			break;
		}
		}
	}

	ofstream o("services.txt", ios_base::trunc);
	o << n << endl;
	for (int i = 0; i < n; i++)
	{
		o << arr[i].cost << endl << arr[i].name << endl;
	}
	delete[]arr;
	o.close();
}

void Admin::AddService(Service*& arr, int& n)
{
	system("cls");
	Service* arrn = new Service[n + 3];
	for (int i = 0; i < n; i++)
	{
		arrn[i].name = arr[i].name;
		arrn[i].cost = arr[i].cost;
	}
	delete[] arr;
	arr = arrn;

	cout << "������� �������� ������" << endl;
	getline(cin, arr[n].name);
	getline(cin, arr[n].name);

	cout << "������� ��������� � ������" << endl;
	do
	{
		arr[n].cost = InputDouble();
		if (arr[n].cost <= 0)
		{
			cout << "��������� ������ ���� ������ 0" << endl;
		}
	} while (arr[n].cost <= 0);

	n++;
}

void Admin::EditService(Service*& arr, int& n)
{
	system("cls");
	if (!n)
	{
		cout << "��� �� ����� ������" << endl;
		return;
	}
	Service::ShowServices(arr, n);
	int choise = -1;
	cout << "�������� ����� ������" << endl;
	while (choise<1 || choise>n)
	{
		choise = InputInt();
		if (choise<1 || choise>n)
		{
			cout << "������������ ����" << endl;
		}
	}
	choise--;
	bool work = true;
	while (work)
	{
		system("cls");
		Service::ShowServices(arr, n);
		cout << "1.�������� ������" << endl;
		cout << "2.���������" << endl;
		cout << "3.�����" << endl;
		char ch;
		cin >> ch;
		switch (ch)
		{
		case '1':
		{
			cout << "������� �������� ������" << endl;
			getline(cin, arr[choise].name);
			getline(cin, arr[choise].name);
			break;
		}
		case '2':
		{
			cout << "������� ��������� � ������" << endl;
			do
			{
				arr[choise].cost = InputDouble();
				if (arr[choise].cost <= 0)
				{
					cout << "��������� ������ ���� ������ 0" << endl;
				}
			} while (arr[choise].cost <= 0);

			break;
		}
		case '3':
		{
			work = false;
			break;
		}
		default:
		{
			system("cls");
			cout << "������.��������� ����" << endl;
			system("pause");
			break;
		}
		}
	}
}

void Admin::DelService(Service*& arr, int& n)
{
	system("cls");
	if (!n)
	{
		cout << "��� �� ����� ������" << endl;
		system("pause");
		return;
	}
	Service::ShowServices(arr, n);
	int choise = -1;
	cout << "�������� ����� ������" << endl;
	while (choise<1 || choise>n)
	{
		choise = InputInt();
		if (choise<1 || choise>n)
		{
			cout << "������������ ����" << endl;
		}
	}
	choise--;
	for (int i = choise; i < n - 1; i++)
	{
		arr[i].name = arr[i + 1].name;
		arr[i].cost = arr[i + 1].cost;
	}
	n--;
}

void Admin::Menu()
{

	bool exit = false;
	while (!exit)
	{
		Account** a = NULL;
		int na = 0;
		Admin admin(*this);

		Master* arrD = NULL;
		FileManager<Master> fmM(MASTER_FILE);
		int nD = fmM.Load(arrD);
		Client* arrP = NULL;
		FileManager<Client> fmP(CLIENT_FILE);
		int nP = fmP.Load(arrP);

		a = new Account*[2 + nD + nP];
		a[0] = &admin;
		for (int i = 1; i < nD + 1; i++)
		{
			a[i] = arrD + i - 1;
		}
		for (int i = 1 + nD; i < 1 + nD + nP; i++)
		{
			a[i] = arrP + i - 1 - nD;
		}
		
		na = 1 + nD + nP;

		system("cls");
		cout << "����� ���������� ," << GetLogin() << "!\n\n\n";
		cout << "�������� ��������:" << endl;
		cout << "1.����������� ������ ������������\n";
		cout << "2.����������� ������ ��������\n";
		cout << "3.�������� ������� �����������\n";
		cout << "4.�������� ������� �������\n";
		cout << "5.������� ������� �����������\n";
		cout << "6.������� ������� �������\n";
		cout << "7.�������� 3 ����� �������������� �����������\n";
		cout << "8.���� ���������� ��������\n";
		cout << "9.�����\n";
		char choise;
		cin >> choise;
		system("cls");
		switch (choise)
		{
		case '1':
		{
			Master::ShowPersons();
			system("pause");
			break;
		}
		case '2':
		{
			Client::ShowPersons();
			system("pause");
			break;
		}
		case '3':
		{
			Master* arr = NULL;
			FileManager<Master> fmR(MASTER_FILE);
			int n = fmR.Load(arr);
			if (!n)
			{
				arr = new Master[2];
			}
			cout << "������� �����" << endl;
			bool correct = false;
			string str;
			do
			{
				correct = true;
				cin >> str;
				for (int i = 0; i < na; i++)
				{
					if (str == a[i]->GetLogin())
					{
						cout << "����� ����� ��� ����������" << endl;
						correct = false;
						break;
					}
				}
			} while (!correct);

			arr[n].SetLogin(str);
			cout << "������� ������" << endl;
			cin >> str;
			arr[n].SetPass(str);

			cout << "������� ���" << endl;
			FIO fio = InputFIO();
			arr[n].SetFIO(fio);

			int exp = -1;
			cout << "������� ���� � �����" << endl;
			while (exp < 0 || exp>40)
			{
				exp = InputInt();
				if (exp < 0 || exp>40)
				{
					cout << "���� ������ ���� �� 0 �� 40 ���" << endl;
				}
			}
			arr[n].SetExperience(exp);
			int r;
			cout << "������� �������" << endl;
			do
			{
				r = InputInt();
				if (r <= 0)
				{
					cout << "������������ ����" << endl;
				}
			} while (r <= 0);
			arr[n].SetWorkRoom(r);


			cout << "������� ����� ������ ������� ������ (�� 12:00)" << endl;
			Time tm;
			do
			{
				tm = InputTime();
			} while (tm > Time(12, 00));

			arr[n].SetStart(tm);

			cout << "������� ����� ����� ������� ������ (����� 12:00)" << endl;
			do
			{
				tm = InputTime();
			} while (tm < Time(12, 00));

			arr[n].SetEnd(tm);

			n++;

			fmR.Save(arr, n);
			delete[] arr;
			break;
		}
		case '4':
		{
			Client* arr = NULL;
			FileManager<Client> fmR(CLIENT_FILE);
			int n = fmR.Load(arr);
			if (!n)
			{
				arr = new Client[2];
			}
			cout << "������� �����" << endl;
			bool correct = false;
			string str;
			do
			{
				correct = true;
				cin >> str;
				for (int i = 0; i < na; i++)
				{
					if (str == a[i]->GetLogin())
					{
						cout << "����� ����� ��� ����������" << endl;
						correct = false;
						break;
					}
				}
			} while (!correct);

			arr[n].SetLogin(str);
			cout << "������� ������" << endl;
			cin >> str;
			arr[n].SetPass(str);


			cout << "������� ���" << endl;
			FIO fio = InputFIO();
			arr[n].SetFIO(fio);

			cout << "������� �������" << endl;
			int age = 0;
			while (age < 14 || age>100)
			{
				age = InputInt();
				if (age < 14 || age>100)
				{
					cout << "������� ������ ���� �� 14 �� 100 ���" << endl;
				}
			}
			arr[n].SetAge(age);

			n++;

			fmR.Save(arr, n);
			delete[] arr;

			break;
		}
		case '5':
		{
			Master* arr = NULL;
			FileManager<Master> fmR(MASTER_FILE);
			int n = fmR.Load(arr);
			if (!n)
			{
				cout << "��� ���������" << endl;
				system("pause");
				break;
			}

			Master::ShowPersons(arr, n);

			int num = 0;
			cout << "�������� ����� ���������� ��������" << endl;
			while (num<1 || num>n)
			{
				num = InputInt();
				if (num<1 || num>n)
				{
					cout << "������ ������ �������� ���" << endl;
				}
			}
			num--;

			FIO fio = arr[num].GetFIO();

			for (int i = num; i < n - 1; i++)
			{
				arr[i] = arr[i + 1];
			}
			n--;
			fmR.Save(arr, n);
			delete[] arr;

			Record* ar = NULL;
			FileManager<Record> fmA(RECORD_FILE);
			n = fmA.Load(ar);
			if (n)
			{
				for (int i = 0; i < n; i++)
				{
					if (ar[i].GetMaster() == fio)
					{
						for (int j = i; j < n - 1; j++)
						{
							ar[j] = ar[j + 1];
						}
						i--;
						n--;
					}
				}
			}
			fmA.Save(ar, n);
			break;
		}
		case '6':
		{
			Client* arr = NULL;
			FileManager<Client> fmR(CLIENT_FILE);
			int n = fmR.Load(arr);
			if (!n)
			{
				cout << "��� ���������" << endl;
				system("pause");
				break;
			}

			Client::ShowPersons(arr, n);

			int num = 0;
			cout << "�������� ����� ���������� ��������" << endl;
			while (num<1 || num>n)
			{
				num = InputInt();
				if (num<1 || num>n)
				{
					cout << "������ ������ �������� ���" << endl;
				}
			}
			num--;

			FIO fio = arr[num].GetFIO();

			for (int i = num; i < n - 1; i++)
			{
				arr[i] = arr[i + 1];
			}
			n--;
			fmR.Save(arr, n);
			delete[] arr;

			Record* ar = NULL;
			FileManager<Record> fmA(RECORD_FILE);
			n = fmA.Load(ar);
			if (n)
			{
				for (int i = 0; i < n; i++)
				{
					if (ar[i].GetClient() == fio)
					{
						for (int j = i; j < n - 1; j++)
						{
							ar[j] = ar[j + 1];
						}
						i--;
						n--;
					}
				}
			}
			fmA.Save(ar, n);
			break;
		}
		case '7':
		{
			Master* arr = NULL;
			FileManager<Master> fmR(MASTER_FILE);
			int n = fmR.Load(arr);
			if (!n)
			{
				cout << "��� ���������" << endl;
				system("pause");
				break;
			}
			if (n < 3)
			{
				cout << "�� ���������� ������" << endl;
				system("pause");
				break;
			}

			Record* ar = NULL;
			FileManager<Record> fmA(RECORD_FILE);
			int nr = fmA.Load(ar);
			if (!nr)
			{
				cout << "�� ���������� �������" << endl;
				system("pause");
				delete[] arr;
				break;
			}
			int* rating = new int[n];
			for (int i = 0; i < n; i++) rating[i] = 0;

			for (int i = 0; i < nr; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (arr[j].GetFIO() == ar[i].GetMaster())
					{
						rating[j]++;
					}
				}
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = i; j < n; j++)
				{
					if (rating[j] > rating[i])
					{
						swap(arr[i], arr[j]);
						swap(rating[i], rating[j]);
					}
				}
			}
			cout << "|***|********************|******|*********|***************|**************|" << endl;
			cout << "| � |         ���        | ���� | ������� |  ����������   |���-�� �������|" << endl;
			cout << "|***|********************|******|*********|***************|**************|" << endl;
			for (int i = 0; i < 3; i++)
			{
				printf("|%3d|%15s %c.%c.|%6d|  %4d   | %02d:%02d - %02d:%02d |     %4d     |\n", i + 1, arr[i].GetFIO().F.c_str(), arr[i].GetFIO().I[0], arr[i].GetFIO().O[0], arr[i].GetExperience(), arr[i].GetWorkroom(), arr[i].GetStart().GetHours(), arr[i].GetStart().GetMinutes(), arr[i].GetEnd().GetHours(), arr[i].GetEnd().GetMinutes(), rating[i]);
				cout << "|***|********************|******|*********|***************|**************|" << endl;
			}
			system("pause");
			delete[] arr;
			delete[] ar;
			delete[] rating;
			break;
		}
		case '8':
		{
			MenuService();
			break;
		}
		case '9':
		{
			exit = true;
			break;
		}
		default:
		{
			cout << "������ �����, ��������� ��� ���" << endl;
			system("pause");
		}
		}
		if (a)
			delete[] a;
		if (arrD)
			delete[] arrD;
		if (arrP)
			delete[] arrP;
	}
}

ostream& operator<<(ostream& o, Admin obj)
{
	o << obj.login << " " << obj.password << endl;
	return o;
}

istream& operator>>(istream& in, Admin& obj)
{
	in >> obj.login >> obj.password;
	return in;
}