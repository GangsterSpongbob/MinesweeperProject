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
using namespace console_io;

int main() {
	int arr_size{}, mines{};

	arr_size = get_table_size();
	mines = get_mine_count(arr_size);

	Field& field = Field::instance(arr_size, mines);

	Line message = "Welcome to Minesweeper!";

	do {
		cout << "\033[H\033[J";
		field.print_table();

		cout << message.line << '\n';
		cout << "(o)pen   <Row> <Column>\n" \
				"(m)ark   <Row> <Column>\n" \
				"(u)nmark <Row> <Column>\n" \
				"(q)uit \nEnter action: ";

		commands cmd_type = NONE;

		cmd_type = read_cmd();

		if (cmd_type == NONE) {
			message = "Invalid action!";
			continue;
		} else if (cmd_type == QUIT) {
			cout << "Quitter!" << '\n';
			exit(0);
		}

		int x_coord = read_int();
		int y_coord = read_int();

		if (x_coord < 1 || x_coord > arr_size ||
			y_coord < 1 || y_coord > arr_size) {
			message = "Invalid coordinates!";
			continue;
		}

		x_coord--;
		y_coord--;

		if (cmd_type == OPEN) {
			message = field.open_func(x_coord, y_coord);
		} else if (cmd_type == MARK) {
			message = field.mark_func(x_coord, y_coord);
		} else if (cmd_type == UNMARK) {
			message = field.unmark_func(x_coord, y_coord);
		} else {
			message = "Invalid action!";
		}

	} while (!field.game_over() && !field.game_won());

	cout << "\033[H\033[J";
	field.print_table();

	if (field.game_over())
		cout << game_over_ascii;

	if (field.game_won())
		cout << game_won_ascii;
}
