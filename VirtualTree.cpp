#include "VirtualTree.h"


Token::Token(TokenType type, size_t lineno, const wchar_t* data, size_t data_size) {
	this->type = type;
	this->lineno = lineno;
	this->data_size = data_size;

	this->data = new wchar_t[data_size + 1];
	for (size_t i = 0; i < data_size; i++)
		this->data[i] = data[i];

	this->data[data_size] = '\0';

}

Token::~Token() {
	if (this->data != nullptr && this->data_size > 0) {
		delete[] this->data;
		this->data = nullptr;
		this->data_size = 0;
	}
}
