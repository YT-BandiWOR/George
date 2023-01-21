#include "Tools.h"

const wchar_t* operator_to_wtext(TokenType type)
{
	switch (type)
	{
	case TokenType::NONE: return L"NONE";
	case TokenType::LITERAL: return L"LITERAL";
	case TokenType::TEXT: return L"TEXT";
	case TokenType::COMMENT: return L"COMMENT";
	case TokenType::INTEGER: return L"INTEGER";
	case TokenType::FLOAT: return L"FLOAT";
	case TokenType::DOT: return L"DOT";
	case TokenType::COMMA: return L"COMMA";
	case TokenType::COLON: return L"COLON";
	case TokenType::SEMI: return L"SEMI";
	case TokenType::LEFT_PARENTHESIS: return L"LEFT_PARENTHESIS";
	case TokenType::RIGHT_PARENTHESIS: return L"RIGHT_PARENTHESIS";
	case TokenType::LEFT_SQUARE_BRACKET: return L"LEFT_SQUARE_BRACKET";
	case TokenType::RIGHT_SQUARE_BRACKET: return L"RIGHT_SQUARE_BRACKET";
	case TokenType::LEFT_CURLY_BRACKET: return L"LEFT_CURLY_BRACKET";
	case TokenType::RIGHT_CURLY_BRACKET: return L"RIGHT_CURLY_BRACKET";
	case TokenType::PLUS: return L"PLUS";
	case TokenType::MINUS: return L"MINUS";
	case TokenType::STAR: return L"STAR";
	case TokenType::SLASH: return L"SLASH";
	case TokenType::DOUBLESTAR: return L"DOUBLESTAR";
	case TokenType::DOUBLESLASH: return L"DOUBLESLASH";
	case TokenType::VERTICAL: return L"VERTICAL";
	case TokenType::AMPER: return L"AMPER";
	case TokenType::CIRCUMFLEX: return L"CIRCUMFLEX";
	case TokenType::PERCENT: return L"PERCENT";
	case TokenType::DOLLAR: return L"DOLLAR";
	case TokenType::AT: return L"AT";
	case TokenType::LEFT_BITSHIFT: return L"LEFT_BITSHIFT";
	case TokenType::RIGHT_BITSHIFT: return L"RIGHT_BITSHIFT";
	case TokenType::PLUSEQ: return L"PLUSEQ";
	case TokenType::MINUSEQ: return L"MINUSEQ";
	case TokenType::STAREQ: return L"STAREQ";
	case TokenType::SLASHEQ: return L"SLASHEQ";
	case TokenType::DOUBLESTAREQ: return L"DOUBLESTAREQ";
	case TokenType::DOUBLESLASHEQ: return L"DOUBLESLASHEQ";
	case TokenType::VERTICALEQ: return L"VERTICALEQ";
	case TokenType::AMPEREQ: return L"AMPEREQ";
	case TokenType::CIRCUMFLEXEQ: return L"CIRCUMFLEXEQ";
	case TokenType::PERCENTEQ: return L"PERCENTEQ";
	case TokenType::DOLLAREQ: return L"DOLLAREQ";
	case TokenType::ATEQ: return L"ATEQ";
	case TokenType::LEFT_BITSHIFTEQ: return L"LEFT_BITSHIFTEQ";
	case TokenType::RIGHT_BITSHIFTEQ: return L"RIGHT_BITSHIFTEQ";
	case TokenType::EQUALS: return L"EQUALS";
	case TokenType::EQEQUALS: return L"EQEQUALS";
	case TokenType::LT: return L"LT";
	case TokenType::GT: return L"GT";
	case TokenType::LTE: return L"LTE";
	case TokenType::GTE: return L"GTE";
	case TokenType::NOTEQ: return L"NOTEW";
	case TokenType::EXCLAMATION_MARK: return L"!";
	default: return L"unknown";
	}
}
