#pragma once
#include <vector>
#include "BinaryTree.h"

#ifdef DEBUG

#define FUNC_HI printf("\nHi, I am %s!\n", __func__);
#define FUNC_BYE printf("\nBye from %s!\n", __func__);

#else //not DEBUG
#define FUNC_HI
#define FUNC_BYE
#endif //DEBUG


class SyntaxAnaliz
{
public:
	SyntaxAnaliz();
	~SyntaxAnaliz();
	void SetArrayTokens(std::vector <BinaryTreeNode> & arrayNodes);
	int DumpTokens();
	void Get0();
	BinaryTreeNode *GetRoot();	
private:
	size_t currentPosition_;
	BinaryTreeNode *root_;
	std::vector <BinaryTreeNode> arrayTokens_;
	
	BinaryTreeNode *GetN();//number
	BinaryTreeNode *GetM_D();//mul or div
	BinaryTreeNode *GetP_M();//plus or minus
	BinaryTreeNode *GetBR();//bracket
	BinaryTreeNode *GetAs();//assign
	BinaryTreeNode *GetCom();//comma (;)
	BinaryTreeNode *GetWhIf();//while if 
};

SyntaxAnaliz::SyntaxAnaliz() :
	currentPosition_ (0),
	root_ (NULL)
{
}

SyntaxAnaliz::~SyntaxAnaliz()
{
}

void SyntaxAnaliz::SetArrayTokens(std::vector<BinaryTreeNode>& arrayNodes)
{
	arrayTokens_ = arrayNodes;
}

 int SyntaxAnaliz::DumpTokens()
{
	
	printf("\n\nDump Tokens\n==============================\n");
	printf("SyntaxAnaliz [0x%p] {\n", this);
	for (auto &now : arrayTokens_)
	{
		now.Dump();
	}
	printf("}\n");
	return 0;
}

BinaryTreeNode *SyntaxAnaliz::GetRoot()
 {
	return root_;
 }


void SyntaxAnaliz::Get0()
{
	root_ = GetCom();
}

 BinaryTreeNode *SyntaxAnaliz::GetN()
 {
	 FUNC_HI

	 //assert(currentPosition_ <= arrayTokens_.size());
	 if (currentPosition_ < arrayTokens_.size() && 
				(arrayTokens_[currentPosition_].GetValue().type_ == NUMBER || arrayTokens_[currentPosition_].GetValue().type_ == VARIABLE))
	 {
		 FUNC_BYE
		 return &arrayTokens_[currentPosition_++];
	 }
	 else
	 {
		 FUNC_BYE
		 return NULL;
	 }
}

 BinaryTreeNode *SyntaxAnaliz::GetP_M()
 {
	 FUNC_HI
	 BinaryTreeNode *leftChild = GetM_D();
	 BinaryTreeNode *rightChild = NULL;
	 BinaryTreeNode *parent = NULL;
	 
	 while ((currentPosition_ < arrayTokens_.size())  && arrayTokens_[currentPosition_].GetValue().type_ == PLUS_MINUS)
	 {
		
		 parent = &arrayTokens_[currentPosition_++];
		 rightChild = GetM_D();
		 parent->InsertLeft(leftChild);
		 parent->InsertRight(rightChild);
		 leftChild = parent;
		 //printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		 //assert(currentPosition_ < arrayTokens_.size());
	 }
	 FUNC_BYE
	 return leftChild;
 }
 
 BinaryTreeNode *SyntaxAnaliz::GetM_D()
 {
	 FUNC_HI
	 BinaryTreeNode *leftChild = GetBR();
	 BinaryTreeNode *rightChild = NULL;
	 BinaryTreeNode *parent = NULL;

	 while ((currentPosition_ < arrayTokens_.size()) && arrayTokens_[currentPosition_].GetValue().type_ == MUL_DIV)
	 {

		 parent = &arrayTokens_[currentPosition_++];
		 rightChild = GetBR();
		 parent->InsertLeft(leftChild);
		 parent->InsertRight(rightChild);
		 leftChild = parent;
		 //printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		 //assert(currentPosition_ < arrayTokens_.size());
	 }
	 FUNC_BYE
	 return leftChild;
 }
 
 BinaryTreeNode *SyntaxAnaliz::GetBR()
 {
	 FUNC_HI
	 BinaryTreeNode *parent = NULL;

	if ((currentPosition_ < arrayTokens_.size()) && arrayTokens_[currentPosition_].GetValue().type_ == BRACKET)
	{
		currentPosition_++;
		parent = GetP_M();
		arrayTokens_[currentPosition_].Dump();
		printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		assert(arrayTokens_[currentPosition_].GetValue().type_ == BRACKET); //переделать
		currentPosition_++;
		FUNC_BYE
		return parent;
		 //printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		 //assert(currentPosition_ < arrayTokens_.size());
	}
	else
	{
		BinaryTreeNode *node = GetN();
		FUNC_BYE
		return node;
		
	}
 }

 BinaryTreeNode *SyntaxAnaliz::GetAs()//assign
 {
	 FUNC_HI
	 BinaryTreeNode *leftChild = GetP_M();
	 BinaryTreeNode *rightChild = NULL;
	 BinaryTreeNode *parent = NULL;

	 while ((currentPosition_ < arrayTokens_.size()) && arrayTokens_[currentPosition_].GetValue().type_ == ASSIGN)
	 {

		 parent = &arrayTokens_[currentPosition_++];
		 rightChild = GetP_M();
		 parent->InsertLeft(leftChild);
		 parent->InsertRight(rightChild);
		 leftChild = parent;
		 //printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		 //assert(currentPosition_ < arrayTokens_.size());
	 }
	 FUNC_BYE
		 return leftChild;
 }
 
BinaryTreeNode *SyntaxAnaliz::GetCom()//comma (;)
 {
	 FUNC_HI
	 BinaryTreeNode *leftChild = GetWhIf();
	 BinaryTreeNode *rightChild = NULL;
	 BinaryTreeNode *parent = NULL;

	 while ((currentPosition_ < arrayTokens_.size()) && arrayTokens_[currentPosition_].GetValue().type_ == COMMA)
	 {

		 parent = &arrayTokens_[currentPosition_++];
		 printf(" comma cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		 rightChild = GetCom();
		 parent->InsertLeft(leftChild);
		 parent->InsertRight(rightChild);
		 leftChild = parent;
		 //printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		 //assert(currentPosition_ < arrayTokens_.size());
	 }
         FUNC_BYE
		 return leftChild;
 }

BinaryTreeNode *SyntaxAnaliz::GetWhIf()
{
	FUNC_HI
	BinaryTreeNode *parent = NULL;
	BinaryTreeNode *leftChild = NULL;
	BinaryTreeNode *rightChild = NULL;



	if ((currentPosition_ < arrayTokens_.size()) && arrayTokens_[currentPosition_].GetValue().type_ == WHILE)
	{
		parent = &arrayTokens_[currentPosition_++];
		leftChild = GetBR();
		//assert(arrayTokens_[currentPosition_].GetValue().type_ == BRACKET);
		currentPosition_++;
		rightChild = GetCom();
		//arrayTokens_[currentPosition_].Dump();
		assert(arrayTokens_[currentPosition_].GetValue().type_ == BRACE); //переделать
		currentPosition_++;
		parent->InsertLeft(leftChild);
		parent->InsertRight(rightChild);
		FUNC_BYE
		//printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		return parent;
		
		//assert(currentPosition_ < arrayTokens_.size());
	}
	else
	{
		
		BinaryTreeNode *node = GetAs();
		FUNC_BYE
		return node;
	}
}
