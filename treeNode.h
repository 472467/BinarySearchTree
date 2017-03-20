#pragma warning
#ifndef TREENODE_H
#define TREENODE_H

#include <string.h>
#include <iostream>

class TreeNode
{
	private:
		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;
		char* c;
		float id;
	
	public:
		TreeNode(TreeNode*, char*);
		~TreeNode();
		TreeNode(TreeNode*, TreeNode*, char*);
		TreeNode(TreeNode*, TreeNode*, TreeNode*, char*);
		char* getChar();
		void setChar(char*);
		void safeDelete();
		
		TreeNode* getParent();
		void setParent(TreeNode*);
		
		TreeNode* getLeft();
		void setLeft(TreeNode*);
		
		TreeNode* getRight();
		void setRight(TreeNode*);
		int getDepth();
		int convertCharToInt2(char);
		int convertCharPointerToInt2(char*);
		float getID();
};

#endif