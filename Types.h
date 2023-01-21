#pragma once

enum class TokenType
{
	NONE,

	LITERAL, TEXT, COMMENT, INTEGER, FLOAT,

	DOT, COMMA, COLON, SEMI,

	LEFT_PARENTHESIS, RIGHT_PARENTHESIS,
	LEFT_SQUARE_BRACKET, RIGHT_SQUARE_BRACKET,
	LEFT_CURLY_BRACKET, RIGHT_CURLY_BRACKET,

	PLUS, MINUS, STAR, SLASH, DOUBLESTAR, DOUBLESLASH, VERTICAL, AMPER, CIRCUMFLEX, PERCENT, DOLLAR, AT, LEFT_BITSHIFT, RIGHT_BITSHIFT,
	PLUSEQ, MINUSEQ, STAREQ, SLASHEQ, DOUBLESTAREQ, DOUBLESLASHEQ, VERTICALEQ, AMPEREQ, CIRCUMFLEXEQ, PERCENTEQ, DOLLAREQ, ATEQ, LEFT_BITSHIFTEQ, RIGHT_BITSHIFTEQ,
	EQUALS, EQEQUALS,

	LT, GT, LTE, GTE, NOTEQ, EXCLAMATION_MARK
};

enum class IntType
{
	NONE, SPEC, HEX, DEC, OCT, BIN
};

enum class StringType
{
	NONE, SINGLE, DOUBLE
};

enum class StringBackSlash
{
	FALSE, TRUE
};

enum class CommentType
{
	NONE, ONELINE, MULTINLINE
};

enum class LongOperator
{
	FALSE, TRUE
};

struct TokenizerStatus
{
	wchar_t c;
	unsigned int line, symbol;
	TokenType token_type;
	IntType int_type;
	StringType string_type;
	StringBackSlash string_backslash;
	LongOperator long_operator;
	CommentType comment_type;
};
