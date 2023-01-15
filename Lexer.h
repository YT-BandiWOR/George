#pragma once

#include "VirtualTree.h"
#include <string>

using std::wstring;

class Lexer
{
public:
	static VirtualTree* Tokenize(wchar_t* str, size_t length);

	static void AppendToken(VirtualTree* tree, size_t lineno, wstring& buffer, LexerState& state, IntNumberType number_type = DEC);
	static void AppendToken(VirtualTree* tree, size_t lineno, LexerState& state);

	static wchar_t* convert_num2dec(wstring& buffer, size_t foundation);
	static wchar_t* convert_num2wchar(size_t num);

	static size_t get_num_size(size_t num);
	static size_t get_alphabet_number(wchar_t chr);
};