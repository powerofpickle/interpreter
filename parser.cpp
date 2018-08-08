#include <iostream>

#include "parser.h"
#include "file_util.h"

void Parser::from_file(Parser& p, std::string path){
	p = Parser();
	FileUtil::read_file(path, p.text);
}

void Parser::print_whole_text(){
	std::cout << "Whole text:" << std::endl
	<< text << std::endl;
}

char Parser::read_next(){
	current_char = text.at(++pos);
	return current_char;
}
