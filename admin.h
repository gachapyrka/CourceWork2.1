#pragma once
#include "account.h"
#include "menu.h"

using namespace std;

class Admin : public Account
{
	static string defaultLogin;
	static string defaultPassword;
public:
	Admin();
	void Init();
	void MenuService();
	void AddService(Service*&, int&);
	void EditService(Service*&, int&);
	void DelService(Service*&, int&);
	virtual void Menu();

	friend ostream& operator<<(ostream& o, Admin obj);
	friend istream& operator>>(istream& i, Admin& obj);
};