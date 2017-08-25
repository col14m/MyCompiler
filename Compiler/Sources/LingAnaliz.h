#pragma once
#include "BinaryTree.h"

#include <iostream>
#include <vector>
#include <string.h>
#include <array>

#define PARSE_ON_TOKENS(bufAddress) strtok(bufAddress," \n\t")

class LingAnaliz
{
public:
	LingAnaliz(char *text);
	~LingAnaliz();
	int ParseTextAndConvertToArrayNodes();
	bool HaveVariableInDeclaration(char *str);
	int Dump();
	std::vector <BinaryTreeNode> &GetArrayNodes();

private:
	char *ParseVariables();
	int DumpVariables();
	std::vector <BinaryTreeNode> arrayNodes_;
	std::vector <BinaryTreeNode> arrayVariables_;
	char *copyText_;

};



LingAnaliz::LingAnaliz(char *text) :
	copyText_(NULL)
	
{
	assert(text);
	size_t textLen = strnlen(text, 2048);
	copyText_ = new char[textLen + 1];
	strcpy(copyText_, text);

}

LingAnaliz::~LingAnaliz()
{
	delete copyText_;
	copyText_ = NULL;
}
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

int LingAnaliz::ParseTextAndConvertToArrayNodes()
{
	char *pch = NULL;
	char *currentPosit = ParseVariables();
	if (currentPosit != NULL)
	{
		pch = PARSE_ON_TOKENS(currentPosit); //strtok(ParseVariables(), " \n\t");
	}
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
		else if (!strcmp(pch, "else"))
		{
			BinaryTreeNode tmp(NodeValue(ELSE, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (!strcmp(pch, "while"))
		{
			BinaryTreeNode tmp (NodeValue(WHILE, pch));
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
		else if (HaveVariableInDeclaration(pch))
		{
			BinaryTreeNode tmp(NodeValue(VARIABLE, pch));
			arrayNodes_.push_back(tmp);
		}
		else if (pch[0] == '/' && pch[1] == '/')
		{
		}
		else
		{
			BinaryTreeNode tmp(NodeValue(UNKNOWN, pch));
			arrayNodes_.push_back(tmp);
			return 1;
		}
		pch = PARSE_ON_TOKENS(NULL); //strtok(NULL, " \n\t")
	}
	
	return 0;
}

bool LingAnaliz::HaveVariableInDeclaration(char *str)
{
	assert(str);
	for (auto &now : arrayVariables_)
	{
		if (!strcmp(str, now.GetValue().strData_))
		{
			return true;
		}
	}
	
	return false;
}

char *LingAnaliz::ParseVariables()
{
	char *pch = PARSE_ON_TOKENS(copyText_);                    // strtok(copyText_, " \n\t");
	if (!strcmp(pch, "var"))
	{
		pch = PARSE_ON_TOKENS(NULL); // strtok(NULL, " \n\t");
		while (pch != NULL && strcmp(";", pch))
		{
			BinaryTreeNode tmp(NodeValue(VARIABLE, pch));
			arrayVariables_.push_back(tmp);
			pch = PARSE_ON_TOKENS(NULL);// strtok(NULL, " \n\t");

		}
		return pch + 2;
	}
	else
	{
		return NULL;
	}
}


inline int LingAnaliz::Dump()
{
	DumpVariables();
	printf("\n\nDump Tokens\n==============================\n");
	printf("LingAnaliz [0x%p] {\n", this);
	for (auto &now : arrayNodes_)
	{
		now.Dump();
	}
	printf("}\n");
	return 0;
}
std::vector<BinaryTreeNode>& LingAnaliz::GetArrayNodes()
{
	return arrayNodes_;
}
inline int LingAnaliz::DumpVariables()
{
	printf("\n\nDump Variables\n==============================\n");
	printf("LingAnaliz [0x%p] {\n", this);
	for (auto &now : arrayVariables_)
	{
		now.Dump();
	}
	printf("}\n");
	return 0;
}
