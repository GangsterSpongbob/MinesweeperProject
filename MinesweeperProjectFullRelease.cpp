#include <iostream>
#include <ctime>

using namespace std;

struct String
{
	const int maxSize{ 20 };
	char* value = new char[maxSize] {};

	void getLine()
	{
		char input{};
		int index{};
		for (int i = 0; i < maxSize; i++)
		{
			value[i] = '\0';
		}
		while (input != '\n' && index < maxSize)
		{
			cin.get(input);
			if (input == '\n')
			{
				break;
			}
			value[index++] = input;
		}
	}

	void getWord()
	{
		char input{};
		int index{};
		for (int i = 0; i < maxSize; i++)
		{
			value[i] = '\0';
		}
		while (input != '\n' && input != ' ' && index < maxSize)
		{
			cin.get(input);
			if (input == '\n' || input == ' ')
			{
				break;
			}
			value[index++] = input;
		}
	}

	bool Compare(char* comp)
	{
		int index{};
		while (comp[index] != '\0' && value[index] != '\0')
		{
			if (comp[index] != value[index])
			{
				return 0;
			}
			index++;
		}

		if (comp[index] != value[index])
		{
			return 0;
		}

		return 1;
	}

	void setString(char inp[])
	{
		value = inp;
	}

	void clearStr()
	{
		delete value;
	}
};

struct
{
	int arrSize{}, mines{};
	int** playingField{}, ** maskedField{};
}field;

bool checkInteger(String check)
{
	char empty{ '\0' };
	if (check.Compare(&empty))
	{
		return 0;
	}

	int i{ check.value[0] == '-' ? 1 : 0 };

	while (check.value[i] != '\0')
	{
		if (!(check.value[i] >= '0' && check.value[i] <= '9'))
		{
			return 0;
		}
		i++;
	}

	return 1;
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

int strToInt(String toInt)
{
	if (!checkInteger(toInt))
	{
		return 0;
	}

	int index{}, total{}, negative{ 1 };
	if (toInt.value[index] == '-')
	{
		negative = -1;
		index++;
	}

	while (toInt.value[index] != '\0')
	{
		total = 10 * total + (toInt.value[index] - '0');
		index++;
	}

	return negative * total;
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

	if (field.arrSize < 3 || field.arrSize > 9)
	{
		exit(-1);
	}

	field.playingField = new int* [field.arrSize] {};
	for (int i = 0; i < field.arrSize; i++)
	{
		field.playingField[i] = new int[field.arrSize] {};
	}

	int extendedRowCol{ field.arrSize + 2 }; // size for bufferTable
	int** bufferTable = new int* [extendedRowCol] {}; // tableArr with one empty row/column to each side
	for (int i = 0; i < extendedRowCol; i++)
	{
		bufferTable[i] = new int[extendedRowCol] {};
	}

	// Populate with mines

	while (mineCount)
	{
		int rowNum{ rand() % field.arrSize };
		int colNum{ rand() % field.arrSize };

		if (field.playingField[rowNum][colNum] == 9)
		{
			continue;
		}
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
				for (int k = i; k <= i + 2; k++)
				{
					for (int l = j; l <= j + 2; l++)
					{
						if (bufferTable[k][l] == 9)
						{
							field.playingField[i][j]++;
						}
					}
				}
			}
		}
	}

	delArr(bufferTable, extendedRowCol);
}

char* openFunc(int xCoord, int yCoord)
{
	if (field.maskedField[xCoord][yCoord] == 11)
	{
		char* output = new char[18] { "Square is marked!" };
		return output;
	}

	else if (field.maskedField[xCoord][yCoord] != 10)
	{
		char* output = new char[24] { "Square is already open!" };
		return output;
	}

	else
	{
		openTile(xCoord, yCoord);
		char* output = new char[1] { "" };
		return output;
	}
}

char* markFunc(int xCoord, int yCoord)
{
	if (field.maskedField[xCoord][yCoord] == 10)
	{
		field.maskedField[xCoord][yCoord] = 11;
		field.mines--;
		char* output = new char[1] { "" };
		return output;
	}

	else if (field.maskedField[xCoord][yCoord] == 11)
	{
		char* output = new char[26]{ "Square is already marked!" };
		return output;
	}

	else
	{
		char* output = new char[24]{ "Square is already open!" };
		return output;
	}
}

char* unmarkFunc(int xCoord, int yCoord)
{
	if (field.maskedField[xCoord][yCoord] == 10)
	{
		char* output = new char[22]{ "Square is not marked!" };
		return output;
	}

	else if (field.maskedField[xCoord][yCoord] != 11)
	{
		char* output = new char[24]{ "Square is already open!" };
		return output;
	}

	else
	{
		field.maskedField[xCoord][yCoord] = 10;
		field.mines++;
		char* output = new char[1]{ "" };
		return output;
	}
}

int main()
{
	String input{};

	do
	{
		cout << "Enter number of rows and columns between 3 and 9: ";
		input.getLine();

		if (checkInteger(input))
		{
			field.arrSize = strToInt(input);
		}
		else
		{
			continue;
		}

	} while (field.arrSize < 3 || field.arrSize > 9);

	do
	{
		cout << "Enter number of mines between 1 and " << (3 * field.arrSize) << ": ";
		input.getLine();

		if (checkInteger(input))
		{
			field.mines = strToInt(input);
		}
		else
		{
			continue;
		}

	} while (field.mines < 1 || field.mines > 3 * field.arrSize);


	populateTable(field.mines);
	maskTable();
	String message{};

	do
	{
		cout << "\033[H\033[J";
		printTable(field.maskedField, field.arrSize, field.mines);

		cout << message.value << endl;
		cout << "(open <Row> <Column>) (mark <Row> <Column>) (unmark <Row> <Column>) (quit) \nEnter action: ";

		String cmd{};
		int xCoord{}, yCoord{};
		cmd.getWord();

		char quit[]{ "quit" }, open[]{ "open" }, mark[]{ "mark" }, unmark[]{ "unmark" };
		if (cmd.Compare(quit))
		{
			delArr(field.playingField, field.arrSize);
			delArr(field.maskedField, field.arrSize);
			cout << "Quitter!" << endl;
			exit(0);
		}
		else if (!(cmd.Compare(open) || cmd.Compare(mark) || cmd.Compare(unmark)))
		{
			char temp[]{ "Invalid action!" };
			message.setString(temp);
			continue;
		}

		String xInp{}, yInp{};
		xInp.getWord();
		yInp.getWord();

		if (checkInteger(xInp) && checkInteger(yInp))
		{
			xCoord = strToInt(xInp);
			yCoord = strToInt(yInp);
		}
		else
		{
			char temp[]{ "Invalid coordinates!" };
			message.setString(temp);
			continue;
		}

		if (xCoord > field.arrSize || yCoord > field.arrSize || xCoord < 1 || yCoord < 1)
		{
			char temp[]{ "Invalid coordinates!" };
			message.setString(temp);
			continue;
		}

		xCoord--;
		yCoord--;

		if (cmd.Compare(open))
		{
			message.setString(openFunc(xCoord, yCoord));
		}

		else if (cmd.Compare(mark))
		{
			message.setString(markFunc(xCoord, yCoord));
		}

		else if (cmd.Compare(unmark))
		{
			message.setString(unmarkFunc(xCoord, yCoord));
		}

		else
		{
			char temp[]{ "Invalid action!" };
			message.setString(temp);
		}

		xInp.clearStr();
		yInp.clearStr();
		cmd.clearStr();

	} while (!gameOver() && !gameWon());

	cout << "\033[H\033[J";
	printTable(field.playingField, field.arrSize, field.mines);

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

	input.clearStr();
	message.clearStr();

	delArr(field.maskedField, field.arrSize);
	delArr(field.playingField, field.arrSize);
}
