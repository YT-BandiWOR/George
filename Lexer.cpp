#include "Lexer.h"

using std::wstring;

Tokenizer::Tokenizer(const wchar_t text[], size_t text_length)
{
	this->text_length = text_length;
	this->text = new wchar_t[text_length + 1];
	for (size_t i = 0; i < text_length; i++)
		this->text[i] = text[i];
	this->text[text_length] = L'\0';
	this->status = TokenizerStatus();
	status.c = L'\0';
	status.string_type = StringType::NONE;
	status.int_type = IntType::NONE;
	status.token_type = TokenType::NONE;
	status.string_backslash = StringBackSlash::FALSE;
	status.long_operator = LongOperator::FALSE;
	buffer = wstring();
	buffer.reserve(64);
	tree = nullptr;
}

VirtualTree* Tokenizer::tokenize()
{
	tree = new VirtualTree();
	status.symbol = 0;
	status.line = 1;
	for (size_t i = 0; i < text_length; ++i)
	{
		this->status.c = this->text[i];
		wchar_t c = this->status.c;
		if (c == L'\n') {
			this->status.line += 1;
			this->status.symbol = 1;
		}
		else this->status.symbol += 1;

		if (this->status.token_type != TokenType::TEXT &&
			this->status.token_type != TokenType::COMMENT &&
			this->status.long_operator == LongOperator::FALSE) {
			if (SwitchOperators()) continue;
		}

		switch (this->status.token_type)
		{
		case TokenType::NONE:
			if (c == L'0') {
				this->status.token_type = TokenType::INTEGER;
				this->status.int_type = IntType::SPEC;

			}
			else if (c == L'"') {
				this->status.token_type = TokenType::TEXT;
				this->status.string_type = StringType::DOUBLE;
			}
			else if (c == L'\'') {
				this->status.token_type = TokenType::TEXT;
				this->status.string_type = StringType::SINGLE;
			}
			else if (c >= L'0' && c <= L'9') {
				this->status.token_type = TokenType::INTEGER;
				this->status.int_type = IntType::DEC;
				buffer += c;
			}
			else {
				this->status.token_type = TokenType::LITERAL;
				this->buffer += c;
			}
			break;
		case TokenType::TEXT:
			if (c == L'\\' && status.string_backslash == StringBackSlash::FALSE) {
				status.string_backslash = StringBackSlash::TRUE;
			}
			else if (c == L'\\' && status.string_backslash == StringBackSlash::TRUE) {
				status.string_backslash = StringBackSlash::FALSE;
				buffer += L'\\';
			}
			else if (status.string_backslash == StringBackSlash::TRUE) {
				status.string_backslash = StringBackSlash::FALSE;
				if (c == L'n') buffer += L'\n';
				else buffer += c;
			}
			else if (status.string_backslash == StringBackSlash::FALSE) {
				if (c == L'"' && status.string_type == StringType::DOUBLE) {
					AppendToken();
					status.string_type = StringType::NONE;
				}
				else if (c == L'\'' && status.string_type == StringType::SINGLE) {
					AppendToken();
					status.string_type = StringType::NONE;
				}
				else {
					buffer += c;
				}
			}
			break;
		case TokenType::LITERAL:
			if (!SwitchOperators())
				buffer += c;
			break;
		case TokenType::INTEGER:
			if (c >= L'0' && c <= L'9')
			{
				buffer += c;
			}
			else if (c == L'.') {
				buffer += c;
				status.token_type = TokenType::FLOAT;
			}
			break;
		case TokenType::FLOAT:
			if (c >= L'0' && c <= L'9')
				buffer += c;
			else {
				// Error
			}
			break;
		case TokenType::PLUS:
			if (c == L'=') {
				AddLongOperator(TokenType::PLUSEQ);
			}
			else if (CheckSymbolsAfterOperator(c)) {
				// Error
			}
			break;
		case TokenType::MINUS:
			if (c == L'=') {
				AddLongOperator(TokenType::MINUSEQ);
			}
			else if (c >= L'0' && c <= L'9') {
				status.token_type = TokenType::INTEGER;
				status.int_type = IntType::DEC;
				buffer += L'-';
				buffer += c;
			}
			else if (CheckSymbolsAfterOperator(c)) {
				// Error
			}
			break;
		case TokenType::STAR:
			if (c == L'=') {
				AddLongOperator(TokenType::STAREQ);
			}
			else if (c == L'*') {
				status.token_type = TokenType::DOUBLESTAR;
			}
			else if (CheckSymbolsAfterOperator(c)) {
				// Error
			}
			break;
		case TokenType::SLASH:
			if (c == L'=') {
				AddLongOperator(TokenType::SLASHEQ);
			}
			else if (c == L'/') {
				status.token_type = TokenType::DOUBLESLASH;
			}
			else if (CheckSymbolsAfterOperator(c)) {
				// Error
			}
			break;
		case TokenType::LT:
			if (c == L'=') {
				AddLongOperator(TokenType::LTE);
			}
			else if (CheckSymbolsAfterOperator(c)) {
				// Error
			}
			break;
		case TokenType::GT:
			if (c == L'=') {
				AddLongOperator(TokenType::GTE);
			}
			else if (CheckSymbolsAfterOperator(c)) {
				// Error
			}
			break;
		case TokenType::AT:
			if (c == L'=') {
				AddLongOperator(TokenType::ATEQ);
			}
			else if (CheckSymbolsAfterOperator(c)) {
				// Error
			}
			break;
		case TokenType::EQUALS:
			if (c == L'=') {
				AddLongOperator(TokenType::EQEQUALS);
			}
			else if (CheckSymbolsAfterOperator(c)) {
				// Error
			}
			break;
		}
	}
	AppendToken();

	return tree;
}

void Tokenizer::AppendToken()
{
	if (status.token_type == TokenType::NONE) return;
	if (buffer.empty()) {
		if (status.token_type == TokenType::LITERAL) return;
		else if (status.token_type == TokenType::INTEGER) {
			auto result = new long long[1];
			*result = 0;
			tree->push_back(new Token(status.line, status.symbol, status.token_type, (wchar_t*)result, sizeof(long long) / sizeof(wchar_t)));
		}
		else {
			tree->push_back(new Token(status.line, status.symbol, status.token_type, nullptr, 0));
		}
	}
	else {
		if (status.token_type == TokenType::INTEGER) {
			auto result = new long long[1];
			*result = ConvertWstringToLong(buffer.c_str(), buffer.size(), status.int_type);
			tree->push_back(new Token(status.line, status.symbol, status.token_type, (wchar_t*)result, T1_as_T2_ratio(long long, wchar_t)));
		}
		else if (status.token_type == TokenType::FLOAT) {
			auto result = new long double[1];
			*result = ConvertWstringToFloat(buffer.c_str(), buffer.size());
			tree->push_back(new Token(status.line, status.symbol, status.token_type, (wchar_t*)result, T1_as_T2_ratio(long double, wchar_t)));
		}
		else {
			tree->push_back(new Token(status.line, status.symbol, status.token_type, buffer.c_str(), buffer.size()));
		}
	}

	buffer.clear();
	status.token_type = TokenType::NONE;
	status.int_type = IntType::NONE;
	status.long_operator = LongOperator::FALSE;
	status.string_backslash = StringBackSlash::FALSE;
}

void Tokenizer::AddToken(TokenType type)
{
	AppendToken();
	this->status.token_type = type;
	AppendToken();
}

void Tokenizer::SetLongOperator(TokenType type)
{
	this->status.long_operator = LongOperator::TRUE;
	AppendToken();
	this->status.token_type = type;
}

void Tokenizer::AddLongOperator(TokenType type)
{
	this->status.token_type = type;
	this->status.long_operator = LongOperator::FALSE;
	AppendToken();
}

bool Tokenizer::SwitchOperators()
{
	switch (status.c)
	{
	case L'\n':
	case L' ':
	case L'\t':
		AppendToken();
		return true;
	case L'(':
		AddToken(TokenType::LEFT_PARENTHESIS);
		return true;
	case L')':
		AddToken(TokenType::RIGHT_PARENTHESIS);
		return true;
	case L'[':
		AddToken(TokenType::LEFT_SQUARE_BRACKET);
		return true;
	case L']':
		AddToken(TokenType::RIGHT_SQUARE_BRACKET);
		return true;
	case L'{':
		AddToken(TokenType::LEFT_CURLY_BRACKET);
		return true;
	case L'}':
		AddToken(TokenType::RIGHT_CURLY_BRACKET);
		return true;
	case L'.':
		if (status.token_type == TokenType::INTEGER) {
			status.token_type = TokenType::FLOAT;
			buffer += L'.';
			return false;
		}
		AddToken(TokenType::DOT);
		return true;
	case L',':
		AddToken(TokenType::COMMA);
		return true;
	case L':':
		AddToken(TokenType::COLON);
		return true;
	case L';':
		AddToken(TokenType::SEMI);
		return true;
	case L'=':
		SetLongOperator(TokenType::EQUALS);
		return true;
	case L'!':
		SetLongOperator(TokenType::EXCLAMATION_MARK);
		return true;
	case L'<':
		SetLongOperator(TokenType::LT);
		return true;
	case L'>':
		SetLongOperator(TokenType::GT);
		return true;
	case L'@':
		SetLongOperator(TokenType::AT);
		return true;
	case L'|':
		SetLongOperator(TokenType::VERTICAL);
		return true;
	case L'&':
		SetLongOperator(TokenType::AMPER);
		return true;
	case L'^':
		SetLongOperator(TokenType::CIRCUMFLEX);
		return true;
	case L'%':
		SetLongOperator(TokenType::PERCENT);
		return true;
	case L'+':
		SetLongOperator(TokenType::PLUS);
		return true;
	case L'-':
		SetLongOperator(TokenType::MINUS);
		return true;
	case L'*':
		SetLongOperator(TokenType::STAR);
		return true;
	case L'/':
		SetLongOperator(TokenType::SLASH);
		return true;

	}
	return false;
}

bool Tokenizer::IsOperator(wchar_t c)
{
	switch (c)
	{
	case L'+': return true;
	case L'-': return true;
	case L'*': return true;
	case L'/': return true;
	case L'%': return true;
	case L'^': return true;
	case L'$': return true;
	case L'@': return true;
	case L'<': return true;
	case L'>': return true;
	case L'!': return true;
	case L'=': return true;
	default:
		return false;
	}
}

bool Tokenizer::CheckSymbolsAfterOperator(wchar_t c)
{
	if (!IsOperator(c)) {
		if (c >= L'1' && c <= L'9') {
			status.token_type = TokenType::INTEGER;
			buffer += c;
		}
		else if (c == L'0') {
			status.token_type = TokenType::INTEGER;
			status.int_type = IntType::SPEC;
		}
		else if (c == L'"') {
			status.token_type = TokenType::TEXT;
			status.string_type = StringType::DOUBLE;
		}
		else if (c == L'\'') {
			status.token_type = TokenType::TEXT;
			status.string_type = StringType::SINGLE;
		}
		else if (c == L' ') {
			AppendToken();
		}
		else {
			AppendToken();
			status.token_type = TokenType::LITERAL;
			buffer += c;
		}
		return true;
	}
	else {
		return false;
	}
}

long long Tokenizer::ConvertWstringToLong(const wchar_t str[], size_t length, IntType type)
{
	switch (type)
	{
	case IntType::HEX: return ConvertWstringNumToDec(str, length, 16);
	case IntType::DEC: return ConvertWstringNumToDec(str, length, 10);
	case IntType::OCT: return ConvertWstringNumToDec(str, length, 8);
	case IntType::BIN: return ConvertWstringNumToDec(str, length, 2);
	case IntType::NONE: break;
	case IntType::SPEC: break;
	default: break;
	}
	return 0;
}

long double Tokenizer::ConvertWstringToFloat(const wchar_t str[], size_t length)
{
	long double result = 0;
	size_t min_str_index = 0;
	bool negative = false;

	int power = -1;
	for (size_t i = 0; str[i] != L'.' && str[i] != L'\0'; ++i) power++;
	
	if (str[0] == L'-') {
		min_str_index++;
		negative = true;
	}
	for (size_t i = 0; i < length; i++)
	{
		auto c = str[i];
		if (c == L'.' || c == L',') {
			for (size_t j = i + 1; j < length; j++)
			{
				c = str[j];
				long double inc = 0.1;
				result += ConvertWcharToNum(c) * inc;
				inc /= 10;
			}
			break;
		}
		else {
			result += ConvertWcharToNum(c) * pow(10, power);
			power--;
		}
	}

	return (negative) ? -result : result;
}

long long Tokenizer::ConvertWstringNumToDec(const wchar_t str[], size_t length, unsigned int foundation)
{
	long long result = 0;
	size_t min_str_index = 0;
	bool negative = false;
	size_t power = length - 1;
	if (str[0] == L'-') {
		min_str_index++;
		negative = true;
		power--;
	};
	for (size_t i = min_str_index; i < length; i++)
	{
		result += ConvertWcharToNum(str[i]) * pow(foundation, power);
		power--;
	}

	return (negative) ? -result: result;
}

unsigned int Tokenizer::ConvertWcharToNum(wchar_t c)
{
	switch (c)
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
	case L'b': return 11;
	case L'c': return 12;
	case L'd': return 13;
	case L'e': return 14;
	case L'f': return 15;
	case L'A': return 10;
	case L'B': return 11;
	case L'C': return 12;
	case L'D': return 13;
	case L'E': return 14;
	case L'F': return 15;
	default: return 0;
	}
}
