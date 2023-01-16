#include "Tools.h"



wchar_t* token_type_to_wcharptr(TokenType type) {
	wchar_t* str;

	switch (type)
	{
	case LITER:
		str = (wchar_t*)L"LITER";
		break;
	case TEXT:
		str = (wchar_t*)L"TEXT";
		break;
	case INTEGER:
		str = (wchar_t*)L"INTEGER";
		break;
	case FLOAT:
		str = (wchar_t*)L"FLOAT";
		break;
	case OP_DOT:
		str = (wchar_t*)L"OP_DOT";
		break;
	case OP_COMMA:
		str = (wchar_t*)L"OP_COMMA";
		break;
	case OP_ROUND_BRACKET_OPENED:
		str = (wchar_t*)L"OP_ROUND_BRACKET_OPENED";
		break;
	case OP_ROUND_BRACKET_CLOSED:
		str = (wchar_t*)L"OP_ROUND_BRACKET_CLOSED";
		break;
	case OP_SQUARE_BRACKET_OPENED:
		str = (wchar_t*)L"OP_SQUARE_BRACKET_OPENED";
		break;
	case OP_SQUARE_BRACKET_CLOSED:
		str = (wchar_t*)L"OP_SQUARE_BRACKET_CLOSED";
		break;
	case OP_CURLY_BRACKET_OPENED:
		str = (wchar_t*)L"OP_CURLY_BRACKET_OPENED";
		break;
	case OP_CURLY_BRACKET_CLOSED:
		str = (wchar_t*)L"OP_CURLY_BRACKET_CLOSED";
		break;
	case OP_COMMENT:
		str = (wchar_t*)L"OP_COMMENT";
		break;
	case OP_ADD:
		str = (wchar_t*)L"OP_ADD";
		break;
	case OP_SUB:
		str = (wchar_t*)L"OP_SUB";
		break;
	case OP_MUL:
		str = (wchar_t*)L"OP_MUL";
		break;
	case OP_DIV:
		str = (wchar_t*)L"OP_DIV";
		break;
	case OP_MOD:
		str = (wchar_t*)L"OP_MOD";
		break;
	case OP_POW:
		str = (wchar_t*)L"OP_POW";
		break;
	case OP_EQ:
		str = (wchar_t*)L"OP_EQ";
		break;
	case OP_ASSIGN:
		str = (wchar_t*)L"OP_ASSIGN";
		break;
	case OP_LT:
		str = (wchar_t*)L"OP_LT";
		break;
	case OP_GT:
		str = (wchar_t*)L"OP_GT";
		break;
	case OP_LTE:
		str = (wchar_t*)L"OP_LTE";
		break;
	case OP_GTE:
		str = (wchar_t*)L"OP_GTE";
		break;
	case OP_COLON:
		str = (wchar_t*)L"OP_COLON";
		break;
	case OP_SEMICOLON:
		str = (wchar_t*)L"OP_SEMICOLON";
		break;
	case NEW_LINE:
		str = (wchar_t*)L"NEW_LINE";
		break;
	default:
		str = (wchar_t*)L"UNKNOWN";
		break;
	}
	return str;
}
