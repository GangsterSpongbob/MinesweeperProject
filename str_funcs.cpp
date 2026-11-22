#include "funcs_header.h"

#include <iostream>

using std::cin;

Line& Line::assign(const char* str) {
	int index{};
	while (str[index] != '\0' && index < max_array_length) {
		line[index] = str[index];
		index++;
	}

	return *this;
}

Line::Line(const char* str) {
	this->assign(str);
}

char& Line::operator[](int index) {
	return line[index];
}

const char& Line::operator[](int index) const {
	return line[index];
}

Line& Line::operator=(const char* str) {
	return this->assign(str);
}

Line& Line::operator=(const Line& other) {
	return this->assign(other.line);
}

bool Line::operator==(const char* str) const {
	int index{};
	while (line[index] != '\0' && str[index] != '\0' && index < max_array_length) {
		if (line[index] != str[index])
			return false;
		index++;
	}
	return true;
}

bool Line::operator==(const Line& other) const {
	return *this == other.line;
}

bool operator==(const char* a, const Line& b) {
	return b == a;
}

bool Line::check_int() {
	char* check = this->line;

	if (check[0] == '\0') // empty string cannot be number
		return 0;

	int index{ check[0] == '-' ? 1 : 0 };

	while (check[index] != '\0') {
		if (!(check[index] >= '0' && check[index] <= '9' && index < max_array_length))
			return 0;
		index++;
	}

	return 1;
}

int Line::to_int() {
	char* to_int = this->line;

	if (!this->check_int())
		return -1;

	int index{}, total{}, polarity{ 1 };
	if (to_int[index] == '-') {
		polarity = -1;
		index++;
	}

	while (to_int[index] != '\0' && index < max_array_length) {
		total = 10 * total + (to_int[index] - '0');
		index++;
	}

	return polarity * total;
}

Line Line::get_line() {
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

Line Line::get_word() {
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
