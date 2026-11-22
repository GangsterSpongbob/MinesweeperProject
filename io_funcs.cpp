#include "funcs_header.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::cin;

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
			delete[] output;
			return OPEN;
		} else if (compare(output, "mark")) {
			delete[] output;
			return MARK;
		} else if (compare(output, "unmark")) {
			delete[] output;
			return UNMARK;
		} else if (compare(output, "quit")) {
			delete[] output;
			return QUIT;
		} else {
			delete[] output;
			return NONE;
		}
	} catch (...) {
		delete[] output;
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

int get_table_size(char* input) {
	int size{};

	do {
		cout << "Enter number of rows and columns between 3 and 9: ";
		clear_str(input);
		get_line(input);

		if (check_int(input)) {
			size = str_to_int(input);
		} else {
			clear_str(input);
			continue;
		}

	} while (size < 3 || size > 9);
	return size;
}

int get_mine_count(char* input, const int& arr_size) {
	int mines{};

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

	return mines;
}
