#pragma once
#include "client.h"
using namespace filemanager;
Client::Client() :Person()
{
	age = 0;
}

Client::Client(const Client& o) : Person(o)
{
	age = o.age;
}

void Client::AddRecord()
{
	system("cls");
	Service* arr = NULL;
	FileManager<Service> fmS("services.txt");
	int n = fmS.Load(arr);

	if (n)
	{
		system("cls");
		Master* arrDoc = NULL;
		FileManager<Master> fmM(MASTER_FILE);
		int nDoc = fmM.Load(arrDoc);

		if (!nDoc)
		{
			cout << "Нет записей о парикмахерах" << endl;
			system("pause");
		}
		else
		{
			Record* arrRec = NULL;
			FileManager<Record> fmR(RECORD_FILE);
			int nRec = fmR.Load(arrRec);

			if (!arrRec)
			{
				arrRec = new Record[2];
			}

			Master::ShowPersons(arrDoc, nDoc);
			cout << "Выберите номер парикмахера\n";
			int num = 0;
			while (num <= 0 || num > nDoc)
			{
				num = InputInt();
				if (num <= 0 || num > nDoc)
				{
					cout << "Ошибка ввода" << endl;
				}
			}
			num--;

			arrRec[nRec].SetMaster(arrDoc[num].GetFIO());
			arrRec[nRec].SetWorkroom(arrDoc[num].GetWorkroom());

			arrRec[nRec].SetClient(this->GetFIO());

			Service::ShowServices(arr, n);
			cout << "Выберите номер услуги\n";
			int nnum = 0;
			while (nnum <= 0 || nnum > n)
			{
				nnum = InputInt();
				if (nnum <= 0 || nnum > n)
				{
					cout << "Ошибка ввода" << endl;
				}
			}
			nnum--;
			arrRec[nRec].SetServ(arr[nnum]);

			cout << "Введите время записи" << endl;
			do
			{
				Date dt = InputDate();
				arrRec[nRec].SetDate(dt);
				bool correct = false;
				while (!correct)
				{
					Time tm = InputTime();
					if (tm > arrDoc[num].GetStart() && tm < arrDoc[num].GetEnd())
					{
						arrRec[nRec].SetTime(tm);
						correct = true;
					}
					else
					{
						cout << "Парикмахер работает с " << arrDoc[num].GetStart() << " до " << arrDoc[num].GetEnd() << endl;
					}
				}
				if (!Record::CheckRecordsByDoctor(arrRec, nRec, arrRec[nRec]))
				{
					cout << "На это время запись уже есть" << endl;
				}

			} while (!Record::CheckRecordsByDoctor(arrRec, nRec, arrRec[nRec]));

			nRec++;

			fmR.Save(arrRec, nRec);
			delete[] arrDoc;
			delete[] arrRec;
		}

	}

	else
	{
		cout << "Нет ни одной записи о предоставляемых услугах" << endl;
		system("pause");
	}



	fmS.Save(arr, n);
	delete[]arr;

	return;
}

void Client::ShowRecords()
{
	system("cls");
	Record* arrRec = NULL;
	FileManager<Record> fmR(RECORD_FILE);
	int nRec = fmR.Load(arrRec);

	if (!nRec)
	{
		cout << "Записей нет\n";
		system("pause");
		return;
	}

	Record* arr = new Record[nRec];
	int nRecInd = 0;
	for (int i = 0; i < nRec; i++)
	{
		if (this->fio == arrRec[i].GetClient())
		{
			arr[nRecInd] = arrRec[i];
			nRecInd++;
		}
	}
	if (!nRecInd)
	{
		cout << "Записей нет\n";
		system("pause");
		delete[] arrRec;
		delete[] arr;
		return;
	}

	Record::ShowRecords(arr, nRecInd);
	delete[] arrRec;
	delete[] arr;
	return;
}

void Client::DeleteRecord()
{
	system("cls");
	Record* arrRec = NULL;
	FileManager<Record> fmR(RECORD_FILE);
	int nRec = fmR.Load(arrRec);

	if (!nRec)
	{
		cout << "Записей нет\n";
		system("pause");
		return;
	}

	Record* arrInd = new Record[nRec];
	int nRecInd = 0;

	Record* arrOther = new Record[nRec];
	int nRecOther = 0;

	for (int i = 0; i < nRec; i++)
	{
		if (this->fio == arrRec[i].GetClient())
		{
			arrInd[nRecInd] = arrRec[i];
			nRecInd++;
		}
		else
		{
			arrOther[nRecOther] = arrRec[i];
			nRecOther++;
		}
	}
	if (!nRecInd)
	{
		cout << "Записей нет\n";
		system("pause");
		delete[] arrRec;
		delete[] arrInd;
		delete[] arrOther;
		return;
	}

	Record::ShowRecords(arrInd, nRecInd);

	int num = 0;
	cout << "Введите номер записи для удаления" << endl;
	while (num<1 || num>nRecInd)
	{
		num = InputInt();
		if (num<1 || num>nRecInd)
		{
			cout << "Ошибка" << endl;
		}
	}
	num--;
	for (int i = num; i < nRecInd - 1; i++)
	{
		arrInd[i] = arrInd[i + 1];
	}
	nRecInd--;

	int index = 0;
	for (int i = 0; i < nRecOther; i++)
	{
		arrRec[index] = arrOther[i];
		index++;
	}
	for (int i = 0; i < nRecInd; i++)
	{
		arrRec[index] = arrInd[i];
		index++;
	}
	fmR.Save(arrRec, index);

	delete[] arrRec;
	delete[] arrInd;
	delete[] arrOther;
}

void Client::EditRecord()
{
	system("cls");
	Record* arrRec = NULL;
	FileManager<Record> fmR(RECORD_FILE);
	int nRec = fmR.Load(arrRec);

	if (!nRec)
	{
		cout << "Записей нет\n";
		system("pause");
		return;
	}

	Record* arrInd = new Record[nRec];
	int nRecInd = 0;

	Record* arrOther = new Record[nRec];
	int nRecOther = 0;

	for (int i = 0; i < nRec; i++)
	{
		if (this->fio == arrRec[i].GetClient())
		{
			arrInd[nRecInd] = arrRec[i];
			nRecInd++;
		}
		else
		{
			arrOther[nRecOther] = arrRec[i];
			nRecOther++;
		}
	}
	if (!nRecInd)
	{
		cout << "Записей нет\n";
		system("pause");
		delete[] arrRec;
		delete[] arrInd;
		delete[] arrOther;
		return;
	}

	Record::ShowRecords(arrInd, nRecInd);

	int num = 0;
	cout << "Выберите номер записи" << endl;
	while (num<1 || num>nRecInd)
	{
		num = InputInt();
		if (num<1 || num>nRecInd)
		{
			cout << "Ошибка ввода" << endl;
		}
	}
	num--;
	Record temp(arrRec[num]);
	bool work = true;
	while (work)
	{
		cout << "Выберите поле для редактирования" << endl;
		cout << "1.ФИО парикмахера" << endl;
		cout << "2.Услуга" << endl;
		cout << "3.Время записи" << endl;
		cout << "4.Выход" << endl;

		char choise;
		cin >> choise;
		system("cls");
		switch (choise)
		{
		case '1':
		{
			Master* arrDoc = NULL;
			FileManager<Master> fmM(MASTER_FILE);
			int nDoc = fmM.Load(arrDoc);

			Master::ShowPersons(arrDoc, nDoc);
			cout << "Выберите парикмахера\n";
			bool correct = false;
			correct = true;
			int numDoc = 0;
			while (numDoc <= 0 || numDoc > nDoc)
			{
				numDoc = InputInt();
				if (numDoc <= 0 || numDoc > nDoc)
				{
					cout << "Ошибка ввода" << endl;
				}
			}
			numDoc--;
			if (arrDoc[numDoc].GetFIO() == temp.GetMaster())
			{
				correct = true;
				break;
			}


			if (!Record::CheckRecordsByDoctor(arrRec, nRec, temp))
			{
				cout << "В это время парикмахер уже занят\n";
				correct = false;
			}
			else if (arrDoc[numDoc].GetStart() > temp.GetTime() || arrDoc[numDoc].GetEnd() < temp.GetTime())
			{
				cout << "В это время парикмахер не работает" << endl;
				correct = false;
			}
			if (correct)
			{
				temp.SetMaster(arrDoc[numDoc].GetFIO());
				temp.SetWorkroom(arrDoc[numDoc].GetWorkroom());
			}
			arrInd[num] = temp;
			delete[] arrDoc;
			break;
		}
		case '2':
		{
			system("cls");
			Service* arr = NULL;
			int n = 0;
			ifstream in("services.txt", ios_base::in);
			in >> n;
			arr = new Service[n + 2];
			if (n)
			{
				for (int i = 0; i < n; i++)
				{
					getline(in, arr[i].name);
					getline(in, arr[i].name);
					in >> arr[i].cost;
				}
			}
			in.close();

			if (n)
			{
				Service::ShowServices(arr, n);
				cout << "Выберите номер услуги\n";
				int nnum = 0;
				while (nnum <= 0 || nnum > n)
				{
					nnum = InputInt();
					if (nnum <= 0 || nnum > n)
					{
						cout << "Ошибка ввода." << endl;
					}
				}
				nnum--;
				temp.SetServ(arr[nnum]);
				arrInd[num] = temp;
			}
			else
			{
				cout << "На данный момент предоставляемых услуг нет" << endl;
			}

			ofstream o("services.txt", ios_base::trunc);
			o << n << endl;
			for (int i = 0; i < n; i++)
			{
				o << arr[i].name << endl << arr[i].cost << endl;
			}
			delete[]arr;
			o.close();
			break;
		}
		case '3':
		{
			Master* arrDoc = NULL;
			FileManager<Master> fmM(MASTER_FILE);
			int nDoc = fmM.Load(arrDoc);
			int index = 0;
			for (int i = 0; i < nDoc; i++)
			{
				if (arrDoc[i].GetFIO() == temp.GetMaster())
				{
					index = i;
				}
			}
			cout << "Введите время записи" << endl;
			do
			{
				Date dt = InputDate();
				temp.SetDate(dt);
				bool correct = false;
				while (!correct)
				{
					Time tm = InputTime();
					if (tm > arrDoc[index].GetStart() && tm < arrDoc[index].GetEnd())
					{
						temp.SetTime(tm);
						correct = true;
					}
					else
					{
						cout << "Парикмахер работает с " << arrDoc[index].GetStart() << " до " << arrDoc[index].GetEnd() << endl;
					}
				}
				if (!Record::CheckRecordsByDoctor(arrRec, nRec, temp))
				{
					cout << "Запись на это время уже есть" << endl;
				}

			} while (!Record::CheckRecordsByDoctor(arrRec, nRec, temp));
			arrInd[num] = temp;
			delete[] arrDoc;
			break;
		}
		case '4':
		{
			work = false;
			break;
		}
		default:
		{
			cout << "Ошибка ввода" << endl;
			system("pause");
		}
		}
	}

	int index = 0;
	for (int i = 0; i < nRecOther; i++)
	{
		arrRec[index] = arrOther[i];
		index++;
	}
	for (int i = 0; i < nRecInd; i++)
	{
		arrRec[index] = arrInd[i];
		index++;
	}
	fmR.Save(arrRec, nRec);

	delete[] arrRec;
	delete[] arrInd;
	delete[] arrOther;
}

void Client::SearchRecord()
{
	system("cls");
	Record* arrRec = NULL;
	FileManager<Record> fmR(RECORD_FILE);
	int nRec = fmR.Load(arrRec);

	if (!nRec)
	{
		cout << "Записей нет\n";
		system("pause");
		return;
	}
	bool work = true;
	while (work)
	{
		system("cls");
		Record* arr = new Record[nRec];
		int nRecFound = 0;
		cout << "Выберите поле для поиска" << endl;
		cout << "1.Фамилия парикмахера" << endl;
		cout << "2.Время записи" << endl;
		cout << "3.Выход" << endl;
		char choise;
		cin >> choise;
		system("cls");
		switch (choise)
		{
		case '1':
		{
			string f;
			cout << "Введите фамилию парикмахера" << endl;
			cin >> f;
			for (int i = 0; i < nRec; i++)
			{
				if (arrRec[i].GetClient() == this->GetFIO() && arrRec[i].GetMaster().F == f)
				{
					arr[nRecFound] = arrRec[i];
					nRecFound++;
				}
			}
			break;
		}
		case '2':
		{
			Date dt = InputDate();
			Time tm = InputTime();

			for (int i = 0; i < nRec; i++)
			{
				if (arrRec[i].GetClient() == this->GetFIO() && arrRec[i].GetDate() == dt && arrRec[i].GetTime() == tm)
				{
					arr[nRecFound] = arrRec[i];
					nRecFound++;
				}
			}
			break;
		}
		case '3':
		{
			work = false;
			nRecFound = -1;
			break;
		}
		default:
			cout << "Ошибка ввода" << endl;
			system("pause");
			nRecFound = -1;
			break;
		}
		system("cls");
		if (nRecFound == 0)
		{
			cout << "Записей не найдено" << endl;
			system("pause");
		}
		else if (nRecFound > 0)
		{
			Record::ShowRecords(arr, nRecFound);
			system("pause");
		}
		delete[] arr;

	}
	delete[] arrRec;
	return;
}

void Client::SortRecord()
{
	system("cls");
	Record* arrRec = NULL;
	FileManager<Record> fmR(RECORD_FILE);
	int nRec = fmR.Load(arrRec);

	if (!nRec)
	{
		cout << "Записей нет\n";
		system("pause");
		return;
	}

	Record* arr = new Record[nRec];
	int nRecInd = 0;
	for (int i = 0; i < nRec; i++)
	{
		if (this->fio == arrRec[i].GetClient())
		{
			arr[nRecInd] = arrRec[i];
			nRecInd++;
		}
	}
	if (!nRecInd)
	{
		cout << "Записей нет\n";
		system("pause");
		delete[] arrRec;
		delete[] arr;
		return;
	}

	bool work = true;
	while (work)
	{
		system("cls");
		cout << "Выберите поле для сортировки" << endl;
		cout << "1.ФИО парикмахера" << endl;
		cout << "2.Время записи" << endl;
		cout << "3.Стоимость записи" << endl;
		cout << "4.Выход" << endl;
		char choise;
		cin >> choise;
		system("cls");
		switch (choise)
		{
		case '1':
		{
			for (int i = 0; i < nRecInd; i++)
			{
				for (int j = i + 1; j < nRecInd; j++)
				{
					if (strcmp(arr[i].GetMaster().F.c_str(), arr[j].GetMaster().F.c_str()) == 0)
					{
						if (strcmp(arr[i].GetMaster().I.c_str(), arr[j].GetMaster().I.c_str()) == 0)
						{
							if (strcmp(arr[i].GetMaster().O.c_str(), arr[j].GetMaster().O.c_str()) == 1)
							{
								swap(arr[i], arr[j]);
							}
						}
						else if (strcmp(arr[i].GetMaster().I.c_str(), arr[j].GetMaster().I.c_str()) == 1)
						{
							swap(arr[i], arr[j]);
						}
					}
					else if (strcmp(arr[i].GetMaster().F.c_str(), arr[j].GetMaster().F.c_str()) == 1)
					{
						swap(arr[i], arr[j]);
					}
				}
			}
			Record::ShowRecords(arr, nRecInd);
			system("pause");
			break;
		}
		case '2':
		{
			for (int i = 0; i < nRecInd; i++)
			{
				for (int j = i + 1; j < nRecInd; j++)
				{
					if (arr[i].GetDate() == arr[j].GetDate())
					{
						if (arr[i].GetTime() > arr[j].GetTime())
						{
							swap(arr[i], arr[j]);
						}
					}
					else if (arr[i].GetDate() > arr[j].GetDate())
					{
						swap(arr[i], arr[j]);
					}
				}
			}
			Record::ShowRecords(arr, nRecInd);
			system("pause");
			break;
		}
		case '3':
		{
			for (int i = 0; i < nRecInd; i++)
			{
				for (int j = i + 1; j < nRecInd; j++)
				{
					if (arr[i].GetServ().cost > arr[j].GetServ().cost)
					{
						swap(arr[i], arr[j]);
					}
				}
			}
			Record::ShowRecords(arr, nRecInd);
			system("pause");
			break;
		}
		case '4':
		{
			work = false;
			break;
		}
		default:
		{
			cout << "Ошибка ввода" << endl;
			system("pause");
			break;
		}
		}
	}
	delete[] arrRec;
	delete[] arr;
	return;
}

void Client::FilterRecord()
{
	system("cls");
	Record* arrRec = NULL;
	FileManager<Record> fmR(RECORD_FILE);
	int nRec = fmR.Load(arrRec);

	if (!nRec)
	{
		cout << "Записей нет\n";
		system("pause");
		return;
	}

	system("cls");
	Record* arr = new Record[nRec];
	int nRecFound = 0;
	cout << "Введите диапазон дат" << endl;
	cout << "От:" << endl;
	Date dt = InputDate();
	cout << "До:" << endl;
	Date dt1 = InputDate();
	for (int i = 0; i < nRec; i++)
	{
		if (arrRec[i].GetClient() == this->GetFIO() && (arrRec[i].GetDate() > dt || arrRec[i].GetDate() == dt) && (arrRec[i].GetDate() < dt1 || arrRec[i].GetDate() == dt1))
		{
			arr[nRecFound] = arrRec[i];
			nRecFound++;
		}
	}
	system("cls");
	if (nRecFound == 0)
	{
		cout << "Записей не найдено" << endl;
		system("pause");
	}
	else if (nRecFound > 0)
	{
		Record::ShowRecords(arr, nRecFound);
		system("pause");
	}
	delete[] arr;
	delete[] arrRec;
	return;
}

void Client::EditAccount()
{
	bool work = true;
	Client temp = *this;
	while (work)
	{
		system("cls");
		cout << "Выберите поле для редактирования" << endl;
		cout << "1.ФИО" << endl;
		cout << "2.Возраст" << endl;
		cout << "3.Выход" << endl;
		char choise;
		cin >> choise;
		system("cls");
		switch (choise)
		{
		case '1':
		{
			FIO fio = InputFIO();
			Record* arr = NULL;
			FileManager<Record> fmR(RECORD_FILE);
			int nRec = fmR.Load(arr);
			for (int i = 0; i < nRec; i++)
			{
				if (arr[i].GetClient() == this->GetFIO())
				{
					arr[i].SetClient(fio);
				}
			}
			SetFIO(fio);
			fmR.Save(arr, nRec);
			delete[] arr;
			break;
		}
		case '2':
		{
			cout << "Введите возраст" << endl;
			int age = 0;
			while (age < 14 || age>100)
			{
				age = InputInt();
				if (age < 14 || age>100)
				{
					cout << "Возраст должен быть от 14 до 100" << endl;
				}
			}
			SetAge(age);
			break;
		}
		case '3':
		{
			work = false;
			break;
		}
		default:
		{
			cout << "Ошибка ввода" << endl;
			system("pause");
		}
		}
	}
	Client* arrPac = NULL;
	FileManager<Client> fmM(CLIENT_FILE);
	int nPac = fmM.Load(arrPac);

	for (int i = 0; i < nPac; i++)
	{
		if (arrPac[i].fio == temp.fio)
		{
			arrPac[i] = *this;
		}
	}
	fmM.Save(arrPac, nPac);
}

ostream& operator<<(ostream& o, Client obj)
{
	o << obj.fio << " " << obj.age << endl;
	o << obj.login << " " << obj.password << endl;
	return o;
}

istream& operator>>(istream& in, Client& obj)
{
	in >> obj.fio >> obj.age >> obj.login >> obj.password;
	return in;
}

void Client::SetAge(int a)
{
	age = a;
}

int Client::GetAge()
{
	return age;
}

Client::~Client()
{

}

void Client::ShowPersons()
{
	Client* arr = NULL;
	FileManager<Client> fmM(CLIENT_FILE);
	int n = fmM.Load(arr);
	Client::ShowPersons(arr, n);
	delete[] arr;
}

void Client::ShowPersons(Client* arr, int n)
{
	if (!n)
	{
		cout << "Записей нет" << endl;
		return;
	}

	cout << "|************************|*********|" << endl;
	cout << "| № |         ФИО        | Возраст |" << endl;
	cout << "|************************|*********|" << endl;
	for (int i = 0; i < n; i++)
	{
		printf("|%3d|%15s %c.%c.| %3d лет |\n", i + 1, arr[i].fio.F.c_str(), arr[i].fio.I[0], arr[i].fio.O[0], arr[i].age);
		cout << "|************************|*********|" << endl;
	}
}
void Client::Menu()
{
	bool exit = false;
	while (!exit)
	{
		system("cls");
		cout << "Добро пожаловать ," << GetFIO() << "!\n\n\n";
		cout << "Выберите действие:" << endl;
		cout << "1.Просмотреть списки парикмахеров\n";
		cout << "2.Записаться на прием\n";
		cout << "3.Просмотреть список записей\n";
		cout << "4.Удалить запись на стрижку\n";
		cout << "5.Редактировать запись на стрижку\n";
		cout << "6.Искать запись на стрижку\n";
		cout << "7.Сортировать записи\n";
		cout << "8.Фильтровать записи\n";
		cout << "9.Изменить информацию аккаунта\n";
		cout << "0.Выход\n";
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
			AddRecord();
			break;
		}
		case '3':
		{
			ShowRecords();
			system("pause");
			break;
		}
		case '4':
		{
			DeleteRecord();
			break;
		}
		case '5':
		{
			EditRecord();
			break;
		}
		case '6':
		{
			SearchRecord();
			break;
		}
		case '7':
		{
			SortRecord();
			break;
		}
		case '8':
		{
			FilterRecord();
			break;
		}
		case '9':
		{
			EditAccount();
			break;
		}
		case '0':
		{
			exit = true;
			break;
		}
		default:
			cout << "Ошибка!\n";
			system("pause");
			break;
		}
	}
}
