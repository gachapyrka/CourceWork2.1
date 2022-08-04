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
			cout << "��� ������� � ��������" << endl;
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
			cout << "�������� ����� ������\n";
			int num = 0;
			while (num <= 0 || num > n)
			{
				num = InputInt();
				if (num <= 0 || num > n)
				{
					cout << "������ �����." << endl;
				}
			}
			num--;
			arrRec[nRec].SetServ(arr[num]);

			Client::ShowPersons(arrPac, nPac);
			cout << "�������� ����� �������\n";
			num = 0;
			while (num <= 0 || num > nPac)
			{
				num = InputInt();
				if (num <= 0 || num > nPac)
				{
					cout << "������ �����." << endl;
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
					cout << "������� ����� � ���� ������� ���� (�� " << GetStart() << " �� " << GetEnd() << ")" << endl;
				}
				if (!Record::CheckRecordsByPacient(arrRec, nRec, arrRec[nRec]) || !Record::CheckRecordsByDoctor(arrRec, nRec, arrRec[nRec]))
				{
					correct = false;
					cout << "������ �� ��� ����� ��� ����" << endl;
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
		cout << "��� �� ����� ������ � ��������������� �������" << endl;
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
		cout << "������� ���\n";
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
		cout << "������� ���\n";
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
		cout << "������� ���\n";
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
		cout << "������� ���\n";
		system("pause");
		delete[] arrRec;
		delete[] arrInd;
		delete[] arrOther;
		return;
	}

	Record::ShowRecords(arrInd, nRecInd);

	int num = 0;
	cout << "������� ����� ������ ��� ��������" << endl;
	while (num<1 || num>nRecInd)
	{
		num = InputInt();
		if (num<1 || num>nRecInd)
		{
			cout << "������ �����" << endl;
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
		cout << "������� ���\n";
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
		cout << "������� ���\n";
		system("pause");
		delete[] arrRec;
		delete[] arrInd;
		delete[] arrOther;
		return;
	}

	Record::ShowRecords(arrInd, nRecInd);

	int num = 0;
	cout << "������� ����� ������ ��� ��������������" << endl;
	while (num<1 || num>nRecInd)
	{
		num = InputInt();
		if (num<1 || num>nRecInd)
		{
			cout << "������ �����" << endl;
		}
	}
	num--;
	Record temp(arrInd[num]);
	bool work = true;
	while (work)
	{
		cout << "�������� ���� ��� ��������������" << endl;
		cout << "1.��� �������" << endl;
		cout << "2.����� ������" << endl;
		cout << "3.�����" << endl;

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
			cout << "�������� ����� �������\n";
			do
			{
				int numPac = 0;
				while (numPac <= 0 || numPac > nPac)
				{
					numPac = InputInt();
					if (numPac <= 0 || numPac > nPac)
					{
						cout << "������ �����" << endl;
					}
				}
				numPac--;

				if (!(temp.GetClient() == arrPac[numPac].GetFIO()))
				{
					temp.SetClient(arrPac[numPac].GetFIO());
					if (!Record::CheckRecordsByPacient(arrRec, nRec, temp))
					{
						cout << "� ������� ��� ���� ������ �� ��� �����\n";
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
			cout << "������� ����� ������" << endl;
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
					cout << "������� ����� � ���� ������� ���� (�� " << GetStart() << " �� " << GetEnd() << ")" << endl;
				}
				if (!Record::CheckRecordsByPacient(arrRec, nRec, temp))
				{
					correct = false;
					cout << "������ �� ��� ����� ��� ����" << endl;
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
			cout << "������ �����" << endl;
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
		cout << "������� ���\n";
		system("pause");
		return;
	}
	bool work = true;
	while (work)
	{
		system("cls");
		Record* arr = new Record[nRec];
		int nRecFound = 0;
		cout << "�������� ���� ��� ������" << endl;
		cout << "1.������� �������" << endl;
		cout << "2.����� ������" << endl;
		cout << "3.�����" << endl;
		char choise;
		cin >> choise;
		system("cls");
		switch (choise)
		{
		case '1':
		{
			string f;
			cout << "������� ������� �������" << endl;
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
			cout << "������ �����" << endl;
			system("pause");
			nRecFound = -1;
			break;
		}
		system("cls");
		if (nRecFound == 0)
		{
			cout << "������� �� �������" << endl;
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
		cout << "������� ���\n";
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
		cout << "������� ���\n";
		system("pause");
		delete[] arrRec;
		delete[] arr;
		return;
	}

	bool work = true;
	while (work)
	{
		system("cls");
		cout << "�������� ���� ��� ����������" << endl;
		cout << "1.������� �������" << endl;
		cout << "2.����� ������" << endl;
		cout << "3.��������� ������" << endl;
		cout << "4.�����" << endl;
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
			cout << "������ �����" << endl;
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
		cout << "������� ���\n";
		system("pause");
		return;
	}

	system("cls");
	Record* arr = new Record[nRec];
	int nRecFound = 0;
	cout << "������� �������� ���" << endl;
	cout << "��:" << endl;
	Date dt = InputDate();
	cout << "��:" << endl;
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
		cout << "������� �� �������" << endl;
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
		cout << "�������� ���� ��� ��������������" << endl;
		cout << "1.���" << endl;
		cout << "2.����" << endl;
		cout << "3.�������" << endl;
		cout << "4.����� ������ ������" << endl;
		cout << "5.����� ����� ������" << endl;
		cout << "6.�����" << endl;
		char choise;
		cin >> choise;
		system("cls");
		switch (choise)
		{
		case '1':
		{
			cout << "������� ���" << endl;
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
			cout << "������� ���� � �����" << endl;
			int exp = 0;
			while (exp <= 0 || exp > 40)
			{
				exp = InputInt();
				if (exp <= 0 || exp > 40)
				{
					cout << "���� ����� ���� �� 0 �� 40 ���" << endl;
				}
			}
			SetExperience(exp);
			break;
		}
		case '3':
		{
			int room;
			cout << "������� ����� ��������" << endl;
			do
			{
				room = InputInt();
				if (room <= 0)
				{
					cout << "������������ ����" << endl;
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
			else cout << "����� ������ ������ ���� �� ����� ������� ����� �������� ���" << endl;
			break;
		}
		case '5':
		{
			Time tm = InputTime();
			if (tm > GetStart())
				SetEnd(tm);
			else cout << "����� ����� ������ ���� �� ������ ������� ������ �������� ���" << endl;
			break;
		}
		case '6':
		{
			work = false;
			break;
		}
		default:
		{
			cout << "������ �����" << endl;
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
		cout << "������� ���" << endl;
		return;
	}

	cout << "|***|********************|******|*********|***************|" << endl;
	cout << "| � |         ���        | ���� | ������� |  ����������   |" << endl;
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
		cout << "����� ���������� ," << GetFIO() << "!\n\n\n";
		cout << "�������� ��������:\n";
		cout << "1.����������� ������ ��������\n";
		cout << "2.������� ������ �� �������\n";
		cout << "3.����������� ������ �������\n";
		cout << "4.������� ������ �� �������\n";
		cout << "5.������������� ������ �� �������\n";
		cout << "6.������ ������ �� �������\n";
		cout << "7.����������� ������\n";
		cout << "8.����������� ������\n";
		cout << "9.�������� ���������� ��������\n";
		cout << "0.�����\n";
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
			cout << "������!\n";
			system("pause");
			break;
		}
	}
}