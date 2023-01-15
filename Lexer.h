/*
#pragma once

#include <iostream>
#include "VirtualTree.h"

using namespace std;

class Lexer
{
private:
	enum SpecNumberType
	{
		HEX, OCT, BIN
	};
public:
	Lexer() = delete;
	Lexer(Lexer&) = delete;

	static VirtualTree* Tokenize(wchar_t* str) {
		auto tree = new VirtualTree();

		size_t length = wcslen(str);
		size_t lineno = 0;

		bool quote = false;
		bool backSlash = false;

		bool isSpecNumber = false;
		SpecNumberType num_type;
		bool isNumber = false;

		bool isLiteral = false;

		wstring buffer;
		buffer.reserve(64);

		for (size_t i = 0; i < length; ++i)
		{
			wchar_t chr = str[i];
			
			if (chr == L'\n') {
				++lineno;
				goto end;
			}
			if (chr == L'"' && !quote) {
				quote = true;
				goto end;
			}
			if (quote) {
				if (backSlash) {
					backSlash = false;
					switch (chr) {
					case L'\\': buffer += L'\\';
					case L'"': buffer += L'"';
					case L'\'': buffer += L'\'';
					case L'n': buffer += L'\n';
					}
					goto end;
				}
				else {
					if (chr == L'\\') {
						backSlash = true;
						goto end;
					}
					else if (chr == L'"') {
						quote = false;
						tree->push_back(STRING, buffer.c_str(), buffer.size());
						buffer.clear();
						goto end;
					}
					else {
						buffer += chr;
						goto end;
					}
				}
			}

			if (chr >= L'0' && chr <= L'9' && !isLiteral) {
				if (chr == L'0' && !isNumber) {
					isNumber = true;
					isSpecNumber = true;
					goto end;
				}
				else {
					isNumber = true;
					buffer += chr;
					goto end;
				}
			}

			if (((chr >= L'a' && chr <= L'f') || (chr >= L'A' && chr <= 'F')) && isSpecNumber && (num_type == HEX)) {
				buffer += chr;
				goto end;
			}

			if (isSpecNumber && chr == L'x') {
				num_type = HEX;
				goto end;
			}
			else if (isSpecNumber && chr == L'o') {
				num_type = OCT;
				goto end;
			}
			else if (isSpecNumber && chr == L'b') {
				num_type = BIN;
				goto end;
			}

			end:
			if ((chr == L' ' && !quote) || (i + 1 == length)) {
				if (isNumber) {
					isNumber = false;
					if (isSpecNumber) {
						isSpecNumber = false;
						if (num_type == HEX) {
							auto num = convert_hex2dec(buffer);
							tree->push_back(NUMBER, num.c_str(), num.size());
						}
						continue;
					}
					else {

						continue;
					}
					continue;
				}
				
				buffer.clear();
			}
		}

		return tree;
	}

	static wstring convert_hex2dec(wstring hex_num) {
		size_t result = 0;
		size_t power = 0;
		size_t foundation = 16;
		for (size_t i = hex_num.size() - 1; i >= 0; --i)
		{
			result += get_alphabet_number(hex_num[i]) * pow(foundation, power);
			power++;
		}
		wstring new_str;
		new_str += result;
		return new_str;
	}

	static size_t get_alphabet_number(wchar_t chr) {
		switch (chr)
		{
		case L'0': return 0;
		case L'1': return 1;
		case L'2': return 2;
		case L'3': return 3;
		case L'4': return 4;
		case L'5': return 5;
		case L'6': return 6;
		case L'7': return 7;
		case L'8': return 8;
		case L'9': return 9;
		case L'a': return 10;
		case L'A': return 10;
		case L'b': return 11;
		case L'B': return 11;
		case L'c': return 12;
		case L'C': return 12;
		case L'd': return 13;
		case L'D': return 13;
		case L'e': return 14;
		case L'E': return 14;
		case L'f': return 15;
		case L'F': return 15;
		default:
			return 0;
		}
	}
};

*/