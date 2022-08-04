#pragma once
#include "input.h"

int InputInt()
{
	std::string input = "";

	bool correct = false;
	while (!correct)
	{

		std::cin >> input;

		correct = true;

		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] < '0' || input[i]>'9')
			{
				correct = false;

				if (input[i] == '-' && i == 0)
				{
					correct = true;
				}
			}
		}
		if (!correct)
		{
			std::cout << "Ошибка ввода\n";
		}
	}

	return atoi(input.c_str());
}

double InputDouble()
{
	std::string input = "";

	bool correct = false;

	bool isNegative = false;

	while (!correct)
	{
		correct = true;

		std::cin >> input;

		int countOfDerivers = 0;

		for (int i = 0; i < input.length(); i++)
		{

			if ((input[i] < '0' && input[i] != '.' && input[i] != ',') || (input[i] > '9' && input[i] != '.' && input[i] != ',') || (countOfDerivers > 0 && input[i] == '.') || (countOfDerivers > 0 && input[i] == ','))
			{
				if (input[i] == '-' && i == 0)
				{
					isNegative = true;
				}
				else
				{
					std::cout << "Ошибка ввода\n";
					correct = false;

					break;
				}
			}
			else if (input[i] == '.' || input[i] == ',')
			{
				countOfDerivers++;
			}
		}
	}

	double a = 0;
	double b = 0;

	int i = 0;

	if (isNegative)
	{
		i++;
	}
	while (i < input.length() && input[i] != ',' && input[i] != '.')
	{
		char d[2];
		d[0] = input[i];
		d[1] = '\0';
		a *= 10;
		a += atoi(d);
		i++;
	}
	i++;
	while (i < input.length() && input[i] <= '9' && input[i] >= '0')
	{
		char d[2];
		d[0] = input[i];
		d[1] = '\0';
		b *= 10;
		b += atoi(d);
		i++;
	}

	while (b > 1)
	{
		b = b / 10;
	}

	if (isNegative)
	{
		return -(a + b);
	}
	else
	{
		return (a + b);
	}
}

