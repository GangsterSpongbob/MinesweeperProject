#include "FuncsHeader.h"
#include <ctime>
#include <random>

using std::srand;
using std::rand;

extern int arrSize, mines;
extern int** playingField, ** maskedField;

void delArr(int**& delA, const int& dArrSize)
{
	for (int i = 0; i < dArrSize; i++)
	{
		delete[] delA[i];
		delA[i] = nullptr;
	}

	delete[] delA;
	delA = nullptr;
}

void openTile(const int& xCoord, const int& yCoord)
{
	if (xCoord < 0 || yCoord < 0 || xCoord > arrSize - 1 || yCoord > arrSize - 1)
	{
		return;
	}

	if (maskedField[xCoord][yCoord] == 10)
	{
		maskedField[xCoord][yCoord] = playingField[xCoord][yCoord];
	}
	else
	{
		return;
	}

	if (maskedField[xCoord][yCoord] == 0)
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
	for (int i = 0; i < arrSize; i++)
	{
		for (int j = 0; j < arrSize; j++)
		{
			if (maskedField[i][j] == 9)
			{
				return 1;
			}
		}
	}

	return 0;
}

bool gameWon()
{
	for (int i = 0; i < arrSize; i++)
	{
		for (int j = 0; j < arrSize; j++)
		{
			if (maskedField[i][j] == 10)
			{
				return 0;
			}

			if (playingField[i][j] != 9 && maskedField[i][j] == 11)
			{
				return 0;
			}

			if (playingField[i][j] == 9 && maskedField[i][j] != 11)
			{
				return 0;
			}
		}
	}

	return 1;
}

void maskTable()
{
	maskedField = new int* [arrSize] {};

	for (int i = 0; i < arrSize; i++)
	{
		maskedField[i] = new int[arrSize] {};
	}

	for (int i = 0; i < arrSize; i++)
	{
		for (int j = 0; j < arrSize; j++)
		{
			maskedField[i][j] = 10;
		}
	}
}

void populateTable(int mineCount)
{
	srand(signed(time(NULL)));

	if (arrSize < 3 || arrSize > 9)
	{
		return;
	}

	playingField = new int* [arrSize] {};
	for (int i = 0; i < arrSize; i++)
	{
		playingField[i] = new int[arrSize] {};
	}

	int extendedRowCol{ arrSize + 2 }; // size for bufferTable
	int** bufferTable = new int* [extendedRowCol] {}; // tableArr with one empty row/column to each side
	for (int i = 0; i < extendedRowCol; i++)
	{
		bufferTable[i] = new int[extendedRowCol] {};
	}

	// Populate with mines

	while (mineCount)
	{
		int rowNum{ rand() % arrSize };
		int colNum{ rand() % arrSize };

		if (playingField[rowNum][colNum] == 9)
		{
			continue;
		}
		playingField[rowNum][colNum] = 9;
		mineCount--;
	}

	// Copy to bufferTable

	for (int i = 0; i < arrSize; i++)
	{
		for (int j = 0; j < arrSize; j++)
		{
			bufferTable[i + 1][j + 1] = playingField[i][j];
		}
	}

	// Now populate with counters

	for (int i = 0; i < arrSize; i++)
	{
		for (int j = 0; j < arrSize; j++)
		{
			if (playingField[i][j] != 9)
			{
				int k{ i + 1 }, l{ j + 1 }; // k and l corrsepond to i and j in bufferTable
				playingField[i][j] += bufferTable[k - 1][l - 1] == 9;
				playingField[i][j] += bufferTable[k - 1][l] == 9;
				playingField[i][j] += bufferTable[k - 1][l + 1] == 9;
				playingField[i][j] += bufferTable[k][l - 1] == 9;
				playingField[i][j] += bufferTable[k][l + 1] == 9;
				playingField[i][j] += bufferTable[k + 1][l - 1] == 9;
				playingField[i][j] += bufferTable[k + 1][l] == 9;
				playingField[i][j] += bufferTable[k + 1][l + 1] == 9;
			}
		}
	}

	delArr(bufferTable, extendedRowCol);
}

char* openFunc(const int& xCoord, const int& yCoord)
{
	if (maskedField[xCoord][yCoord] == 11)
	{
		char* output = new char[18] { "Square is marked!" };
		return output;
	}

	else if (maskedField[xCoord][yCoord] != 10)
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

char* markFunc(const int& xCoord, const int& yCoord)
{
	if (maskedField[xCoord][yCoord] == 10)
	{
		maskedField[xCoord][yCoord] = 11;
		mines--;
		char* output = new char[1] { "" };
		return output;
	}

	else if (maskedField[xCoord][yCoord] == 11)
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

char* unmarkFunc(const int& xCoord, const int& yCoord)
{
	if (maskedField[xCoord][yCoord] == 10)
	{
		char* output = new char[22] { "Square is not marked!" };
		return output;
	}

	else if (maskedField[xCoord][yCoord] != 11)
	{
		char* output = new char[24] { "Square is already open!" };
		return output;
	}

	else
	{
		maskedField[xCoord][yCoord] = 10;
		mines++;
		char* output = new char[1] { "" };
		return output;
	}
}
