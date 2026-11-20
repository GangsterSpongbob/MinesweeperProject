#include "funcs_header.h"
#include <iostream> //

void set_message(char* msg, const char inp[]) {
	clear_str(msg);
	int index{};
	while (inp[index] != '\0') {
		msg[index] = inp[index];
		index++;
	}
}

// fills string with \0 characters
void clear_str(char* clr) {
	for (int i = 0; i < max_array_length; i++)
		clr[i] = '\0';
}

bool compare(const char* to_compare, const char* comp) {
	int index{};
	while (to_compare[index] != '\0' && comp[index] != '\0') {
		if (to_compare[index] != comp[index])
			return 0;
		index++;
	}
	return 1;
}

bool check_int(const char* check) {
	if (*check == '\0') // empty string cannot be number
		return 0;

	int index{ *check == '-' ? 1 : 0 };

	while (check[index] != '\0') {
		if (!(check[index] >= '0' && check[index] <= '9'))
			return 0;
		index++;
	}

	return 1;
}

int str_to_int(const char* to_int) {
	if (!check_int(to_int))
		return 0;

	int index{}, total{}, negative{ 1 };
	if (to_int[index] == '-') {
		negative = -1;
		index++;
	}

	while (to_int[index] != '\0') {
		total = 10 * total + (to_int[index] - '0');
		index++;
	}

	return negative * total;
}
