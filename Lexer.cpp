#include "Lexer.h"



vector<Token*>* Lexer::Tokenize(wchar_t* str, size_t length) {
	auto tree = new vector<Token*>();

	size_t lineno = 0;
	LexerState state = ST_NONE;
	IntNumberType spec_integer_type = DEC;
	wstring buf;
	buf.reserve(64);

	bool isBackSlash = false;

	for (size_t i = 0; i < length; i++)
	{
		wchar_t c = str[i];
		if (c == L'\n') lineno++;

		if (c == L'(') {
			AppendToken(tree, lineno, buf, state, spec_integer_type);
			AppendToken(tree, lineno, OP_ROUND_BRACKET_OPENED);
			continue;
		}
		else if (c == L')') {
			AppendToken(tree, lineno, buf, state, spec_integer_type);
			AppendToken(tree, lineno, OP_ROUND_BRACKET_CLOSED);
			continue;
		}
		else if (c == L'[') {
			AppendToken(tree, lineno, buf, state, spec_integer_type);
			AppendToken(tree, lineno, OP_SQUARE_BRACKET_OPENED);
			continue;
		}
		else if (c == L']') {
			AppendToken(tree, lineno, buf, state, spec_integer_type);
			AppendToken(tree, lineno, OP_SQUARE_BRACKET_CLOSED);
			continue;
		}
		else if (c == L'{') {
			AppendToken(tree, lineno, buf, state, spec_integer_type);
			AppendToken(tree, lineno, OP_CURLY_BRACKET_OPENED);
			continue;
		}
		else if (c == L'}') {
			AppendToken(tree, lineno, buf, state, spec_integer_type);
			AppendToken(tree, lineno, OP_CURLY_BRACKET_CLOSED);
			continue;
		}

		switch (state)
		{
		case ST_NONE:  //   
		{
			switch (c)
			{
			case L' ': continue;
			case L'#': state = ST_COMMENT; continue;
			case L'\'': state = ST_TEXT; continue;
			case L'\"': state = ST_DOUBLETEXT; continue;
			case L'0': state = ST_SPECINTEGER; continue;
			}

			if (c >= L'0' && c <= L'9') {
				state = ST_INTEGER;
				buf += c;
			}

			continue;
		}
		break;
		case ST_COMMENT:   // #...
		{
			if (c == L'\n') {
				AppendToken(tree, lineno - 1, buf, state);
				break;
			}
			buf += c;
		}
		break;
		case ST_TEXT:       // '...'
		case ST_DOUBLETEXT: // "..."
			if (isBackSlash) {
				isBackSlash = false;
				if (c == L'\\') buf += c;
				else if (c == L'n') buf += c;
				else if (c == L'"') buf += c;
				else if (c == L'\'') buf += c;
			}
			else {
				if (c == L'\\') {
					isBackSlash = true;
				}
				else {
					if ((state == ST_DOUBLETEXT && c == L'"') || (state == ST_TEXT && c == L'\'')) {
						AppendToken(tree, lineno, buf, state);
					}
					else {
						buf += c;
					}
				}
			}
			break;
		case ST_SPECINTEGER:
			switch (c)
			{
			case L'\n':
				AppendToken(tree, lineno, buf, state, spec_integer_type);
				spec_integer_type = DEC;
				break;
			case L'0': {
				spec_integer_type = DEC;
				state = ST_INTEGER;
			}
					 continue;
			case L'X':
			case L'x': spec_integer_type = HEX; continue;
			case L'B':
			case L'b': spec_integer_type = BIN; continue;
			case L'O':
			case L'o': spec_integer_type = OCT; continue;
			default: break; // Error
			}

			if (
				((spec_integer_type == HEX) && ((c >= L'0' && c <= L'9') || (c >= L'a' && c <= L'f') || (c >= L'A' && c <= 'F'))) ||
				((spec_integer_type == OCT) && (c >= '0' && c <= '7')) ||
				((spec_integer_type == BIN) && (c == L'0' || c == L'1'))
				) {
				buf += c;
				break;
			}
			else {
				// Error
			}
		break;
		
		case ST_INTEGER:
			switch (c)
			{
			case L'\n':
				AppendToken(tree, lineno, buf, state);
				break;
			case L'.':
				state = ST_FLOAT;
				continue;
			default: break;
			}

			if (c >= L'0' && c <= L'9') {
				buf += c;
				continue;
			}
			else {
				// Error
			}
		}
	}

	if (!buf.empty() && state != ST_NONE) {
		AppendToken(tree, lineno, buf, state, spec_integer_type);
	}

	return tree;
}

void Lexer::AppendToken(vector<Token*>* tree, size_t lineno, wstring& buffer, LexerState& state, IntNumberType number_type) {
	switch (state)
	{
	case ST_COMMENT:
		tree->push_back(new Token(OP_COMMENT, lineno, buffer.c_str(), buffer.size()));
		break;
	case ST_DOUBLETEXT:
	case ST_TEXT:
		tree->push_back(new Token(TEXT, lineno, buffer.c_str(), buffer.size()));
		break;
	case ST_INTEGER:
	case ST_SPECINTEGER:
		wchar_t* num_str = nullptr;
		if (number_type == HEX)
			num_str = convert_num2dec(buffer, 16);
		else if (number_type == BIN)
			num_str = convert_num2dec(buffer, 2);
		else if (number_type == OCT)
			num_str = convert_num2dec(buffer, 8);
		else
			num_str = convert_num2dec(buffer, 10);

		tree->push_back(new Token(INTEGER, lineno, num_str, wcslen(num_str)));
		delete[] num_str;
		break;
	}
	buffer.clear();
	state = ST_NONE;
}



void Lexer::AppendToken(vector<Token*>* tree, size_t lineno, TokenType type) {
	tree->push_back(new Token(type, lineno, nullptr, 0));
}

wchar_t* Lexer::convert_num2dec(wstring& buffer, size_t foundation) {
	size_t result = 0;
	size_t power = buffer.size() - 1;
	for (size_t i = 0; i < buffer.size(); ++i)
	{
		result += get_alphabet_number(buffer[i]) * pow(foundation, power);
		--power;
	}
	return convert_num2wchar(result);
}

wchar_t* Lexer::convert_num2wchar(size_t num) {
	wchar_t* n = new wchar_t[get_num_size(num) + 1];
	n[get_num_size(num)] = '\0';

	size_t f = 0;
	size_t index = get_num_size(num) - 1;
	while (num) {
		f = num % 10;
		num /= 10;
		switch (f)
		{
		case 1: n[index] = L'1'; break;
		case 2: n[index] = L'2'; break;
		case 3: n[index] = L'3'; break;
		case 4: n[index] = L'4'; break;
		case 5: n[index] = L'5'; break;
		case 6: n[index] = L'6'; break;
		case 7: n[index] = L'7'; break;
		case 8: n[index] = L'8'; break;
		case 9: n[index] = L'9'; break;
		default: n[index] = L'0'; break;
		}
		--index;
	}
	return n;
}

size_t Lexer::get_num_size(size_t num) {
	size_t count = 0;
	while (num) {
		num /= 10;
		count++;
	}
	return count;
}

size_t Lexer::get_alphabet_number(wchar_t chr) {
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