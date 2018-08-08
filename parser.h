#pragma once
#include <iostream>
#include <string>


class Parser{
public:

	static void from_file(Parser& p, std::string path);

	std::string text;
	char current_char;
	int pos = 0;
	
	void print_whole_text();
	char read_next();
};
