#include "funcs_header.h"
#include <iostream>
#include <stdexcept>

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
			 * 1 - 8 mark number of surrounding mines
			 * 9 marks a mine
			 * 10 marks undiscovered square
			 * 11 marks marked square (marked mine)
			 * 0 is "empty", meaning it is open, but has no neighbouring mines
			*/
			switch (masked_field[i][j]) {
			case 9:
				cout << color_codes[RED] << 'M' << color_codes[RESET];
				break;
			case 10:
				cout << color_codes[GREY] << ' ' << color_codes[RESET];
				break;
			case 11:
				cout << color_codes[RED] << '!' << color_codes[RESET];
				break;
			case 0:
				cout << ' ';
				break;
			default:
				cout << color_codes[masked_field[i][j]] << masked_field[i][j]
					<< color_codes[RESET];
				break;
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

commands read_cmd() {
	char* output{ new char[max_array_length] {} };

	try {
		get_word(output);

		if (compare(output, "open")) {
			free(output);
			return OPEN;
		} else if (compare(output, "mark")) {
			free(output);
			return MARK;
		} else if (compare(output, "unmark")) {
			free(output);
			return UNMARK;
		} else if (compare(output, "quit")) {
			free(output);
			return QUIT;
		} else {
			free(output);
			return NONE;
		}
	} catch (...) {
		free(output);
		throw std::invalid_argument("Invalid command input");
	}

}

int read_int() {
	char* output{ new char[max_array_length] {} };

	try {
		get_word(output);

		if (!check_int(output))
			throw std::invalid_argument("Invalid integer input");

		int result = str_to_int(output);
		delete[] output;
		return result;
	} catch (...) {
		delete[] output;
		throw;
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
