#pragma once
#include <vector>

#include "node.h"
#include "parser.h"

namespace ast{

class Expression{
public:

	static Expression* parse_next(Parser* p, std::vector<char>& delimiters);

	Expression* parent = nullptr;

	void set_parent(Expression* parent);
	virtual void set_child(Expression* child);

	virtual void parse(Parser* p);
	virtual Node* eval();

};

class ExpressionContainer : public Expression{
public:

	Expression* child= nullptr;

	virtual void parse(Parser* p, std::vector<char>& delimiters);
	
};

class ExpressionList : public Expression{
public:
	std::vector<Expression*> expressions;
	virtual void parse(Parser* p);

	
};



};
