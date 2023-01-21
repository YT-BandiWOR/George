#include <iostream>
#include <fstream>

#include "Lexer.h"
#include "Tools.h"

using namespace std;

std::string ReadFromFile(const char filename[]) {
	std::ifstream f(filename);
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();
	std::string s(size, ' ');
	f.seekg(0);
	f.read(&s[0], size);
	return s;
}


int main(int argc, const char* argv[]) {
	char* filename;

	if (argc > 1) {
		filename = (char*)argv[1];
	}
	else {
		filename = (char*)"Main.gr";
	}


	string str = ReadFromFile(filename);
	std::wstring wstr(str.begin(), str.end());
	wchar_t* data = new wchar_t[wstr.size() + 1];
	for (size_t i = 0; i < wstr.size(); i++)
	{
		data[i] = wstr[i];
	}
	data[wstr.size()] = '\0';

	auto lexer = Tokenizer(data, wstr.size());
	auto virtual_tree = lexer.tokenize();

	delete[] data;

	for (size_t i = 0; i < virtual_tree->size(); i++)
	{
		auto el = virtual_tree->at(i);
		if (el->type == TokenType::INTEGER) {
			wcout << operator_to_wtext(el->type) << L" " << (long long)*el->data << endl;
		}
		else {
			wcout << operator_to_wtext(el->type) << L" " << el->data << endl;
		}
	}

	delete virtual_tree;


	return 0;
}
