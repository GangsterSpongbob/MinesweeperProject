#include "funcs_header.h"
#include <ctime>
#include <random>

using std::srand;
using std::rand;

extern int arr_size, mines;
extern int** playing_field, ** masked_field;

void free_array(int**& arr, const int& arr_len) {
	for (int i = 0; i < arr_len; i++) {
		delete[] arr[i];
		arr[i] = nullptr;
	}

	delete[] arr;
	arr = nullptr;
}

void open_tile(const int& x_coord, const int& y_coord) {
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

bool game_over() {
	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			if (masked_field[i][j] == 9)
				return 1;
		}
	}

	return 0;
}

bool game_won() {
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

void mask_table() {
	masked_field = new int* [arr_size] {};

	for (int i = 0; i < arr_size; i++)
		masked_field[i] = new int[arr_size] {};

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			masked_field[i][j] = 10;
		}
	}
}

void populate_table(int mine_count) {
	srand(signed(time(NULL)));

	if (arr_size < 3 || arr_size > 9)
		return;

	playing_field = new int* [arr_size] {};
	for (int i = 0; i < arr_size; i++)
		playing_field[i] = new int[arr_size] {};

	int extended_row_col{ arr_size + 2 }; // size for buffer_table
	int** buffer_table = new int* [extended_row_col] {}; // tableArr with one empty row/column to each side
	for (int i = 0; i < extended_row_col; i++)
		buffer_table[i] = new int[extended_row_col] {};

	// Populate with mines

	while (mine_count) {
		int row_num{ rand() % arr_size };
		int col_num{ rand() % arr_size };

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
}

char* open_func(const int& x_coord, const int& y_coord) {
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

char* mark_func(const int& x_coord, const int& y_coord) {
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

char* unmark_func(const int& x_coord, const int& y_coord) {
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
