#include <iostream>
#include <fstream>

#include "Lexer.h"
#include "Tools.h"

using namespace std;

std::wstring ReadFromFile(const wchar_t filename[]) {
	std::wifstream f(filename);
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();
	std::wstring s(size, ' ');
	f.seekg(0);
	f.read(&s[0], size);
	return s;
}

int wmain(int argc, const wchar_t* argv[]) {
	wchar_t* filename;
	if (argc > 1) filename = (wchar_t*)argv[1];
	else filename = (wchar_t*)L"Main.gr";

	auto file_text = ReadFromFile(filename);
	auto lexer = Tokenizer(file_text.c_str(), file_text.size());
	auto virtual_tree = lexer.tokenize();

	for (size_t i = 0; i < virtual_tree->size(); i++)
	{
		auto el = virtual_tree->at(i);
		if (el->type == TokenType::INTEGER) {
			auto data = (long long*)el->data;

			wcout << operator_to_wtext(el->type) << L" " << *data << endl;
		}
		else if (el->type == TokenType::FLOAT) {
			auto data = (long double*)el->data;

			wcout << operator_to_wtext(el->type) << L" " << *data << endl;
		}
		else {
			wcout << operator_to_wtext(el->type) << L" " << el->data << endl;
		}
	}

	delete virtual_tree;

	return 0;
}
