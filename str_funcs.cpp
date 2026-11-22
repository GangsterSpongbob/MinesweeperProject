#include "funcs_header.h"
#include <iostream> //

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

char& Line::operator[](const int& index) {
	return line[index];
}

const char& Line::operator[](const int& index) const {
	return line[index];
}

Line& Line::operator=(const char* str) {
	return this->assign(str);
}

Line& Line::operator=(const Line& other) {
	return this->assign(other.line);
}

bool Line::operator==(const char* str) {
	int index{};
	while (line[index] != '\0' && str[index] != '\0' && index < max_array_length) {
		if (line[index] != str[index])
			return false;
		index++;
	}
	return true;
}

bool Line::operator==(const Line& other) {
	return *this == other.line;
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
		return 0;

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
