#pragma once
#include <vector>
#include "Types.h"


class Token {
public:
	unsigned int line, symbol;
	wchar_t* data;
	size_t size;
	TokenType type;

	Token(unsigned int line, unsigned int symbol, TokenType type, const wchar_t* data, size_t size) {
		this->line = line;
		this->symbol = symbol;
		this->type = type;
		this->size = size;
		this->data = new wchar_t[size + 1];
		this->data[size] = L'\0';
		for (size_t i = 0; i < size; i++) this->data[i] = data[i];
	}

	~Token() {
		if (size >= 0) delete[] data;
		size = 0;
	}
};

using VirtualTree = std::vector<Token*>;
