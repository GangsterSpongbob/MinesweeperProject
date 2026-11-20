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

int arr_size{}, mines{};
int** playing_field{}, ** masked_field{};

int main() {
	char* input{ new char[max_array_length] {} };

	get_table_size(input);
	get_mine_count(input);

	populate_table(mines);
	mask_table();
	char* message{ new char[max_array_length] {} };

	do {
		cout << "\033[H\033[J";
		print_table();

		cout << message << '\n';
		cout << "(open <Row> <Column>) (mark <Row> <Column>) (unmark <Row> <Column>) (quit) \nEnter action: ";

		char* cmd{ new char[max_array_length] {} };
		int x_coord{}, y_coord{};
		get_word(cmd);

		if (compare(cmd, "quit")) {
			free_array(playing_field, arr_size);
			free_array(masked_field, arr_size);
			cout << "Quitter!" << '\n';
			exit(0);
		} else if (!(compare(cmd, "open") || compare(cmd, "mark") || compare(cmd, "unmark"))) {
			set_message(message, "Invalid action");
			continue;
		}

		char* x_input{ new char[max_array_length] {} }, * y_input{ new char[max_array_length] {} };
		get_word(x_input);
		get_word(y_input);

		if (check_int(x_input) && check_int(y_input)) {
			x_coord = str_to_int(x_input);
			y_coord = str_to_int(y_input);
		} else {
			set_message(message, "Invalid coordinates!");
			continue;
		}

		if (x_coord > arr_size || y_coord > arr_size || x_coord < 1 || y_coord < 1) {
			set_message(message, "Invalid coordinates!");
			continue;
		}

		x_coord--;
		y_coord--;

		if (compare(cmd, "open")) {
			set_message(message, open_func(x_coord, y_coord));
		} else if (compare(cmd, "mark")) {
			set_message(message, mark_func(x_coord, y_coord));
		} else if (compare(cmd, "unmark")) {
			set_message(message, unmark_func(x_coord, y_coord));
		} else {
			set_message(message, "Invalid action!");
		}

		delete[] x_input;
		delete[] y_input;
		delete[] cmd;
		x_input = nullptr;
		y_input = nullptr;
		cmd = nullptr;

	} while (!game_over() && !game_won());

	cout << "\033[H\033[J";
	print_table();

	if (game_over()) {
		cout << "\nGame Over!\n";
		cout << '\n' << GAME_OVER_ASCII;
	}

	if (game_won()) {
		cout << "\nCongratulations! You beat the game!\n";
		cout << '\n' << GAME_WON_ASCII;
	}

	delete[] input;
	delete[] message;
	input = nullptr;
	message = nullptr;

	free_array(masked_field, arr_size);
	free_array(playing_field, arr_size);
}
