#include "funcs_header.h"

#include <iostream>
#include <memory>

using std::cout;

namespace {
    std::unique_ptr<Field> g_field;
}

Field& Field::instance(const int a, const int b) {
    if (!g_field)
        g_field.reset(new Field(a, b));

    return *g_field;
}

Field& Field::instance() {
    if (!g_field)
        throw std::runtime_error("Field::instance() called before initialization");

    return *g_field;
}

void Field::create_playing_field(Field& field, int arr_size, int mine_count) {
	std::srand(signed(time(NULL)));

	if (arr_size < 3 || arr_size > 9)
		return;

    int (&playing_field)[max_playing_field_size][max_playing_field_size] = field.playing_field;

	// Populate with mines

	while (mine_count) {
        // add 1 to row_num and col_num to account for buffer_table
		int row_num{ (std::rand() % arr_size) + 1 };
		int col_num{ (std::rand() % arr_size) + 1 };

		if (playing_field[row_num][col_num] == 9)
			continue;

		playing_field[row_num][col_num] = 9;
		mine_count--;
	}

	// Now populate with counters

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
            int k{ i + 1 }, l{ j + 1 }; // k and l corrsepond to i and j in buffer_table
			if (playing_field[k][l] != 9) {
				playing_field[k][l] += playing_field[k - 1][l - 1] == 9;
				playing_field[k][l] += playing_field[k - 1][l] == 9;
				playing_field[k][l] += playing_field[k - 1][l + 1] == 9;
				playing_field[k][l] += playing_field[k][l - 1] == 9;
				playing_field[k][l] += playing_field[k][l + 1] == 9;
				playing_field[k][l] += playing_field[k + 1][l - 1] == 9;
				playing_field[k][l] += playing_field[k + 1][l] == 9;
				playing_field[k][l] += playing_field[k + 1][l + 1] == 9;
			}
		}
	}
}

void Field::create_masked_field(Field& field, int arr_size) {
	int (&masked_field)[max_masked_field_size][max_masked_field_size] = field.masked_field;

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			masked_field[i][j] = 10;
		}
	}
}

Field::Field(int size, int mine_count) : arr_size{ size }, mines{ mine_count } {
    create_playing_field(*this, arr_size, mines);
    create_masked_field(*this, arr_size);
}

void Field::open_tile(int x_coord, int y_coord) {
	if (x_coord < 0 || y_coord < 0 || x_coord > arr_size - 1 || y_coord > arr_size - 1)
		return;

	if (masked_field[x_coord][y_coord] == 10) {
		masked_field[x_coord][y_coord] = playing_field[x_coord + 1][y_coord + 1];
	} else {
		return;
	}

	if (masked_field[x_coord][y_coord] == 0) {
		open_tile(x_coord - 1, y_coord - 1);
		open_tile(x_coord - 1, y_coord);
		open_tile(x_coord - 1, y_coord + 1);
		open_tile(x_coord, y_coord - 1);
		open_tile(x_coord, y_coord + 1);
		open_tile(x_coord + 1, y_coord - 1);
		open_tile(x_coord + 1, y_coord);
		open_tile(x_coord + 1, y_coord + 1);
	}
}

void Field::print_table() {
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
				cout << colors[RED] << 'M' << colors[RESET];
				break;
			case 10:
				cout << colors[GREY] << ' ' << colors[RESET];
				break;
			case 11:
				cout << colors[RED] << '!' << colors[RESET];
				break;
			case 0:
				cout << ' ';
				break;
			default:
				cout << colors[masked_field[i][j]] << masked_field[i][j]
					<< colors[RESET];
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

bool Field::game_over() {
	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			if (masked_field[i][j] == 9)
				return 1;
		}
	}

	return 0;
}

bool Field::game_won() {
	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			if (masked_field[i][j] == 10)
				return 0;

			if (playing_field[i + 1][j + 1] != 9 && masked_field[i][j] == 11)
				return 0;

			if (playing_field[i + 1][j + 1] == 9 && masked_field[i][j] != 11)
				return 0;
		}
	}

	return 1;
}

Line Field::open_func(int x_coord, int y_coord) {
	Line output;

	if (masked_field[x_coord][y_coord] == 11) {
		output = "Square is marked!";
	} else if (masked_field[x_coord][y_coord] != 10) {
		output = "Square is already open!";
	} else {
		open_tile(x_coord, y_coord);
		output = "";
	}

    return output;
}

Line Field::mark_func(int x_coord, int y_coord) {
	Line output;

	if (masked_field[x_coord][y_coord] == 10) {
		masked_field[x_coord][y_coord] = 11;
		mines--;
		output = "";
	} else if (masked_field[x_coord][y_coord] == 11) {
		output = "Square is already marked!";
	} else {
		output = "Square is already open!";
	}

    return output;
}

Line Field::unmark_func(int x_coord, int y_coord) {
	Line output;

	if (masked_field[x_coord][y_coord] == 10) {
		output = "Square is not marked!";
	} else if (masked_field[x_coord][y_coord] != 11) {
		output = "Square is already open!";
	} else {
		masked_field[x_coord][y_coord] = 10;
		mines++;
		output = "";
	}

    return output;
}
