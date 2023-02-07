/**
*
* Solution to course project # 07
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Angel Ivanov
* @idnumber 3MI0600238
* @compiler VC
*
* main and only file
*
*/

#include <iostream>
#include <ctime>

using namespace std;

struct String
{
	const int maxSize{ 100 }; // more than a 100 characters would be obsolete
	char* value = new char[maxSize] {};

	void getLine()
	{
		char input{};
		int index{};

		for (int i = 0; i < maxSize; i++)
		{
			value[i] = '\0';
		}

		cin.get(input);
		while (input != '\n')
		{
			if (index < maxSize)
			{
				value[index] = input;
			}
			cin.get(input);
			index++;
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

		cin.get(input);
		while (input != '\n' && input != ' ')
		{
			if (index < maxSize)
			{
				value[index] = input;
			}
			cin.get(input);
			index++;
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
	if (check.value[0] == '\0') // empty string cannot be number
	{
		return 0;
	}

	int index{ check.value[0] == '-' ? 1 : 0 };

	while (check.value[index] != '\0')
	{
		if (!(check.value[index] >= '0' && check.value[index] <= '9'))
		{
			return 0;
		}
		index++;
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
	if (xCoord < 0 || yCoord < 0 || xCoord > field.arrSize - 1 || yCoord > field.arrSize - 1)
	{
		return;
	}

	if (field.maskedField[xCoord][yCoord] == 10)
	{
		field.maskedField[xCoord][yCoord] = field.playingField[xCoord][yCoord];
	}
	else
	{
		return;
	}

	if (field.maskedField[xCoord][yCoord] == 0)
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

void printTable(int** prField, int prSize, int minesLeft = 0)
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
				cout << 'M';
			}
			else if (prField[i][j] == 10) // 10 marks undiscovered square
			{
				cout << '@';
			}
			else if (prField[i][j] == 11) // 11 marks marked square (marked mine)
			{
				cout << '!';
			}
			else if (prField[i][j] == 0) // 0 is "empty", meaning it is open, but has no neighbouring mines
			{
				cout << ' ';
			}
			else
			{
				cout << prField[i][j];
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
				int k{ i + 1 }, l{ j + 1 }; // k and l corrsepond to i and j in bufferTable
				field.playingField[i][j] += bufferTable[k - 1][l - 1] == 9;
				field.playingField[i][j] += bufferTable[k - 1][l] == 9;
				field.playingField[i][j] += bufferTable[k - 1][l + 1] == 9;
				field.playingField[i][j] += bufferTable[k][l - 1] == 9;
				field.playingField[i][j] += bufferTable[k][l + 1] == 9;
				field.playingField[i][j] += bufferTable[k + 1][l - 1] == 9;
				field.playingField[i][j] += bufferTable[k + 1][l] == 9;
				field.playingField[i][j] += bufferTable[k + 1][l + 1] == 9;
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
		char* output = new char[26] { "Square is already marked!" };
		return output;
	}

	else
	{
		char* output = new char[24] { "Square is already open!" };
		return output;
	}
}

char* unmarkFunc(int xCoord, int yCoord)
{
	if (field.maskedField[xCoord][yCoord] == 10)
	{
		char* output = new char[22] { "Square is not marked!" };
		return output;
	}

	else if (field.maskedField[xCoord][yCoord] != 11)
	{
		char* output = new char[24] { "Square is already open!" };
		return output;
	}

	else
	{
		field.maskedField[xCoord][yCoord] = 10;
		field.mines++;
		char* output = new char[1] { "" };
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
		system("cls");
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

	system("cls");
	printTable(field.playingField, field.arrSize, field.mines);

	if (gameOver())
	{
		cout << endl << "Game Over!" << endl;
		cout << '\n' <<
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
			"         OO!                   ON!" << endl;
	}

	if (gameWon())
	{
		cout << endl << "Congratulations! You beat the game!" << endl;
		cout << '\n' <<
			"             ___________\n" <<
			"            \'._==_==_=_.\'\n" <<
			"            .-\\:      /-.\n" <<
			"           | (|:.     |) |\n" <<
			"            \'-|:.     |-\'\n" <<
			"              \\::.    /\n" <<
			"               \'::. .\'\n" <<
			"                 ) (\n" <<
			"               _.\' \'._\n" <<
			"              `\"\"\"\"\"\"\"`" << endl;
	}

	input.clearStr();
	message.clearStr();

	delArr(field.maskedField, field.arrSize);
	delArr(field.playingField, field.arrSize);
}
