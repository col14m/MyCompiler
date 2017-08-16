#pragma once
#include "BinaryTree.h"

#include <iostream>
#include <vector>
#include <string.h>

class LingAnaliz
{
public:
	LingAnaliz();
	~LingAnaliz();
	int ParseTextAndConvertToArrayNodes(char *text);
	int Dump();

private:
	std::vector <BinaryTreeNode> arrayNodes_;

};

bool IsNumber(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{

		if (!isdigit(str[i]))
		{
			return false;
		}
		i++;
	}
	return true;
}

bool IsPlusOrMinus(char *str)
{
	if ((str[0] == '+' || str[0] == '-') && str[1] == '\0')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool IsMulOrDiv(char *str)
{
	if ((str[0] == '*' || str[0] == '/') && str[1] == '\0')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool IsComparison(char *str)
{
	if (str[0] == '<' || str[0] == '>' || !strcmp(str, "=="))
	{
		return true;
	}
	else
	{
		return false;
	}
}
LingAnaliz::LingAnaliz()
{
}

LingAnaliz::~LingAnaliz()
{
}

int LingAnaliz::ParseTextAndConvertToArrayNodes(char *text)
{
	assert(text);
	size_t textLen = strlen(text);
	char *copyText = new char[textLen + 1];
	strcpy(copyText, text);
	char *pch = strtok(copyText, " \n\t");
	
	while (pch != NULL)                         
	{
		if (IsNumber(pch))
		{
			BinaryTreeNode tmp(NodeValue(NUMBER, atoi(pch)));
			arrayNodes_.push_back(tmp);
		}
		else if (IsPlusOrMinus(pch))
		{
			BinaryTreeNode tmp(NodeValue(PLUS_MINUS, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (IsMulOrDiv(pch))
		{
			BinaryTreeNode tmp(NodeValue(MUL_DIV, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (!strcmp (pch, "(") || !strcmp(pch, ")"))
		{
			BinaryTreeNode tmp(NodeValue(BRACKET, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (!strcmp(pch, "="))
		{
			BinaryTreeNode tmp(NodeValue(EQUAL, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (IsComparison(pch))
		{
			BinaryTreeNode tmp(NodeValue(COMPARISON, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (!strcmp(pch, "if"))
		{
			BinaryTreeNode tmp(NodeValue(IF, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (!strcmp(pch, "while"))
		{
			BinaryTreeNode tmp(NodeValue(WHILE, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (!strcmp(pch, "func"))
		{
			BinaryTreeNode tmp(NodeValue(FUNC, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (!strcmp(pch, "ret"))
		{
			BinaryTreeNode tmp(NodeValue(RET, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (!strcmp(pch, ";"))
		{
			BinaryTreeNode tmp(NodeValue(COMMA, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (!strcmp(pch, "//"))
		{
		}
		else
		{
			BinaryTreeNode tmp(NodeValue(UNKNOWN, pch));
			arrayNodes_.push_back(tmp);
		}
		

		pch = strtok(NULL, " \n\t");
	}
	delete copyText;
	return 0;
}

inline int LingAnaliz::Dump()
{
	//printf("LingAnaliz [0x%p] {\n", this);
	for (auto &now : arrayNodes_)
	{
		now.Dump();
	}
	printf("}\n");
	return 0;
}

