#include "VirtualTree.h"


Token::Token(TokenType type, size_t lineno, const wchar_t* data, size_t data_size) {
	this->next = nullptr;
	this->type = type;
	this->lineno = lineno;
	this->data_size = data_size;
	this->data = new wchar_t[data_size + 1];
	for (size_t i = 0; i < data_size; i++)
		this->data[i] = data[i];
	this->data[data_size] = '\0';
}

void VirtualTree::push_back(TokenType type, size_t lineno, const wchar_t* data, size_t data_size) {
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

Token* VirtualTree::at(size_t index) {
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