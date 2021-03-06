#pragma once

#include <assert.h>
#include <stdio.h>
#include <iostream>

enum Type;

class NodeValue
{
public:
	NodeValue();
	NodeValue(Type type, char data[16]);//// 
	NodeValue(Type type, int data);
	~NodeValue();

	bool Ok() const;
	void Dump() const;
	void Dump(FILE *log) const;

	Type type_;
	int intData_;
	char strData_[16];
};

enum Type
{
	EMPTY,
	NUMBER,
	VARIABLE,
	OPERAND,
	PLUS_MINUS,
	MUL_DIV,
	BRACKET,
	BRACE,
	EQUAL,
	COMPARISON,
	ASSIGN,
	IF,
	ELSE,
	WHILE,
	FUNC,
	RET,
	COMMA,
	COMMA_LOWER,
	UNKNOWN,
	ERRORS
};

NodeValue::NodeValue() :
	type_(EMPTY),
	intData_(0)
	//strData_({})
{
	memset(strData_, 0, 16);
}

NodeValue::NodeValue(Type type, char data[16]) :
	type_(type),
	intData_(0)
	//strData_({})
{
	strcpy_s(strData_, 16, data);
}

NodeValue::NodeValue(Type type, int data) :
	type_(type),
	intData_(data)
	//strData_({})
{
	memset(strData_, 0, 16);
	_itoa_s(data, strData_, 16, 10);
}


NodeValue::~NodeValue()
{
	type_ = ERRORS;
}


bool NodeValue::Ok() const
{
	return type_ != ERRORS;
}

void NodeValue::Dump() const
{
	//printf("NodeValue (%s) [0x%p] :\n", Ok() ? "ok" : "ERROR", this);
	printf("\ttype_\t: %i\n", type_);
	printf("\tdata_[int] : %i\n", intData_);
	printf("\tdata_[str] : %s\n", strData_);
}

void NodeValue::Dump(FILE *log) const
{
	assert(log);

	fprintf(log, "NodeValue (%s) [0x%p] :\n", Ok() ? "ok" : "ERROR", this);
	fprintf(log, "\ttype_\t: %i\n", type_);
	fprintf(log, "\tdata_[int] : %i\n", intData_);
	fprintf(log, "\tdata_[str] : %s\n", strData_);
}

