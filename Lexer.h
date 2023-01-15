#pragma once

#include "VirtualTree.h"
#include <string>
#include <vector>

using std::wstring;
using std::vector;

class Lexer
{
public:
	static vector<Token*>* Tokenize(wchar_t* str, size_t length);

	static void AppendToken(vector<Token*>* tree, size_t lineno, wstring& buffer, LexerState& state, IntNumberType number_type = DEC);
	static void AppendToken(vector<Token*>* tree, size_t lineno, TokenType type);

	static wchar_t* convert_num2dec(wstring& buffer, size_t foundation);
	static wchar_t* convert_num2wchar(size_t num);

	static size_t get_num_size(size_t num);
	static size_t get_alphabet_number(wchar_t chr);
};