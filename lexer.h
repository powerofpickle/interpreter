#pragma once
#include <string>
#include <vector>

class Token{
public:
	enum TokenType{
		EXPRESSION_START,
		EXPRESSION_END
	};
	TokenType type;
	std::string word;
	Token(TokenType type, std::string word);
};

class Lexer{
private:
	std::string text;
	std::vector<Token> tokens;
public:
	Lexer(std::string text);
	void push_token(Token::TokenType type, std::string word);
	void lexinate();
};
