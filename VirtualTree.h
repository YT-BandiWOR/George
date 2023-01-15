#pragma once


enum TokenType
{
	LITER, TEXT, INTEGER, FLOAT,
	OP_DOT, OP_COMMA,
	OP_ROUND_BRACKET_OPENED, OP_ROUND_BRACKET_CLOSED,
	OP_SQUARE_BRACKET_OPENED, OP_SQUARE_BRACKET_CLOSED,
	OP_CURLY_BRACKET_OPENED, OP_CURLY_BRACKET_CLOSED,
	OP_COMMENT,

	OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_POW,

	OP_EQ, OP_ASSIGN, OP_LT, OP_GT, OP_LTE, OP_GTE,

	OP_COLON, OP_SEMICOLON,
	
	NEW_LINE
};

enum IntNumberType
{
	HEX, DEC, OCT, BIN
};

enum LexerState
{
	ST_NONE, ST_LITER, ST_TEXT, ST_DOUBLETEXT, ST_INTEGER, ST_SPECINTEGER, ST_FLOAT, ST_COMMENT, ST_OPERATOR
};

class Token
{
public:
	TokenType type;
	size_t lineno;
	wchar_t* data;
	size_t data_size;
	Token* next = nullptr;

	Token(TokenType type, size_t lineno, const wchar_t* data, size_t data_size) {
		this->type = type;
		this->lineno = lineno;
		this->data_size = data_size;
		this->data = new wchar_t[data_size + 1];
		for (size_t i = 0; i <= data_size; i++)
			this->data[i] = data[i];
	}
};

class VirtualTree
{
private:
	Token* head = nullptr;
	size_t _size = 0;
public:
	void push_back(TokenType type, size_t lineno, const wchar_t* data, size_t data_size) {
		if (_size == 0) {
			Token* new_token = new Token(type, lineno, data, data_size);
			head = new_token;
			_size++;
		}
		else {
			auto last_element = head;
			while (last_element->next != nullptr)
				last_element = last_element->next;

			auto new_token = new Token(type, lineno, data, data_size);
			last_element->next = new_token;
			_size++;
		}
	}

	Token* at(size_t index) {
		if (index < 0 || index >= _size || _size == 0) return nullptr;
		Token* element = head;
		size_t _ind = 0;
		while (index != _ind)
		{
			element = element->next;
			_ind++;
		}
		return element;
	}
	size_t size() { return _size; }
};