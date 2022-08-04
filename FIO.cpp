#include "FIO.h"

ostream& operator<<(ostream& o, const FIO& a)
{
	o << a.F << " " << a.I << " " << a.O;
	return o;
}

istream& operator>>(istream& i, FIO& a)
{
	i >> a.F >> a.I >> a.O;
	return i;
}

static char stroka[] = { '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�',
'�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�',
'�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�' };

bool proverka(char p_str)  //�������� ����� �����
{
	int j = 0;
	int k = 1;
	while (j < 64)
	{
		if (p_str == stroka[j])
		{
			k = 0;
			break;
		}
		else j++;
	}
	if (k == 1)
		return false;
	else
		return true;
}

FIO InputFIO()
{
	FIO fio;

	cout << "������� ������� " << endl;
	string str;
	bool correct = false;
	while (!correct)
	{
		correct = true;
		cin >> str;
		for (int i = 0; i < str.length(); i++)
		{
			if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || proverka(str[i])))
			{
				correct = false;

				break;
			}
		}
		if (correct)
		{
			for (int i = 1; i < str.length(); i++)
			{
				if (!proverka(str[i]))
					str[i] = tolower(str[i]);
			}
			if (!proverka(str[0]))
				str[0] += 'A' - 'a';
		}
		else
		{
			cout << "������������ ���� " << endl;
		}
	}
	fio.F = str;

	cout << "������� ��� " << endl;
	str = "";
	correct = false;
	while (!correct)
	{
		correct = true;
		cin >> str;
		for (int i = 0; i < str.length(); i++)
		{
			if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || proverka(str[i])))
			{
				correct = false;
				break;
			}
		}
		if (correct)
		{
			for (int i = 1; i < str.length(); i++)
			{
				if (!proverka(str[i]))
					str[i] = tolower(str[i]);
			}
			if (!proverka(str[0]))
				str[0] += 'A' - 'a';
		}
		else
		{
			cout << "������������ ���� " << endl;
		}
	}
	fio.I = str;

	cout << "������� �������� " << endl;
	str = "";
	correct = false;
	while (!correct)
	{
		correct = true;
		cin >> str;
		for (int i = 0; i < str.length(); i++)
		{
			if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || proverka(str[i])))
			{
				correct = false;
				break;
			}
		}
		if (correct)
		{
			for (int i = 1; i < str.length(); i++)
			{
				if (!proverka(str[i]))
					str[i] = tolower(str[i]);
			}
			if (!proverka(str[0]))
				str[0] += 'A' - 'a';
		}
		else
		{
			cout << "������������ ���� " << endl;
		}
	}
	fio.O = str;
	return fio;
}


