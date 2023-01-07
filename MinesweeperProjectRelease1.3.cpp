#include <iostream>
#include <ctime>
#include <string>

using namespace std;

bool checkInteger(string check)
{
	if (check == "") return 0;

	int i{ check[0] == '-' ? 1 : 0 };

	while (isdigit(check[i++]))
	{
		if (check[i] == '\0')
		{
			return 1;
		}
	}

	return 0;
}

void delArr(int** delA, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		delete[] delA[i];
		delA[i] = nullptr;
	}

	delete[] delA;
	delA = nullptr;
}

void openTile(int ** playingField, int ** maskedTable, int rowCol, int xCoord, int yCoord)
{
	if (maskedTable[xCoord][yCoord] == 10)
	{
		maskedTable[xCoord][yCoord] = playingField[xCoord][yCoord];

		if (maskedTable[xCoord][yCoord] == 0)
		{
			if (xCoord == 0) // isTop
			{
				if (yCoord == 0) // isLeft
				{
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord + 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord + 1);
				}
				else if (yCoord == rowCol - 1) // isRight
				{
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord);
				}
				else // isNeither
				{
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord + 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord + 1);
				}
			}

			else if (xCoord == rowCol - 1) // isBottom
			{
				if (yCoord == 0) // isLeft
				{
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord + 1);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord + 1);
				}
				else if (yCoord == rowCol - 1) // isRight
				{
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord);
				}
				else // isNeiter
				{
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord + 1);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord + 1);
				}
			}

			else // isNeither
			{
				if (yCoord == 0) // isLeft
				{
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord + 1);
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord + 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord + 1);
				}
				else if (yCoord == rowCol - 1) // isRight
				{
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord);
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord);
				}
				else // isNeither
				{
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord);
					openTile(playingField, maskedTable, rowCol, xCoord - 1, yCoord + 1);
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord, yCoord + 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord - 1);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord);
					openTile(playingField, maskedTable, rowCol, xCoord + 1, yCoord + 1);
				}
			}
		}

		else
		{
			maskedTable[xCoord][yCoord] = playingField[xCoord][yCoord];
		}
	}
}

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

			if (table[i][j] != 9 && mask[i][j] == 11)
			{
				return 0;
			}

			if (table[i][j] == 9 && mask[i][j] != 11)
			{
				return 0;
			}
		}
	}

	return 1;
}

void printTable(int** table, int rowCol, int minesLeft = 0)
{
	cout << "Remaining mines: " << minesLeft << endl;

	cout << '+';
	for (int i = 0; i < rowCol + 1; i++)
	{
		cout << "---+";
	}

	cout << endl << '|';
	for (int i = 0; i < rowCol + 1; i++)
	{
		if (i == 0)
		{
			cout << " \\ |";
			continue;
		}
		cout << i << "Cl|";
	}

	cout << endl << '+';
	for (int i = 0; i < rowCol + 1; i++)
	{
		cout << "---+";
	}
	cout << endl;

	for (int i = 0; i < rowCol; i++)
	{
		cout << '|' << i + 1 << "Rw|";
		for (int j = 0; j < rowCol; j++)
		{
			cout << ' ';
			if (table[i][j] == 9) // 9 marks a mine
			{
				cout << "\033[31m" << 'M' << "\033[0m";
			}
			else if (table[i][j] == 10) // 10 marks undiscovered square
			{
				cout << "\033[100m" << ' ' << "\033[0m";
			}
			else if (table[i][j] == 11) // 11 marks marked square (marked mine)
			{
				cout << "\033[31m" << '!' << "\033[0m";
			}
			else if (table[i][j] == 0) // 0 is "empty", meaning it is open, but has no neighbouring mines
			{
				cout << ' ';
			}
			else
			{
				switch (table[i][j]) // 0 - 8 mark number of surrounding mines
				{
				case 1:
					cout << "\033[94m" << table[i][j] << "\033[0m";
					break;
				case 2:
					cout << "\033[92m" << table[i][j] << "\033[0m";
					break;
				case 3:
					cout << "\033[91m" << table[i][j] << "\033[0m";
					break;
				case 4:
					cout << "\033[35m" << table[i][j] << "\033[0m";
					break;
				case 5:
					cout << "\033[33m" << table[i][j] << "\033[0m";
					break;
				case 6:
					cout << "\033[36m" << table[i][j] << "\033[0m";
					break;
				case 7:
					cout << "\033[32m" << table[i][j] << "\033[0m";
					break;
				case 8:
					cout << "\033[95m" << table[i][j] << "\033[0m";
					break;
				}
			}
			cout << " |";
		}

		cout << endl << '+';
		for (int j = 0; j < rowCol + 1; j++)
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

	if (rowCol < 3 || rowCol > 9) exit(-1);

	int** tableArr = new int* [rowCol] {};
	for (int i = 0; i < rowCol; i++) tableArr[i] = new int[rowCol] {};

	int extendedRowCol{ rowCol + 2 }; // size for bufferTable
	int** bufferTable = new int* [extendedRowCol] {}; // tableArr with one empty row/column to each side
	for (int i = 0; i < extendedRowCol; i++) bufferTable[i] = new int[extendedRowCol] {};

	// Populate with mines

	while (mineCount)
	{
		int rowNum{ rand() % rowCol };
		int colNum{ rand() % rowCol };

		if (tableArr[rowNum][colNum] == 9) continue;
		tableArr[rowNum][colNum] = 9;  
		mineCount--;
	}

	// Copy to bufferTable

	for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			bufferTable[i + 1][j + 1] = tableArr[i][j];
		}
	}

	// Now populate with counters

	for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			if (tableArr[i][j] != 9)
			{
				int m{ i + 1 }, n{ j + 1 }; // indexes for bufferTable (it has one extra column on the left and one extra row on top)
				tableArr[i][j] = (bufferTable[m - 1][n - 1] == 9) + (bufferTable[m - 1][n] == 9) + (bufferTable[m - 1][n + 1] == 9) + (bufferTable[m][n - 1] == 9) + (bufferTable[m][n + 1] == 9) + (bufferTable[m + 1][n - 1] == 9) + (bufferTable[m + 1][n] == 9) + (bufferTable[m + 1][n + 1] == 9);
				// ^^^ spans all 8 surrounding tiles
			}
		}
	}

	delArr(bufferTable, extendedRowCol);

	return tableArr;
}

string openFunc(int ** playingField, int ** maskedField, int xCoord, int yCoord, int rowCol)
{
	if (maskedField[xCoord][yCoord] == 11)
	{
		return "Square is marked!";
	}

	else if (maskedField[xCoord][yCoord] != 10)
	{
		return "Square is already open!";
	}

	else
	{
		openTile(playingField, maskedField, rowCol, xCoord, yCoord);
		return "";
	}
}

string markFunc(int** maskedField, int xCoord, int yCoord)
{
		if (maskedField[xCoord][yCoord] == 10)
		{
			maskedField[xCoord][yCoord] = 11;
			return "";
		}

		else if (maskedField[xCoord][yCoord] == 11)
		{
			return "Square is already marked!";
		}

		else
		{
			return "Square is already open!";
		}
}

string unmarkFunc(int** maskedField, int xCoord, int yCoord)
{
	if (maskedField[xCoord][yCoord] == 10)
	{
		return "Square is not marked!";
	}

	else if (maskedField[xCoord][yCoord] != 11)
	{
		return "Square is already open!";
	}

	else
	{
		maskedField[xCoord][yCoord] = 10;
		return "";
	}
}

int main()
{
	int rowColumnCount{}, mines{};
	string input{};

	do
	{
		cout << "Enter number of rows and columns between 3 and 9: ";
		getline(cin, input);

		if (checkInteger(input)) rowColumnCount = stoi(input);
		else continue;

	} while (rowColumnCount < 3 || rowColumnCount > 9);

	do
	{
		cout << "Enter number of mines between 1 and " << (3 * rowColumnCount) << ": ";
		getline(cin, input);

		if (checkInteger(input)) mines = stoi(input);
		else continue;

	} while (mines < 1 || mines > 3 * rowColumnCount);


	int** playingField = populateTable(rowColumnCount, mines);
	int** maskedField = maskTable(rowColumnCount);
	string message{};

	do
	{
		system("CLS");
		printTable(maskedField, rowColumnCount, mines);

		cout << message << endl;
		cout << "(open <Row> <Column>) (mark <Row> <Column>) (unmark <Row> <Column>) (quit) \nEnter action: ";

		string cmd{};
		int xCoord{}, yCoord{};
		cin >> cmd;

		if (cmd == "quit")
		{
			delArr(playingField, rowColumnCount);
			delArr(maskedField, rowColumnCount);
			cout << "Quitter!" << endl;
			exit(0);
		}

		string xInp{}, yInp{};
		cin >> xInp >> yInp;

		if (checkInteger(xInp) && checkInteger(yInp))
		{
			xCoord = stoi(xInp);
			yCoord = stoi(yInp);
		}
		else
		{
			message = "Invalid coordinates!";
			continue;
		}

		if (xCoord > rowColumnCount || yCoord > rowColumnCount)
		{
			message = "Invalid coordinates!";
			continue;
		}

		xCoord--;
		yCoord--;

		if (cmd == "open")
		{
			message = openFunc(playingField, maskedField, xCoord, yCoord, rowColumnCount);
		}

		else if (cmd == "mark")
		{
			if (maskedField[xCoord][yCoord] == 10)
			{
				mines--;
			}
			message = markFunc(maskedField, xCoord, yCoord);
		}

		else if (cmd == "unmark")
		{
			if (maskedField[xCoord][yCoord] == 11)
			{
				mines++;
			}
			message = unmarkFunc(maskedField, xCoord, yCoord);
		}

		else message = "Invalid action!";

	} while (!gameOver(maskedField, rowColumnCount) && !gameWon(maskedField, playingField, rowColumnCount));

	system("CLS");
	printTable(playingField, rowColumnCount, mines);

	if (gameOver(maskedField, rowColumnCount))
	{
		cout << endl << "Game Over!" << endl;
		cout << "\n      NO!                          MNO!\n     MNO!!                        MNNOO!\n   MMNO!                           MNNOO!!\n MNOONNOO!   MMMMMMMMMMPPPOII!   MNNO!!!!\n !O! NNO! MMMMMMMMMMMMMPPPOOOII!! NO!\n       ! MMMMMMMMMMMMMPPPPOOOOIII! !\n        MMMMMMMMMMMMPPPPPOOOOOOII!!\n        MMMMMOOOOOOPPPPPPPPOOOOMII!\n        MMMMM..    OPPMMP    .,OMI!\n        MMMM::   o.,OPMP,.o   ::I!!\n          NNM:::.,,OOPM!P,.::::!!\n         MMNNNNNOOOOPMO!!IIPPO!!O!\n         MMMMMNNNNOO:!!:!!IPPPPOO!\n          MMMMMNNOOMMNNIIIPPPOO!!\n             MMMONNMMNNNIIIOO!\n           MN MOMMMNNNIIIIIO! OO\n          MNO! IiiiiiiiiiiiI OOOO\n     NNN.MNO!   O!!!!!!!!!O   OONO NO!\n    MNNNNNO!    OOOOOOOOOOO    MMNNON!\n      MNNNNO!    PPPPPPPPP    MMNON!\n         OO!                   ON!" << endl;
	}

	if (gameWon(maskedField , playingField, rowColumnCount))
	{
		cout << endl << "Congratulations! You beat the game!" << endl;
		cout << "             ___________\n            \'._==_==_=_.\'\n            .-\\:      /-.\n           | (|:.     |) |\n            \'-|:.     |-\'\n              \\::.    /\n               \'::. .\'\n                 ) (\n               _.\' \'._\n              `\"\"\"\"\"\"\"`" << endl;
	}

	delArr(maskedField, rowColumnCount);
	delArr(playingField, rowColumnCount);
}
