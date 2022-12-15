#include <iostream>
#include <ctime>

using namespace std;

bool gameOver(int** mask, int rowCol)
{
	for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			if (mask[i][j] == 9)
			{
				return 1;
			}
		}
	}
	return 0;
}

bool gameWon(int** mask, int** table, int rowCol)
{
	for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			if (mask[i][j] == 10)
			{
				return 0;
			}
		}
	}

	for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			if (table[i][j] != 9 && mask[i][j] == 11)
			{
				return 0;
			}
		}
	}

	for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			if (table[i][j] == 9 && mask[i][j] != 11)
			{
				return 0;
			}
		}
	}
	return 1;
}

void printTable(int** table, int rowCol)
{
	cout << '+';
	for (int i = 0; i < rowCol; i++)
	{
		cout << "---+";
	}
	cout << endl;

	for (int i = 0; i < rowCol; i++)
	{
		cout << '|';
		for (int j = 0; j < rowCol; j++)
		{
			cout << ' ';
			if (table[i][j] == 9)  // 9 marks a mine
			{
				cout << 'M';
			}
			else if (table[i][j] == 10)  // 10 marks undiscovered square
			{
				cout << '-';
			}
			else if (table[i][j] == 11)  // 11 marks marked square (marked mine)
			{
				cout << '^';
			}
			else if (table[i][j] == 0)
			{
				cout << ' ';
			}
			else
			{
				cout << table[i][j];
			}
			cout << " |";
		}
		cout << endl;

		cout << '+';
		for (int j = 0; j < rowCol; j++)
		{
			cout << "---+";
		}
		cout << endl;
	}
}

int** maskTable(int rowCol)
{
	int** tableMask = new int* [rowCol] {};
	for (int i = 0; i < rowCol; i++)
	{
		tableMask[i] = new int[rowCol] {};
	}

	for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			tableMask[i][j] = 10;
		}
	}
	return tableMask;
}

int** populateTable(int rowCol, int mineCount)
{
	srand(signed(time(NULL)));

	if (rowCol < 3 || rowCol > 9)
	{
		exit(-1);
	}

	int** tableArr = new int* [rowCol] {};
	for (int i = 0; i < rowCol; i++)
	{
		tableArr[i] = new int[rowCol] {};
	}

	while (mineCount)
	{
		int rowNum{ rand() % rowCol };
		int colNum{ rand() % rowCol };
		if (tableArr[rowNum][colNum] == 9)
		{
			continue;
		}
		tableArr[rowNum][colNum] = 9;  
		mineCount--;
	}

	// Now populate with counters

	for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			if (tableArr[i][j] != 9)
			{
				if (i == 0) // isTop
				{
					if (j == 0) // isLeft
					{
						tableArr[i][j] = (tableArr[i][j + 1] == 9) + (tableArr[i + 1][j] == 9) + (tableArr[i + 1][j + 1] == 9);
					}
					else if (j == rowCol - 1) // isRight
					{
						tableArr[i][j] = (tableArr[i][j - 1] == 9) + (tableArr[i + 1][j - 1] == 9) + (tableArr[i + 1][j] == 9);
					}
					else
					{
						tableArr[i][j] = (tableArr[i][j - 1] == 9) + (tableArr[i][j + 1] == 9) + (tableArr[i + 1][j - 1] == 9) + (tableArr[i + 1][j] == 9) + (tableArr[i + 1][j + 1] == 9);
					}
				}
				else if (i == rowCol - 1) // isBottom
				{
					if (j == 0) // isLeft
					{
						tableArr[i][j] = (tableArr[i][j + 1] == 9) + (tableArr[i - 1][j] == 9) + (tableArr[i - 1][j + 1] == 9);
					}
					else if (j == rowCol - 1) // isRight
					{
						tableArr[i][j] = (tableArr[i][j - 1] == 9) + (tableArr[i - 1][j - 1] == 9) + (tableArr[i - 1][j] == 9);
					}
					else
					{
						tableArr[i][j] = (tableArr[i][j - 1] == 9) + (tableArr[i][j + 1] == 9) + (tableArr[i - 1][j - 1] == 9) + (tableArr[i - 1][j] == 9) + (tableArr[i - 1][j + 1] == 9);
					}
				}
				else
				{
					tableArr[i][j] = (tableArr[i - 1][j - 1] == 9) + (tableArr[i - 1][j] == 9) + (tableArr[i - 1][j + 1] == 9) + (tableArr[i][j - 1] == 9) + (tableArr[i][j + 1] == 9) + (tableArr[i + 1][j - 1] == 9) + (tableArr[i + 1][j] == 9) + (tableArr[i + 1][j + 1] == 9);
				}
			}
		}
	}

	return tableArr;

	//Print Array

	/*for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			cout << tableArr[i][j];
		}
		cout << endl;
	}*/
}

int main()
{
	int nNum{}, mines{};

	do
	{
		cout << "Enter number of rows and columns between 3 and 9: ";
		cin >> nNum;
	} while (nNum < 3 || nNum > 9);

	do
	{
		cout << "Enter number of mines between 1 and " << (3 * nNum) << ": ";
		cin >> mines;
	} while (mines < 1 || mines > 3 * nNum);


	int** playingField = populateTable(nNum, mines);
	int** maskedField = maskTable(nNum);

	//printTable(playingField, nNum);
	//printTable(maskedField, nNum);

	do
	{
		printTable(maskedField, nNum);

		cout << "(open <x> <y>) (mark <x> <y>) (unmark <x> <y>) \nEnter action: ";
		string cmd{};
		int xCoord{}, yCoord{};
		cin >> cmd >> xCoord >> yCoord;
		if (xCoord > nNum || yCoord > nNum)
		{
			cout << "Invalid coordinates!" << endl;
			continue;
		}
		xCoord--;
		yCoord--;

		if (cmd == "open")
		{
			if (maskedField[xCoord][yCoord] == 11)
			{
				cout << "Square is marked!" << endl;
			}
			else if (maskedField[xCoord][yCoord] != 10)
			{
				cout << "Square is already open!" << endl;
			}
			else
			{
				maskedField[xCoord][yCoord] = playingField[xCoord][yCoord];
			}
		}
		else if (cmd == "mark")
		{
			if (maskedField[xCoord][yCoord] == 10 || maskedField[xCoord][yCoord] == 11)
			{
				maskedField[xCoord][yCoord] = 11;
			}
			else
			{
				cout << "Square is already open!" << endl;
			}
		}
		else if (cmd == "unmark")
		{
			if (maskedField[xCoord][yCoord] == 10)
			{
				cout << "Square is not marked!" << endl;
			}
			else if (maskedField[xCoord][yCoord] != 11)
			{
				cout << "Square is already open!" << endl;
			}
			else
			{
				maskedField[xCoord][yCoord] = 10;
			}
		}
		else
		{
			cout << "Invalid action!" << endl;
		}
	} while (!gameOver(maskedField, nNum) && !gameWon(maskedField, playingField, nNum));

	printTable(maskedField, nNum);
	if (gameOver(maskedField, nNum))
	{
		cout << "Game Over!" << endl;
	}

	if (gameWon(maskedField , playingField, nNum))
	{
		cout << "Congratulations! You beat the game!" << endl;
	}

	/*
	for (int i = 0; i < nNum; i++) //
	{
		for (int j = 0; j < nNum; j++)
		{
			cout << playingField[i][j] << ' ';
		}
		cout << endl;
	} //
	cout << endl;

	for (int i = 0; i < nNum; i++) //
	{
		for (int j = 0; j < nNum; j++)
		{
			cout << maskedField[i][j] << ' ';
		}
		cout << endl;
	} //
	*/
}