#include "FuncsHeader.h"
#include <iostream>

using std::cout;
using std::cin;

extern int arrSize, mines;
extern int** playingField, ** maskedField;

void printTable()
{
	cout << "Remaining mines: " << mines << '\n';

	cout << '+';
	for (int i = 0; i < arrSize + 1; i++)
	{
		cout << "---+";
	}

	cout << '\n' << '|';
	for (int i = 0; i < arrSize + 1; i++)
	{
		if (i == 0)
		{
			cout << " \\ |";
			continue;
		}
		cout << i << "Cl|";
	}

	cout << '\n' << '+';
	for (int i = 0; i < arrSize + 1; i++)
	{
		cout << "---+";
	}
	cout << '\n';

	for (int i = 0; i < arrSize; i++)
	{
		cout << '|' << i + 1 << "Rw|";
		for (int j = 0; j < arrSize; j++)
		{
			cout << ' ';
			if (maskedField[i][j] == 9) // 9 marks a mine
			{
				cout << "\033[31m" << 'M' << "\033[0m";
			}
			else if (maskedField[i][j] == 10) // 10 marks undiscovered square
			{
				cout << "\033[100m" << ' ' << "\033[0m";
			}
			else if (maskedField[i][j] == 11) // 11 marks marked square (marked mine)
			{
				cout << "\033[31m" << '!' << "\033[0m";
			}
			else if (maskedField[i][j] == 0) // 0 is "empty", meaning it is open, but has no neighbouring mines
			{
				cout << ' ';
			}
			else
			{
				switch (maskedField[i][j]) // 0 - 8 mark number of surrounding mines
				{
				case 1:
					cout << "\033[94m" << maskedField[i][j] << "\033[0m";
					break;
				case 2:
					cout << "\033[92m" << maskedField[i][j] << "\033[0m";
					break;
				case 3:
					cout << "\033[91m" << maskedField[i][j] << "\033[0m";
					break;
				case 4:
					cout << "\033[35m" << maskedField[i][j] << "\033[0m";
					break;
				case 5:
					cout << "\033[33m" << maskedField[i][j] << "\033[0m";
					break;
				case 6:
					cout << "\033[36m" << maskedField[i][j] << "\033[0m";
					break;
				case 7:
					cout << "\033[32m" << maskedField[i][j] << "\033[0m";
					break;
				case 8:
					cout << "\033[95m" << maskedField[i][j] << "\033[0m";
					break;
				}
			}
			cout << " |";
		}

		cout << "\n+";
		for (int j = 0; j < arrSize + 1; j++)
		{
			cout << "---+";
		}
		cout << '\n';
	}
}

void getLine(char* output)
{
	int index{};
	char input{};

	cin.get(input);
	while (input != '\n')
	{
		if (index < maxArrayLength)
		{
			output[index] = input;
		}
		cin.get(input);
		index++;
	}
}

void getWord(char* output)
{
	int index{};
	char input{};

	cin.get(input);
	while (input != '\n' && input != ' ')
	{
		if (index < maxArrayLength)
		{
			output[index] = input;
		}
		cin.get(input);
		index++;
	}
}

void getTableSize(char* input)
{
	do
	{
		cout << "Enter number of rows and columns between 3 and 9: ";
		clearStr(input);
		getLine(input);

		if (checkInteger(input))
		{
			arrSize = strToInt(input);
		}
		else
		{
			clearStr(input);
			continue;
		}

	} while (arrSize < 3 || arrSize > 9);
}

void getMineCount(char* input)
{
	do
	{
		cout << "Enter number of mines between 1 and " << (3 * arrSize) << ": ";
		clearStr(input);
		getLine(input);

		if (checkInteger(input))
		{
			mines = strToInt(input);
		}
		else
		{
			continue;
		}

	} while (mines < 1 || mines > 3 * arrSize);
}