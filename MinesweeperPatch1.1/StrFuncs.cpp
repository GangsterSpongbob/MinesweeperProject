#include "FuncsHeader.h"
#include <iostream> //

void setMessage(char* msg, const char inp[])
{
	clearStr(msg);
	int index{};
	while (inp[index] != '\0')
	{
		msg[index] = inp[index];
		index++;
	}
}

void clearStr(char* clr) // fills string with \0 characters
{
	for (int i = 0; i < maxArrayLength; i++)
	{
		clr[i] = '\0';
	}
}

bool Compare(const char* tocomp, const char* comp)
{
	int index{};
	while (tocomp[index] != '\0' && comp[index] != '\0')
	{
		if (tocomp[index] != comp[index])
		{
			return 0;
		}
		index++;
	}
	return 1;
}

bool checkInteger(const char* check)
{
	if (*check == '\0') // empty string cannot be number
	{
		return 0;
	}

	int index{ *check == '-' ? 1 : 0 };

	while (check[index] != '\0')
	{
		if (!(check[index] >= '0' && check[index] <= '9'))
		{
			return 0;
		}
		index++;
	}

	return 1;
}

int strToInt(const char* toInt)
{
	if (!checkInteger(toInt))
	{
		return 0;
	}

	int index{}, total{}, negative{ 1 };
	if (toInt[index] == '-')
	{
		negative = -1;
		index++;
	}

	while (toInt[index] != '\0')
	{
		total = 10 * total + (toInt[index] - '0');
		index++;
	}

	return negative * total;
}