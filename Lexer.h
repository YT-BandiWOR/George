#pragma once
#include <iostream>
#include "Types.h"
#include "VirtualTree.h"

#define T1_as_T2_ratio(T1, T2) (sizeof(T1)/sizeof(T2))


class Tokenizer
{
private:
	wchar_t* text;
	size_t text_length;
	TokenizerStatus status;
	std::wstring buffer;
	VirtualTree* tree;

	void AppendToken();
	void AddToken(TokenType type);
	void SetLongOperator(TokenType type);
	void AddLongOperator(TokenType type);
	bool SwitchOperators();
	bool IsOperator(wchar_t c);
	bool CheckSymbolsAfterOperator(wchar_t c);
	long long ConvertWstringToLong(const wchar_t str[], size_t length, IntType type);
	long double ConvertWstringToFloat(const wchar_t str[], size_t length);
	long long ConvertWstringNumToDec(const wchar_t str[], size_t length, unsigned int foundation);
	unsigned int ConvertWcharToNum(wchar_t c);

public:
	Tokenizer(const wchar_t text[], size_t text_length);
	VirtualTree* tokenize();
};