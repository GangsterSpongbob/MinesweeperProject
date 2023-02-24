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

#include "FuncsHeader.h"
#include <iostream>
using std::cout;
using std::cin;

int arrSize{}, mines{};
int** playingField{}, ** maskedField{};

int main()
{
	char* input{ new char[maxArrayLength] {} };

	getTableSize(input);
	getMineCount(input);

	populateTable(mines);
	maskTable();
	char* message{ new char[maxArrayLength] {} };

	do
	{
		cout << "\033[H\033[J";
		printTable();

		cout << message << '\n';
		cout << "(open <Row> <Column>) (mark <Row> <Column>) (unmark <Row> <Column>) (quit) \nEnter action: ";

		char* cmd{ new char[maxArrayLength] {} };
		int xCoord{}, yCoord{};
		getWord(cmd);

		if (Compare(cmd,"quit"))
		{
			delArr(playingField, arrSize);
			delArr(maskedField, arrSize);
			cout << "Quitter!" << '\n';
			exit(0);
		}
		else if (!(Compare(cmd, "open") || Compare(cmd, "mark") || Compare(cmd,"unmark")))
		{
			setMessage(message, "Invalid action");
			continue;
		}

		char* xInp{ new char[maxArrayLength] {} }, * yInp{ new char[maxArrayLength] {} };
		getWord(xInp);
		getWord(yInp);

		if (checkInteger(xInp) && checkInteger(yInp))
		{
			xCoord = strToInt(xInp);
			yCoord = strToInt(yInp);
		}
		else
		{
			setMessage(message, "Invalid coordinates!");
			continue;
		}

		if (xCoord > arrSize || yCoord > arrSize || xCoord < 1 || yCoord < 1)
		{
			setMessage(message, "Invalid coordinates!");
			continue;
		}

		xCoord--;
		yCoord--;

		if (Compare(cmd, "open"))
		{
			setMessage(message, openFunc(xCoord, yCoord));
		}

		else if (Compare(cmd, "mark"))
		{
			setMessage(message, markFunc(xCoord, yCoord));
		}

		else if (Compare(cmd, "unmark"))
		{
			setMessage(message, unmarkFunc(xCoord, yCoord));
		}

		else
		{
			setMessage(message, "Invalid action!");
		}

		delete[] xInp;
		delete[] yInp;
		delete[] cmd;
		xInp = nullptr;
		yInp = nullptr;
		cmd = nullptr;

	} while (!gameOver() && !gameWon());

	cout << "\033[H\033[J";
	printTable();

	if (gameOver())
	{
		cout << "\nGame Over!\n";
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
			"         OO!                   ON!" << "\033[0m\n";
	}

	if (gameWon())
	{
		cout << "\nCongratulations! You beat the game!\n";
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
			"              `\"\"\"\"\"\"\"`" << "\033[0m\n";
	}

	delete[] input;
	delete[] message;
	input = nullptr;
	message = nullptr;

	delArr(maskedField, arrSize);
	delArr(playingField, arrSize);
}
