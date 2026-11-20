#include "funcs_header.h"
#include <iostream>

using std::cout;
using std::cin;

extern int arr_size, mines;
extern int** playing_field, ** masked_field;

void print_table() {
	cout << "Remaining mines: " << mines << '\n';

	cout << '+';
	for (int i = 0; i < arr_size + 1; i++)
		cout << "---+";

	cout << '\n' << '|';
	for (int i = 0; i < arr_size + 1; i++) {
		if (i == 0) {
			cout << " \\ |";
			continue;
		}
		cout << i << "Cl|";
	}

	cout << '\n' << '+';
	for (int i = 0; i < arr_size + 1; i++)
		cout << "---+";
	cout << '\n';

	for (int i = 0; i < arr_size; i++) {
		cout << '|' << i + 1 << "Rw|";
		for (int j = 0; j < arr_size; j++) {
			cout << ' ';
			/*
			 * 0 - 8 mark number of surrounding mines
			 * 9 marks a mine
			 * 10 marks undiscovered square
			 * 11 marks marked square (marked mine)
			 * 0 is "empty", meaning it is open, but has no neighbouring mines
			*/
			if (masked_field[i][j] == 9) {
				cout << "\033[31m" << 'M' << "\033[0m";
			} else if (masked_field[i][j] == 10) {
				cout << "\033[100m" << ' ' << "\033[0m";
			} else if (masked_field[i][j] == 11) {
				cout << "\033[31m" << '!' << "\033[0m";
			} else if (masked_field[i][j] == 0) {
				cout << ' ';
			} else {
				switch (masked_field[i][j]) {
				case 1:
					cout << "\033[94m" << masked_field[i][j] << "\033[0m";
					break;
				case 2:
					cout << "\033[92m" << masked_field[i][j] << "\033[0m";
					break;
				case 3:
					cout << "\033[91m" << masked_field[i][j] << "\033[0m";
					break;
				case 4:
					cout << "\033[35m" << masked_field[i][j] << "\033[0m";
					break;
				case 5:
					cout << "\033[33m" << masked_field[i][j] << "\033[0m";
					break;
				case 6:
					cout << "\033[36m" << masked_field[i][j] << "\033[0m";
					break;
				case 7:
					cout << "\033[32m" << masked_field[i][j] << "\033[0m";
					break;
				case 8:
					cout << "\033[95m" << masked_field[i][j] << "\033[0m";
					break;
				}
			}
			cout << " |";
		}

		cout << "\n+";
		for (int j = 0; j < arr_size + 1; j++)
			cout << "---+";
		cout << '\n';
	}
}

void get_line(char* output) {
	int index{};
	char input{};

	cin.get(input);
	while (input != '\n') {
		if (index < max_array_length)
			output[index] = input;
		cin.get(input);
		index++;
	}
}

void get_word(char* output) {
	int index{};
	char input{};

	cin.get(input);
	while (input != '\n' && input != ' ') {
		if (index < max_array_length)
			output[index] = input;
		cin.get(input);
		index++;
	}
}

void get_table_size(char* input) {
	do {
		cout << "Enter number of rows and columns between 3 and 9: ";
		clear_str(input);
		get_line(input);

		if (check_int(input)) {
			arr_size = str_to_int(input);
		} else {
			clear_str(input);
			continue;
		}

	} while (arr_size < 3 || arr_size > 9);
}

void get_mine_count(char* input) {
	do {
		cout << "Enter number of mines between 1 and " << (3 * arr_size) << ": ";
		clear_str(input);
		get_line(input);

		if (check_int(input)) {
			mines = str_to_int(input);
		} else {
			continue;
		}

	} while (mines < 1 || mines > 3 * arr_size);
}
