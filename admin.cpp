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
	cout << "Введите логин\n";
	cin >> login;
	cout << "Введите пароль\n";
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
		cout << "1.Показать список услуг" << endl;
		cout << "2.Добавить услугу" << endl;
		cout << "3.Редактировать услугу" << endl;
		cout << "4.Удалить услугу" << endl;
		cout << "5.Сохранить и выйти" << endl;
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
			cout << "Ошибка.Повторите ввод" << endl;
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

	cout << "Введите название услуги" << endl;
	getline(cin, arr[n].name);
	getline(cin, arr[n].name);

	cout << "Введите стоимость в рублях" << endl;
	do
	{
		arr[n].cost = InputDouble();
		if (arr[n].cost <= 0)
		{
			cout << "Стоимость должна быть больше 0" << endl;
		}
	} while (arr[n].cost <= 0);

	n++;
}

void Admin::EditService(Service*& arr, int& n)
{
	system("cls");
	if (!n)
	{
		cout << "Нет ни одной услуги" << endl;
		return;
	}
	Service::ShowServices(arr, n);
	int choise = -1;
	cout << "Выберите номер услуги" << endl;
	while (choise<1 || choise>n)
	{
		choise = InputInt();
		if (choise<1 || choise>n)
		{
			cout << "Некорректный ввод" << endl;
		}
	}
	choise--;
	bool work = true;
	while (work)
	{
		system("cls");
		Service::ShowServices(arr, n);
		cout << "1.Название услуги" << endl;
		cout << "2.Стоимость" << endl;
		cout << "3.Выход" << endl;
		char ch;
		cin >> ch;
		switch (ch)
		{
		case '1':
		{
			cout << "Введите название услуги" << endl;
			getline(cin, arr[choise].name);
			getline(cin, arr[choise].name);
			break;
		}
		case '2':
		{
			cout << "Введите стоимость в рублях" << endl;
			do
			{
				arr[choise].cost = InputDouble();
				if (arr[choise].cost <= 0)
				{
					cout << "Стоимость должна быть больше 0" << endl;
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
			cout << "Ошибка.Повторите ввод" << endl;
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
		cout << "Нет ни одной услуги" << endl;
		system("pause");
		return;
	}
	Service::ShowServices(arr, n);
	int choise = -1;
	cout << "Выберите номер услуги" << endl;
	while (choise<1 || choise>n)
	{
		choise = InputInt();
		if (choise<1 || choise>n)
		{
			cout << "Некорректный ввод" << endl;
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
		cout << "Добро пожаловать ," << GetLogin() << "!\n\n\n";
		cout << "Выберите действие:" << endl;
		cout << "1.Просмотреть списки парикмахеров\n";
		cout << "2.Просмотреть списки клиентов\n";
		cout << "3.Добавить аккаунт парикмахера\n";
		cout << "4.Добавить аккаунт клиента\n";
		cout << "5.Удалить аккаунт парикмахера\n";
		cout << "6.Удалить аккаунт клиента\n";
		cout << "7.Показать 3 самых востребованных парикмахера\n";
		cout << "8.Меню управления услугами\n";
		cout << "9.Выход\n";
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
			cout << "Введите логин" << endl;
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
						cout << "Такой логин уже существует" << endl;
						correct = false;
						break;
					}
				}
			} while (!correct);

			arr[n].SetLogin(str);
			cout << "Введите пароль" << endl;
			cin >> str;
			arr[n].SetPass(str);

			cout << "Введите ФИО" << endl;
			FIO fio = InputFIO();
			arr[n].SetFIO(fio);

			int exp = -1;
			cout << "Введите стаж в годах" << endl;
			while (exp < 0 || exp>40)
			{
				exp = InputInt();
				if (exp < 0 || exp>40)
				{
					cout << "Стаж должен быть от 0 до 40 лет" << endl;
				}
			}
			arr[n].SetExperience(exp);
			int r;
			cout << "Введите кабинет" << endl;
			do
			{
				r = InputInt();
				if (r <= 0)
				{
					cout << "Некорректный ввод" << endl;
				}
			} while (r <= 0);
			arr[n].SetWorkRoom(r);


			cout << "Введите время начала периода приема (до 12:00)" << endl;
			Time tm;
			do
			{
				tm = InputTime();
			} while (tm > Time(12, 00));

			arr[n].SetStart(tm);

			cout << "Введите время конца периода приема (после 12:00)" << endl;
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
			cout << "Введите логин" << endl;
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
						cout << "Такой логин уже существует" << endl;
						correct = false;
						break;
					}
				}
			} while (!correct);

			arr[n].SetLogin(str);
			cout << "Введите пароль" << endl;
			cin >> str;
			arr[n].SetPass(str);


			cout << "Введите ФИО" << endl;
			FIO fio = InputFIO();
			arr[n].SetFIO(fio);

			cout << "Введите возраст" << endl;
			int age = 0;
			while (age < 14 || age>100)
			{
				age = InputInt();
				if (age < 14 || age>100)
				{
					cout << "Возраст должен быть от 14 до 100 лет" << endl;
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
				cout << "Нет аккаунтов" << endl;
				system("pause");
				break;
			}

			Master::ShowPersons(arr, n);

			int num = 0;
			cout << "Выберите номер удаляемого аккаунта" << endl;
			while (num<1 || num>n)
			{
				num = InputInt();
				if (num<1 || num>n)
				{
					cout << "Такого номера аккаунта нет" << endl;
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
				cout << "Нет аккаунтов" << endl;
				system("pause");
				break;
			}

			Client::ShowPersons(arr, n);

			int num = 0;
			cout << "Выберите номер удаляемого аккаунта" << endl;
			while (num<1 || num>n)
			{
				num = InputInt();
				if (num<1 || num>n)
				{
					cout << "Такого номера аккаунта нет" << endl;
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
				cout << "Нет аккаунтов" << endl;
				system("pause");
				break;
			}
			if (n < 3)
			{
				cout << "Не достаточно врачей" << endl;
				system("pause");
				break;
			}

			Record* ar = NULL;
			FileManager<Record> fmA(RECORD_FILE);
			int nr = fmA.Load(ar);
			if (!nr)
			{
				cout << "Не достаточно записей" << endl;
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
			cout << "| № |         ФИО        | Стаж | Кабинет |  Расписание   |Кол-во записей|" << endl;
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
			cout << "Ошибка ввода, повторите ещё раз" << endl;
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