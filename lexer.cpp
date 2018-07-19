#include "lexer.h"
#include <iostream>
#include "lexer.h"

Token::Token(TokenType type, std::string word){
	this->type = type;
	this->word = word;
}

Lexer::Lexer(std::string text){
	this->text = text;
	lexinate();
}

void Lexer::push_token(Token::TokenType type, std::string word){
	this->tokens.push_back(Token(type, word));
}

void Lexer::lexinate(){
	std::cout << "Lexinating..." << std::endl;


}
