#pragma once
#include "menu.h"
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace filemanager;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	while (true)
	{
		Admin* arr = NULL;
		FileManager<Admin> fmA(ADMIN_FILE);
		int n = fmA.Load(arr);
		if (!n)
		{
			cout << "Это первый вход. Зарегистрируйте администратора" << endl;
			arr[0].Init();
			arr[0].Menu();
		}

		Client* arrP = NULL;
		FileManager<Client> fmC(CLIENT_FILE);
		int nP = fmC.Load(arrP);
		Master* arrE = NULL;
		FileManager<Master> fmR(MASTER_FILE);
		int nE = fmR.Load(arrE);

		system("cls");
		cout << "Введите логин или 0 для выхода" << endl;
		string login;
		cin >> login;
		if (login == "0")
		{
			break;
		}
		cout << "Введите пароль" << endl;
		char c = 0;
		char str[70];
		int it = 0;
		do
		{
			c = _getch();
			if (c == '\b')
			{
				if (it != 0)
				{
					cout << "\b \b";
					it--;
				}
			}
			else if (c == 13)
			{
				str[it] = '\0';
				it++;
			}
			else
			{
				str[it] = c;
				it++;
				printf("*");
			}

		} while (c != 13);
		string password = str;
		bool loged = false;
		if (arr[0].GetLogin() == login && arr[0].GetPass() == password)
		{
			loged = true;
			arr[0].Menu();
		}
		else
		{
			for (int i = 0; i < nP; i++)
			{
				if (arrP[i].GetLogin() == login && arrP[i].GetPass() == password)
				{
					loged = true;
					arrP[i].Menu();
				}
			}
		}
		if (!loged)
		{
			for (int i = 0; i < nE; i++)
			{
				if (arrE[i].GetLogin() == login && arrE[i].GetPass() == password)
				{
					loged = true;
					arrE[i].Menu();
				}
			}
		}
		if (!loged)
		{
			system("cls");
			cout << "Логин или пароль неверный" << endl;
			system("pause");
		}
	}
	return 0;
}