#include <iostream>
#include <ctime>

using namespace std;

/*void printTable(int rowCol = 3)
{
	cout << '+';
	for (int i = 0; i < rowCol; i++)
	{
		cout << "-+";
	}
	cout << endl;

	for (int i = 0; i < rowCol; i++)
	{
		cout << '|';
		for (int j = 0; j < rowCol; j++)
		{
			cout << " |";
		}
		cout << endl;

		cout << '+';
		for (int j = 0; j < rowCol; j++)
		{
			cout << "-+";
		}
		cout << endl;
	}
}*/

void populateTable(int rowCol, int mineCount)
{
	srand(signed(time(NULL)));
	int const maxArrLen{ 9 };
	int tableArr[maxArrLen][maxArrLen]{};
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
					else if (j == rowCol) // isRight
					{
						tableArr[i][j] = (tableArr[i][j - 1] == 9) + (tableArr[i + 1][j - 1] == 9) + (tableArr[i + 1][j] == 9);
					}
					else
					{
						tableArr[i][j] = (tableArr[i][j - 1] == 9) + (tableArr[i][j + 1] == 9) + (tableArr[i + 1][j - 1] == 9) + (tableArr[i + 1][j] == 9) + (tableArr[i + 1][j + 1] == 9);
					}
				}
				else if (i == rowCol) // isBottom
				{
					if (j == 0) // isLeft
					{
						tableArr[i][j] = (tableArr[i][j + 1] == 9) + (tableArr[i - 1][j] == 9) + (tableArr[i - 1][j + 1] == 9);
					}
					else if (j == rowCol) // isRight
					{
						tableArr[i][j] = (tableArr[i][j - 1] == 9) + (tableArr[i - 1][j - 1] == 9) + (tableArr[i - 1][j] == 9);
					}
					else
					{
						tableArr[i][j] = (tableArr[i][j - 1] == 9) + (tableArr[i][j + 1] == 9) + (tableArr[i - 1][j - 1] == 9) + (tableArr[i - 1][j] == 9) + (tableArr[i + 1][j - 1] == 9);
					}
				}
				else
				{
					tableArr[i][j] = (tableArr[i - 1][j - 1] == 9) + (tableArr[i - 1][j] == 9) + (tableArr[i - 1][j + 1] == 9) + (tableArr[i][j - 1] == 9) + (tableArr[i][j + 1] == 9) + (tableArr[i + 1][j - 1] == 9) + (tableArr[i + 1][j] == 9) + (tableArr[i + 1][j + 1] == 9);
				}
			}
		}
	}

	//Print Array

	/*for (int i = 0; i < rowCol; i++)
	{
		for (int j = 0; j < rowCol; j++)
		{
			cout << tableArr[i][j];
		}
		cout << endl;
	}*/
	
	// Now print table with mines

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
			if (tableArr[i][j] == 9)
			{
				cout << 'M';
			}
			else if (tableArr[i][j] == 0)
			{
				cout << ' ';
			}
			else
			{
				cout << tableArr[i][j];
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

	// ^^^ Printing algorithm
}

int main()
{
	int nNum{}, mines{};
	const int maxArrLen{ 9 };
	int playingField[maxArrLen][maxArrLen]{};


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

	populateTable(nNum, mines);
}