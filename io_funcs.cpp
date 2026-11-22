#include "funcs_header.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::cin;

Line get_line() {
	Line output;

	int index{};
	char input{};

	cin.get(input);
	while (input != '\n') {
		if (index < max_array_length)
			output[index] = input;
		cin.get(input);
		index++;
	}

    return output;
}

Line get_word() {
	Line output;

	int index{};
	char input{};

	cin.get(input);
	while (input != '\n' && input != ' ') {
		if (index < max_array_length)
			output[index] = input;
		cin.get(input);
		index++;
	}
    return output;
}

commands read_cmd() {
	Line input = get_word();

	if (input == "open") {
		return OPEN;
	} else if (input == "mark") {
		return MARK;
	} else if (input == "unmark") {
		return UNMARK;
	} else if (input == "quit") {
		return QUIT;
	} else {
		return NONE;
	}
}

int read_int() {
	Line input = get_word();

	if (!input.check_int())
		throw std::invalid_argument("Invalid integer input");

	int result = input.to_int();
	return result;
}

int get_table_size() {
	int size{};

	do {
		cout << "Enter number of rows and columns between 3 and 9: ";
		Line input = get_line();

		if (input.check_int()) {
			size = input.to_int();
		} else {
			continue;
		}

	} while (size < 3 || size > 9);
	return size;
}

int get_mine_count(const int& arr_size) {
	int mines{};

	do {
		cout << "Enter number of mines between 1 and " << (3 * arr_size) << ": ";
		Line input = get_line();

		if (input.check_int()) {
			mines = input.to_int();
		} else {
			continue;
		}

	} while (mines < 1 || mines > 3 * arr_size);

	return mines;
}
