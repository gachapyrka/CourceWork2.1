#pragma once
#include "master.h"
#include "Date.h"
#include "Time.h"
using namespace filemanager;
Master::Master() :Person()
{
	experience = 0;
	workroom = 0;
}

Master::Master(const Master& obj) :Person(obj)
{
	experience = obj.experience;
	workroom = obj.workroom;
	start = obj.start;
	end = obj.end;
}

void Master::AddRecord()
{
	system("cls");
	Service* arr = NULL;
	FileManager<Service> fmS("services.txt");
	int n = fmS.Load(arr);

	if (n)
	{
		Client* arrPac = NULL;
		FileManager<Client> fmM(CLIENT_FILE);
		int nPac = fmM.Load(arrPac);

		if (!nPac)
		{
			cout << "Нет записей о клиентах" << endl;
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

			Service::ShowServices(arr, n);
			cout << "Выберите номер услуги\n";
			int num = 0;
			while (num <= 0 || num > n)
			{
				num = InputInt();
				if (num <= 0 || num > n)
				{
					cout << "Ошибка ввода." << endl;
				}
			}
			num--;
			arrRec[nRec].SetServ(arr[num]);

			Client::ShowPersons(arrPac, nPac);
			cout << "Выберите номер клиента\n";
			num = 0;
			while (num <= 0 || num > nPac)
			{
				num = InputInt();
				if (num <= 0 || num > nPac)
				{
					cout << "Ошибка ввода." << endl;
				}
			}
			num--;

			arrRec[nRec].SetClient(arrPac[num].GetFIO());

			arrRec[nRec].SetMaster(GetFIO());
			arrRec[nRec].SetWorkroom(GetWorkroom());

			bool correct = false;
			do
			{
				correct = true;
				Date dt = InputDate();
				arrRec[nRec].SetDate(dt);
				Time tm = InputTime();
				arrRec[nRec].SetTime(tm);
				if (tm > GetStart() && tm < GetEnd())
				{
					arrRec[nRec].SetTime(tm);
				}
				else
				{
					correct = false;
					cout << "Укажите время в свои рабочие часы (От " << GetStart() << " до " << GetEnd() << ")" << endl;
				}
				if (!Record::CheckRecordsByPacient(arrRec, nRec, arrRec[nRec]) || !Record::CheckRecordsByDoctor(arrRec, nRec, arrRec[nRec]))
				{
					correct = false;
					cout << "Запись на это время уже есть" << endl;
				}

			} while (!correct);

			nRec++;

			fmR.Save(arrRec, nRec);
			delete[] arrPac;
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
}

void Master::ShowRecords()
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
		if (this->fio == arrRec[i].GetMaster())
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

void Master::DeleteRecord()
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
		if (this->fio == arrRec[i].GetMaster())
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
			cout << "Ошибка ввода" << endl;
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

void Master::EditRecord()
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
		if (this->fio == arrRec[i].GetMaster())
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
	cout << "Введите номер записи для редактирования" << endl;
	while (num<1 || num>nRecInd)
	{
		num = InputInt();
		if (num<1 || num>nRecInd)
		{
			cout << "Ошибка ввода" << endl;
		}
	}
	num--;
	Record temp(arrInd[num]);
	bool work = true;
	while (work)
	{
		cout << "Выберите поле для редактирования" << endl;
		cout << "1.ФИО клиента" << endl;
		cout << "2.Время записи" << endl;
		cout << "3.Выход" << endl;

		char choise;
		cin >> choise;
		system("cls");
		switch (choise)
		{
		case '1':
		{
			Client* arrPac = NULL;
			FileManager<Client> fmP(CLIENT_FILE);
			int nPac = fmP.Load(arrPac);

			Client::ShowPersons(arrPac, nPac);
			cout << "Выберите номер клиента\n";
			do
			{
				int numPac = 0;
				while (numPac <= 0 || numPac > nPac)
				{
					numPac = InputInt();
					if (numPac <= 0 || numPac > nPac)
					{
						cout << "Ошибка ввода" << endl;
					}
				}
				numPac--;

				if (!(temp.GetClient() == arrPac[numPac].GetFIO()))
				{
					temp.SetClient(arrPac[numPac].GetFIO());
					if (!Record::CheckRecordsByPacient(arrRec, nRec, temp))
					{
						cout << "У клиента уже есть запись на это время\n";
					}
				}
				else
				{
					break;
				}

			} while (!Record::CheckRecordsByPacient(arrRec, nRec, temp));
			arrInd[num] = temp;
			delete[] arrPac;
			break;
		}
		case '2':
		{
			cout << "Введите время записи" << endl;
			bool correct = false;
			do
			{
				correct = true;
				Date dt = InputDate();
				temp.SetDate(dt);
				Time tm = InputTime();
				temp.SetTime(tm);
				if (tm > GetStart() && tm < GetEnd())
				{
					arrRec[nRec].SetTime(tm);
				}
				else
				{
					correct = false;
					cout << "Укажите время в свои рабочие часы (От " << GetStart() << " до " << GetEnd() << ")" << endl;
				}
				if (!Record::CheckRecordsByPacient(arrRec, nRec, temp))
				{
					correct = false;
					cout << "Запись на это время уже есть" << endl;
				}

			} while (!correct);
			arrInd[num] = temp;
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

void Master::SearchRecord()
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
		cout << "1.Фамилия клиента" << endl;
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
			cout << "Введите фамилию клиента" << endl;
			cin >> f;
			for (int i = 0; i < nRec; i++)
			{
				if (arrRec[i].GetMaster() == this->GetFIO() && arrRec[i].GetClient().F == f)
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
				if (arrRec[i].GetMaster() == this->GetFIO() && arrRec[i].GetDate() == dt && arrRec[i].GetTime() == tm)
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

void Master::SortRecord()
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
		if (this->fio == arrRec[i].GetMaster())
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
		cout << "1.Фамилия клиента" << endl;
		cout << "2.Время записи" << endl;
		cout << "3.Стоимость услуги" << endl;
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
					if (strcmp(arr[i].GetClient().F.c_str(), arr[j].GetClient().F.c_str()) == 0)
					{
						if (strcmp(arr[i].GetClient().I.c_str(), arr[j].GetClient().I.c_str()) == 0)
						{
							if (strcmp(arr[i].GetClient().O.c_str(), arr[j].GetClient().O.c_str()) == 1)
							{
								swap(arr[i], arr[j]);
							}
						}
						else if (strcmp(arr[i].GetClient().I.c_str(), arr[j].GetClient().I.c_str()) == 1)
						{
							swap(arr[i], arr[j]);
						}
					}
					else if (strcmp(arr[i].GetClient().F.c_str(), arr[j].GetClient().F.c_str()) == 1)
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

void Master::FilterRecord()
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
		if (arrRec[i].GetMaster() == this->GetFIO() && (arrRec[i].GetDate() > dt || arrRec[i].GetDate() == dt) && (arrRec[i].GetDate() < dt1 || arrRec[i].GetDate() == dt1))
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

void Master::EditAccount()
{
	bool work = true;
	Master temp = *this;
	while (work)
	{
		system("cls");
		cout << "Выберите поле для редактирования" << endl;
		cout << "1.ФИО" << endl;
		cout << "2.Стаж" << endl;
		cout << "3.Кабинет" << endl;
		cout << "4.Время начала работы" << endl;
		cout << "5.Время конца работы" << endl;
		cout << "6.Выход" << endl;
		char choise;
		cin >> choise;
		system("cls");
		switch (choise)
		{
		case '1':
		{
			cout << "Введите ФИО" << endl;
			FIO fio = InputFIO();
			Record* arr = NULL;
			FileManager<Record> fmR(RECORD_FILE);
			int nRec = fmR.Load(arr);
			for (int i = 0; i < nRec; i++)
			{
				if (arr[i].GetMaster() == this->GetFIO())
				{
					arr[i].SetMaster(fio);
				}
			}
			SetFIO(fio);
			fmR.Save(arr, nRec);
			delete[] arr;
			break;
		}
		case '2':
		{
			cout << "Введите стаж в годах" << endl;
			int exp = 0;
			while (exp <= 0 || exp > 40)
			{
				exp = InputInt();
				if (exp <= 0 || exp > 40)
				{
					cout << "Стаж может быть от 0 до 40 лет" << endl;
				}
			}
			SetExperience(exp);
			break;
		}
		case '3':
		{
			int room;
			cout << "Введите номер кабиента" << endl;
			do
			{
				room = InputInt();
				if (room <= 0)
				{
					cout << "Некорректный ввод" << endl;
				}
			} while (room <= 0);
			SetWorkRoom(room);
			Record* arr = NULL;
			FileManager<Record> fmR(RECORD_FILE);
			int nRec = fmR.Load(arr);
			for (int i = 0; i < nRec; i++)
			{
				if (arr[i].GetMaster() == this->GetFIO())
				{
					arr[i].SetWorkroom(room);
				}
			}
			fmR.Save(arr, nRec);
			delete[] arr;
			break;
		}
		case '4':
		{
			Time tm = InputTime();
			if (tm < GetEnd())
				SetStart(tm);
			else cout << "Время начала должно быть не позже времени конца рабочеко дня" << endl;
			break;
		}
		case '5':
		{
			Time tm = InputTime();
			if (tm > GetStart())
				SetEnd(tm);
			else cout << "Время конца должно быть не раньше времени начала рабочеко дня" << endl;
			break;
		}
		case '6':
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


	Master* arrDoc = NULL;
	FileManager<Master> fmM(MASTER_FILE);
	int nDoc = fmM.Load(arrDoc);

	for (int i = 0; i < nDoc; i++)
	{
		if (temp.fio == arrDoc[i].fio)
		{
			arrDoc[i] = *this;
		}
	}
	fmM.Save(arrDoc, nDoc);
	delete[] arrDoc;
}

ostream& operator<<(ostream& o, Master obj)
{
	o << obj.fio << " " << obj.experience << " " << obj.workroom << endl;
	o << obj.start << "  " << obj.end << endl;
	o << obj.login << " " << obj.password;
	return o;
}

istream& operator>>(istream& in, Master& obj)
{
	string temp;
	in >> obj.fio >> obj.experience >> obj.workroom;
	in >> obj.start >> obj.end;
	in >> obj.login >> obj.password;
	return in;
}

int Master::GetExperience()
{
	return experience;
}

void Master::SetExperience(int exp)
{
	experience = exp;
}

int Master::GetWorkroom()
{
	return workroom;
}

void Master::SetWorkRoom(int room)
{
	workroom = room;
}

Time& Master::GetStart()
{
	return start;
}

void Master::SetStart(Time tm)
{
	start = tm;
}

Time& Master::GetEnd()
{
	return end;
}

void Master::SetEnd(Time tm)
{
	end = tm;
}

void Master::ShowPersons()
{
	Master* arr = NULL;
	FileManager<Master> fmR(MASTER_FILE);
	int n = fmR.Load(arr);
	Master::ShowPersons(arr, n);
	delete[] arr;
}

void Master::ShowPersons(Master* arr, int n)
{
	if (!n)
	{
		cout << "Записей нет" << endl;
		return;
	}

	cout << "|***|********************|******|*********|***************|" << endl;
	cout << "| № |         ФИО        | Стаж | Кабинет |  Расписание   |" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "|************************|******|*********|***************|" << endl;
		printf("|%3d|%15s %c.%c.|%6d|  %4d   | %02d:%02d - %02d:%02d |\n", i + 1, arr[i].fio.F.c_str(), arr[i].fio.I[0], arr[i].fio.O[0], arr[i].experience, arr[i].workroom, arr[i].start.GetHours(), arr[i].start.GetMinutes(), arr[i].end.GetHours(), arr[i].end.GetMinutes());
	}
	cout << "|***|********************|******|*********|***************|" << endl;
}


void Master::Menu()
{
	bool exit = false;
	while (!exit)
	{
		system("cls");
		cout << "Добро пожаловать ," << GetFIO() << "!\n\n\n";
		cout << "Выберите действие:\n";
		cout << "1.Просмотреть списки клиентов\n";
		cout << "2.Создать запись на стрижку\n";
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
			Client::ShowPersons();
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