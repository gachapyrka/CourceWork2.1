#pragma once
#include <iostream>
#include "service.h"

using namespace std;

class Account
{
protected:
	string login;
	string password;
public:
	
	virtual void Menu() = 0;
	string GetLogin();
	string GetPass();

	void SetLogin(string _login);
	void SetPass(string _password);
};

string Encrypt(string);
string Decrypt(string);