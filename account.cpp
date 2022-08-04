#pragma once
#include "account.h"

string Account::GetLogin() { return login; }

string Account::GetPass() { return Decrypt(password); }

void Account::SetLogin(string _login) { login = _login; }

void Account::SetPass(string _password) { password = Encrypt(_password); }

string Encrypt(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] += 100;
	}
	return str;
}

string Decrypt(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] -= 100;
	}
	return str;
}