#include "ast_expression.h"
#include <iostream>

using namespace ast;

Expression* Expression::parse_next(Parser* p, std::vector<char>& delimiters){
	std::cout << "parsing next expression" << std::endl;
	return nullptr;

}

Node* Expression::eval(){
	std::cout << "Error: expression.cpp" << std::endl;
	return nullptr;
}

void Expression::set_parent(Expression* parent){
	this->parent = parent;
}

void Expression::set_child(Expression* child){

}

void Expression::parse(Parser* p){
	std::cout << "Error: expression.cpp" << std::endl;
}

//ExpressionContainer

void ExpressionContainer::parse(Parser* p, std::vector<char>& delimiters){

}

//ExpressionList

void ExpressionList::parse(Parser* p){
	std::cout << "parsing ExpressionList" << std::endl;
	std::vector<char> delimiters;
	delimiters.push_back('\n');
	ExpressionContainer* ec = new ExpressionContainer();
	ec->set_parent(this);
	ec->parse(p, delimiters);
	std::cout << "Error: expression.cpp" << std::endl;
}
