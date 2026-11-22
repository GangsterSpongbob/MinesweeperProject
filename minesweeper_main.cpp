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

#include "funcs_header.h"
#include <iostream>
using std::cout;
using std::cin;

int main() {
	char* input{ new char[max_array_length] {} };
	int arr_size{}, mines{};

	arr_size = get_table_size(input);
	mines = get_mine_count(input, arr_size);

	Field& field = Field::instance(arr_size, mines);

	char* message{ new char[max_array_length] {} };

	do {
		cout << "\033[H\033[J";
		field.print_table();

		cout << message << '\n';
		cout << "(o)pen   <Row> <Column>\n" \
				"(m)ark   <Row> <Column>\n" \
				"(u)nmark <Row> <Column>\n" \
				"(q)uit \nEnter action: ";

		commands cmd_type = NONE;

		try {
			cmd_type = read_cmd();
		} catch (const std::invalid_argument& e) {
			set_message(message, "Invalid input!");
			continue;
		}

		if (cmd_type == QUIT) {
			cout << "Quitter!" << '\n';
			exit(0);
		}

		int x_coord = 0;
		int y_coord = 0;

		try {
			x_coord = read_int();
			y_coord = read_int();
		} catch (const std::invalid_argument& e) {
			set_message(message, "Invalid coordinates!");
			continue;
		}

		if (x_coord < 1 || x_coord > arr_size ||
			y_coord < 1 || y_coord > arr_size) {
			set_message(message, "Invalid coordinates!");
			continue;
		}

		x_coord--;
		y_coord--;

		if (cmd_type == OPEN) {
			set_message(message, field.open_func(x_coord, y_coord));
		} else if (cmd_type == MARK) {
			set_message(message, field.mark_func(x_coord, y_coord));
		} else if (cmd_type == UNMARK) {
			set_message(message, field.unmark_func(x_coord, y_coord));
		} else {
			set_message(message, "Invalid action!");
		}

	} while (!field.game_over() && !field.game_won());

	cout << "\033[H\033[J";
	field.print_table();

	if (field.game_over()) {
		cout << "\nGame Over!\n";
		cout << '\n' << GAME_OVER_ASCII;
	}

	if (field.game_won()) {
		cout << "\nCongratulations! You beat the game!\n";
		cout << '\n' << GAME_WON_ASCII;
	}

	delete[] input;
	delete[] message;
	input = nullptr;
	message = nullptr;
}
