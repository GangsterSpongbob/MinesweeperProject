#include <iostream>
#include <ctime>
#include <string>

using namespace std;

struct
{
	int arrSize{}, mines{};
	int** playingField{}, ** maskedField{};
}field;

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

void openTile(int xCoord, int yCoord)
{
	if (field.maskedField[xCoord][yCoord] == 10)
	{
		field.maskedField[xCoord][yCoord] = field.playingField[xCoord][yCoord];

		if (field.maskedField[xCoord][yCoord] == 0)
		{
			if (xCoord == 0) // isTop
			{
				if (yCoord == 0) // isLeft
				{
					openTile(xCoord, yCoord + 1);
					openTile(xCoord + 1, yCoord);
					openTile(xCoord + 1, yCoord + 1);
				}
				else if (yCoord == field.arrSize - 1) // isRight
				{
					openTile(xCoord, yCoord - 1);
					openTile(xCoord + 1, yCoord - 1);
					openTile(xCoord + 1, yCoord);
				}
				else // isNeither
				{
					openTile(xCoord, yCoord - 1);
					openTile(xCoord, yCoord + 1);
					openTile(xCoord + 1, yCoord - 1);
					openTile(xCoord + 1, yCoord);
					openTile(xCoord + 1, yCoord + 1);
				}
			}

			else if (xCoord == field.arrSize - 1) // isBottom
			{
				if (yCoord == 0) // isLeft
				{
					openTile(xCoord, yCoord + 1);
					openTile(xCoord - 1, yCoord);
					openTile(xCoord - 1, yCoord + 1);
				}
				else if (yCoord == field.arrSize - 1) // isRight
				{
					openTile(xCoord, yCoord - 1);
					openTile(xCoord - 1, yCoord - 1);
					openTile( xCoord - 1, yCoord);
				}
				else // isNeiter
				{
					openTile(xCoord, yCoord - 1);
					openTile(xCoord, yCoord + 1);
					openTile(xCoord - 1, yCoord - 1);
					openTile(xCoord - 1, yCoord);
					openTile(xCoord - 1, yCoord + 1);
				}
			}

			else // isNeither
			{
				if (yCoord == 0) // isLeft
				{
					openTile(xCoord - 1, yCoord);
					openTile(xCoord - 1, yCoord + 1);
					openTile(xCoord, yCoord + 1);
					openTile(xCoord + 1, yCoord);
					openTile(xCoord + 1, yCoord + 1);
				}
				else if (yCoord == field.arrSize - 1) // isRight
				{
					openTile(xCoord - 1, yCoord - 1);
					openTile(xCoord - 1, yCoord);
					openTile(xCoord, yCoord - 1);
					openTile(xCoord + 1, yCoord - 1);
					openTile(xCoord + 1, yCoord);
				}
				else // isNeither
				{
					openTile(xCoord - 1, yCoord - 1);
					openTile(xCoord - 1, yCoord);
					openTile(xCoord - 1, yCoord + 1);
					openTile(xCoord, yCoord - 1);
					openTile(xCoord, yCoord + 1);
					openTile(xCoord + 1, yCoord - 1);
					openTile(xCoord + 1, yCoord);
					openTile(xCoord + 1, yCoord + 1);
				}
			}
		}

		else
		{
			field.maskedField[xCoord][yCoord] = field.playingField[xCoord][yCoord];
		}
	}
}

bool gameOver()
{
	for (int i = 0; i < field.arrSize; i++)
	{
		for (int j = 0; j < field.arrSize; j++)
		{
			if (field.maskedField[i][j] == 9)
			{
				return 1;
			}
		}
	}

	return 0;
}

bool gameWon()
{
	for (int i = 0; i < field.arrSize; i++)
	{
		for (int j = 0; j < field.arrSize; j++)
		{
			if (field.maskedField[i][j] == 10)
			{
				return 0;
			}

			if (field.playingField[i][j] != 9 && field.maskedField[i][j] == 11)
			{
				return 0;
			}

			if (field.playingField[i][j] == 9 && field.maskedField[i][j] != 11)
			{
				return 0;
			}
		}
	}

	return 1;
}

void printTable(int** prField, int prSize ,int minesLeft = 0)
{
	cout << "Remaining mines: " << minesLeft << endl;

	cout << '+';
	for (int i = 0; i < prSize + 1; i++)
	{
		cout << "---+";
	}

	cout << endl << '|';
	for (int i = 0; i < prSize + 1; i++)
	{
		if (i == 0)
		{
			cout << " \\ |";
			continue;
		}
		cout << i << "Cl|";
	}

	cout << endl << '+';
	for (int i = 0; i < prSize + 1; i++)
	{
		cout << "---+";
	}
	cout << endl;

	for (int i = 0; i < prSize; i++)
	{
		cout << '|' << i + 1 << "Rw|";
		for (int j = 0; j < prSize; j++)
		{
			cout << ' ';
			if (prField[i][j] == 9) // 9 marks a mine
			{
				cout << "\033[31m" << 'M' << "\033[0m";
			}
			else if (prField[i][j] == 10) // 10 marks undiscovered square
			{
				cout << "\033[100m" << ' ' << "\033[0m";
			}
			else if (prField[i][j] == 11) // 11 marks marked square (marked mine)
			{
				cout << "\033[31m" << '!' << "\033[0m";
			}
			else if (prField[i][j] == 0) // 0 is "empty", meaning it is open, but has no neighbouring mines
			{
				cout << ' ';
			}
			else
			{
				switch (prField[i][j]) // 0 - 8 mark number of surrounding mines
				{
				case 1:
					cout << "\033[94m" << prField[i][j] << "\033[0m";
					break;
				case 2:
					cout << "\033[92m" << prField[i][j] << "\033[0m";
					break;
				case 3:
					cout << "\033[91m" << prField[i][j] << "\033[0m";
					break;
				case 4:
					cout << "\033[35m" << prField[i][j] << "\033[0m";
					break;
				case 5:
					cout << "\033[33m" << prField[i][j] << "\033[0m";
					break;
				case 6:
					cout << "\033[36m" << prField[i][j] << "\033[0m";
					break;
				case 7:
					cout << "\033[32m" << prField[i][j] << "\033[0m";
					break;
				case 8:
					cout << "\033[95m" << prField[i][j] << "\033[0m";
					break;
				}
			}
			cout << " |";
		}

		cout << endl << '+';
		for (int j = 0; j < prSize + 1; j++)
		{
			cout << "---+";
		}
		cout << endl;
	}
}

void maskTable()
{
	field.maskedField = new int* [field.arrSize] {};

	for (int i = 0; i < field.arrSize; i++)
	{
		field.maskedField[i] = new int[field.arrSize] {};
	}

	for (int i = 0; i < field.arrSize; i++)
	{
		for (int j = 0; j < field.arrSize; j++)
		{
			field.maskedField[i][j] = 10;
		}
	}
}

void populateTable(int mineCount)
{
	srand(signed(time(NULL)));

	if (field.arrSize < 3 || field.arrSize > 9) exit(-1);

	field.playingField = new int* [field.arrSize] {};
	for (int i = 0; i < field.arrSize; i++) field.playingField[i] = new int[field.arrSize] {};

	int extendedRowCol{ field.arrSize + 2 }; // size for bufferTable
	int** bufferTable = new int* [extendedRowCol] {}; // tableArr with one empty row/column to each side
	for (int i = 0; i < extendedRowCol; i++) bufferTable[i] = new int[extendedRowCol] {};

	// Populate with mines

	while (mineCount)
	{
		int rowNum{ rand() % field.arrSize };
		int colNum{ rand() % field.arrSize };

		if (field.playingField[rowNum][colNum] == 9) continue;
		field.playingField[rowNum][colNum] = 9;
		mineCount--;
	}

	// Copy to bufferTable

	for (int i = 0; i < field.arrSize; i++)
	{
		for (int j = 0; j < field.arrSize; j++)
		{
			bufferTable[i + 1][j + 1] = field.playingField[i][j];
		}
	}

	// Now populate with counters

	for (int i = 0; i < field.arrSize; i++)
	{
		for (int j = 0; j < field.arrSize; j++)
		{
			if (field.playingField[i][j] != 9)
			{
				int m{ i + 1 }, n{ j + 1 }; // indexes for bufferTable (it has one extra column on the left and one extra row on top)
				field.playingField[i][j] = (bufferTable[m - 1][n - 1] == 9) + (bufferTable[m - 1][n] == 9) + (bufferTable[m - 1][n + 1] == 9) + (bufferTable[m][n - 1] == 9) + (bufferTable[m][n + 1] == 9) + (bufferTable[m + 1][n - 1] == 9) + (bufferTable[m + 1][n] == 9) + (bufferTable[m + 1][n + 1] == 9);
				// ^^^ spans all 8 surrounding tiles
			}
		}
	}

	delArr(bufferTable, extendedRowCol);
}

string openFunc(int xCoord, int yCoord)
{
	if (field.maskedField[xCoord][yCoord] == 11)
	{
		return "Square is marked!";
	}

	else if (field.maskedField[xCoord][yCoord] != 10)
	{
		return "Square is already open!";
	}

	else
	{
		openTile(xCoord, yCoord);
		return "";
	}
}

string markFunc(int xCoord, int yCoord)
{
	if (field.maskedField[xCoord][yCoord] == 10)
	{
		field.maskedField[xCoord][yCoord] = 11;
		field.mines--;
		return "";
	}

	else if (field.maskedField[xCoord][yCoord] == 11)
	{
		return "Square is already marked!";
	}

	else
	{
		return "Square is already open!";
	}
}

string unmarkFunc(int xCoord, int yCoord)
{
	if (field.maskedField[xCoord][yCoord] == 10)
	{
		return "Square is not marked!";
	}

	else if (field.maskedField[xCoord][yCoord] != 11)
	{
		return "Square is already open!";
	}

	else
	{
		field.maskedField[xCoord][yCoord] = 10;
		field.mines++;
		return "";
	}
}

int main()
{
	string input{};

	do
	{
		cout << "Enter number of rows and columns between 3 and 9: ";
		getline(cin, input);

		if (checkInteger(input)) field.arrSize = stoi(input);
		else continue;

	} while (field.arrSize < 3 || field.arrSize > 9);

	do
	{
		cout << "Enter number of mines between 1 and " << (3 * field.arrSize) << ": ";
		getline(cin, input);

		if (checkInteger(input)) field.mines = stoi(input);
		else continue;

	} while (field.mines < 1 || field.mines > 3 * field.arrSize);


	populateTable(field.mines);
	maskTable();
	string message{};

	do
	{
		system("CLS");
		printTable(field.maskedField, field.arrSize, field.mines);

		cout << message << endl;
		cout << "(open <Row> <Column>) (mark <Row> <Column>) (unmark <Row> <Column>) (quit) \nEnter action: ";

		string cmd{};
		int xCoord{}, yCoord{};
		cin >> cmd;

		if (cmd == "quit")
		{
			delArr(field.playingField, field.arrSize);
			delArr(field.maskedField, field.arrSize);
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

		if (xCoord > field.arrSize || yCoord > field.arrSize || xCoord < 1 || yCoord < 1)
		{
			message = "Invalid coordinates!";
			continue;
		}

		xCoord--;
		yCoord--;

		if (cmd == "open")
		{
			message = openFunc(xCoord, yCoord);
		}

		else if (cmd == "mark")
		{
			message = markFunc(xCoord, yCoord);
		}

		else if (cmd == "unmark")
		{
			message = unmarkFunc(xCoord, yCoord);
		}

		else message = "Invalid action!";

	} while (!gameOver() && !gameWon());

	system("CLS");
	printTable(field.maskedField, field.arrSize, field.mines);

	if (gameOver())
	{
		cout << endl << "Game Over!" << endl;
		cout << '\n' <<
			"\033[32m" <<
			"      NO!                          MNO!\n" <<
			"     MNO!!                        MNNOO!\n" <<
			"   MMNO!                           MNNOO!!\n" <<
			" MNOONNOO!   MMMMMMMMMMPPPOII!   MNNO!!!!\n" <<
			" !O! NNO! MMMMMMMMMMMMMPPPOOOII!! NO!\n" <<
			"       ! MMMMMMMMMMMMMPPPPOOOOIII! !\n" <<
			"        MMMMMMMMMMMMPPPPPOOOOOOII!!\n" <<
			"        MMMMMOOOOOOPPPPPPPPOOOOMII!\n" <<
			"        MMMMM..    OPPMMP    .,OMI!\n" <<
			"        MMMM::   o.,OPMP,.o   ::I!!\n" <<
			"          NNM:::.,,OOPM!P,.::::!!\n" <<
			"         MMNNNNNOOOOPMO!!IIPPO!!O!\n" <<
			"         MMMMMNNNNOO:!!:!!IPPPPOO!\n" <<
			"          MMMMMNNOOMMNNIIIPPPOO!!\n" <<
			"             MMMONNMMNNNIIIOO!\n" <<
			"           MN MOMMMNNNIIIIIO! OO\n" <<
			"          MNO! IiiiiiiiiiiiI OOOO\n" <<
			"     NNN.MNO!   O!!!!!!!!!O   OONO NO!\n" <<
			"    MNNNNNO!    OOOOOOOOOOO    MMNNON!\n" <<
			"      MNNNNO!    PPPPPPPPP    MMNON!\n" <<
			"         OO!                   ON!" << "\033[0m" << endl;
	}

	if (gameWon())
	{
		cout << endl << "Congratulations! You beat the game!" << endl;
		cout << '\n' <<
			"\033[33m" <<
			"             ___________\n" <<
			"            \'._==_==_=_.\'\n" <<
			"            .-\\:      /-.\n" <<
			"           | (|:.     |) |\n" <<
			"            \'-|:.     |-\'\n" <<
			"              \\::.    /\n" <<
			"               \'::. .\'\n" <<
			"                 ) (\n" <<
			"               _.\' \'._\n" <<
			"              `\"\"\"\"\"\"\"`" << "\033[0m" << endl;
	}

	delArr(field.maskedField, field.arrSize);
	delArr(field.playingField, field.arrSize);
}
