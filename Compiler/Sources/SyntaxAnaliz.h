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
	
	BinaryTreeNode *GetN();
	BinaryTreeNode *GetT();
	BinaryTreeNode *GetE();
	BinaryTreeNode *GetP();
	
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

void SyntaxAnaliz::Get0()
 {
	 root_ = GetE();
 }

BinaryTreeNode *SyntaxAnaliz::GetRoot()
 {
	return root_;
 }

 BinaryTreeNode *SyntaxAnaliz::GetN()
 {
	 FUNC_HI

	 assert(currentPosition_ <= arrayTokens_.size());
	 if (arrayTokens_[currentPosition_].GetValue().type_ == NUMBER || arrayTokens_[currentPosition_].GetValue().type_ == VARIABLE)
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

 BinaryTreeNode *SyntaxAnaliz::GetE()
 {
	 FUNC_HI
	 BinaryTreeNode *leftChild = GetT();
	 BinaryTreeNode *rightChild = NULL;
	 BinaryTreeNode *parent = NULL;
	 
	 while ((currentPosition_ < arrayTokens_.size())  && arrayTokens_[currentPosition_].GetValue().type_ == PLUS_MINUS)
	 {
		
		 parent = &arrayTokens_[currentPosition_++];
		 rightChild = GetT();
		 parent->InsertLeft(leftChild);
		 parent->InsertRight(rightChild);
		 leftChild = parent;
		 //printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		 //assert(currentPosition_ < arrayTokens_.size());
	 }
	 FUNC_BYE
	 return leftChild;
 }
 BinaryTreeNode *SyntaxAnaliz::GetT()
 {
	 FUNC_HI
	 BinaryTreeNode *leftChild = GetP();
	 BinaryTreeNode *rightChild = NULL;
	 BinaryTreeNode *parent = NULL;

	 while ((currentPosition_ < arrayTokens_.size()) && arrayTokens_[currentPosition_].GetValue().type_ == MUL_DIV)
	 {

		 parent = &arrayTokens_[currentPosition_++];
		 rightChild = GetP();
		 parent->InsertLeft(leftChild);
		 parent->InsertRight(rightChild);
		 leftChild = parent;
		 //printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		 //assert(currentPosition_ < arrayTokens_.size());
	 }
	 FUNC_BYE
	 return leftChild;
 }
 BinaryTreeNode *SyntaxAnaliz::GetP()
 {
	 FUNC_HI
	 BinaryTreeNode *parent = NULL;

	if ((currentPosition_ < arrayTokens_.size()) && arrayTokens_[currentPosition_].GetValue().type_ == BRACKET)
	{
		currentPosition_++;
		parent = GetE();
		assert(arrayTokens_[currentPosition_].GetValue().type_ == BRACKET); //переделать
		currentPosition_++;
		FUNC_BYE
		return parent;
		 //printf("cur %lu\n size %lu\n", currentPosition_, arrayTokens_.size());
		 //assert(currentPosition_ < arrayTokens_.size());
	}
	else
	{
		FUNC_BYE
		return GetN();
	}
 }