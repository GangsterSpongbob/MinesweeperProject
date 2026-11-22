#include "funcs_header.h"

#include <iostream>
#include <ctime>
#include <random>
#include <memory>

using std::cout;

namespace {
    std::unique_ptr<Field> g_field;

    void free_array(int**& arr, const int& arr_len) {
        for (int i = 0; i < arr_len; i++) {
            delete[] arr[i];
            arr[i] = nullptr;
        }

        delete[] arr;
        arr = nullptr;
    }
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

void Field::create_playing_field(Field& field, const int& arr_size, int mine_count) {
	std::srand(signed(time(NULL)));

	if (arr_size < 3 || arr_size > 9)
		return;

	int** playing_field = new int* [arr_size] {};
	for (int i = 0; i < arr_size; i++)
		playing_field[i] = new int[arr_size] {};

	int extended_row_col{ arr_size + 2 }; // size for buffer_table
	int** buffer_table = new int* [extended_row_col] {}; // tableArr with one empty row/column to each side
	for (int i = 0; i < extended_row_col; i++)
		buffer_table[i] = new int[extended_row_col] {};

	// Populate with mines

	while (mine_count) {
		int row_num{ std::rand() % arr_size };
		int col_num{ std::rand() % arr_size };

		if (playing_field[row_num][col_num] == 9)
			continue;

		playing_field[row_num][col_num] = 9;
		mine_count--;
	}

	// Copy to buffer_table

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++)
			buffer_table[i + 1][j + 1] = playing_field[i][j];
	}

	// Now populate with counters

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			if (playing_field[i][j] != 9) {
				int k{ i + 1 }, l{ j + 1 }; // k and l corrsepond to i and j in buffer_table
				playing_field[i][j] += buffer_table[k - 1][l - 1] == 9;
				playing_field[i][j] += buffer_table[k - 1][l] == 9;
				playing_field[i][j] += buffer_table[k - 1][l + 1] == 9;
				playing_field[i][j] += buffer_table[k][l - 1] == 9;
				playing_field[i][j] += buffer_table[k][l + 1] == 9;
				playing_field[i][j] += buffer_table[k + 1][l - 1] == 9;
				playing_field[i][j] += buffer_table[k + 1][l] == 9;
				playing_field[i][j] += buffer_table[k + 1][l + 1] == 9;
			}
		}
	}

	free_array(buffer_table, extended_row_col);

    field.playing_field = playing_field;
}

void Field::create_masked_field(Field& field, const int& arr_size) {
	int** masked_field = new int* [arr_size] {};

	for (int i = 0; i < arr_size; i++)
		masked_field[i] = new int[arr_size] {};

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			masked_field[i][j] = 10;
		}
	}

    field.masked_field = masked_field;
}

Field::Field(const int& size, const int& mine_count) : arr_size{ size }, mines{ mine_count } {
    create_playing_field(*this, arr_size, mines);
    create_masked_field(*this, arr_size);
}

Field::~Field() {
    free_array(playing_field, arr_size);
    free_array(masked_field, arr_size);
}

void Field::open_tile(const int& x_coord, const int& y_coord) {
	if (x_coord < 0 || y_coord < 0 || x_coord > arr_size - 1 || y_coord > arr_size - 1)
		return;

	if (masked_field[x_coord][y_coord] == 10) {
		masked_field[x_coord][y_coord] = playing_field[x_coord][y_coord];
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

			if (playing_field[i][j] != 9 && masked_field[i][j] == 11)
				return 0;

			if (playing_field[i][j] == 9 && masked_field[i][j] != 11)
				return 0;
		}
	}

	return 1;
}

char* Field::open_func(const int& x_coord, const int& y_coord) {
	if (masked_field[x_coord][y_coord] == 11) {
		char* output = new char[18] { "Square is marked!" };
		return output;
	} else if (masked_field[x_coord][y_coord] != 10) {
		char* output = new char[24] { "Square is already open!" };
		return output;
	} else {
		open_tile(x_coord, y_coord);
		char* output = new char[1] { "" };
		return output;
	}
}

char* Field::mark_func(const int& x_coord, const int& y_coord) {
	if (masked_field[x_coord][y_coord] == 10) {
		masked_field[x_coord][y_coord] = 11;
		mines--;
		char* output = new char[1] { "" };
		return output;
	} else if (masked_field[x_coord][y_coord] == 11) {
		char* output = new char[26] { "Square is already marked!" };
		return output;
	} else {
		char* output = new char[24] { "Square is already open!" };
		return output;
	}
}

char* Field::unmark_func(const int& x_coord, const int& y_coord) {
	if (masked_field[x_coord][y_coord] == 10) {
		char* output = new char[22] { "Square is not marked!" };
		return output;
	} else if (masked_field[x_coord][y_coord] != 11) {
		char* output = new char[24] { "Square is already open!" };
		return output;
	} else {
		masked_field[x_coord][y_coord] = 10;
		mines++;
		char* output = new char[1] { "" };
		return output;
	}
}
