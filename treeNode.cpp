#include "treeNode.h"


TreeNode::TreeNode(TreeNode* p, char* n){
	c = n;
	parent = p;
	left = NULL;
	right = NULL;
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, char* n){
	c = n;
	parent = p;
	left = l;
	right = NULL;
}

TreeNode::~TreeNode(){
	delete c;
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, TreeNode* r, char* n){
	c = n;
	parent = p;
	left = l;
	right = r;
}

char* TreeNode::getChar(){
	return c;
}
void TreeNode::setChar(char*  n){
	strcpy(c, n);
}

TreeNode* TreeNode::getParent(){
	return parent;
}
void TreeNode::setParent(TreeNode* p){
	parent = p;
}

TreeNode* TreeNode::getLeft(){
	return left;
}
void TreeNode::setLeft(TreeNode* l){
	left = l;
}

TreeNode* TreeNode::getRight(){
	return right;
}
void TreeNode::setRight(TreeNode* r){
	right = r;
}

void TreeNode::safeDelete(){//removes references to this and relocates current children to replace itself within tree
	int leftNum = 0;
	int rightNum = 0;
	
	if(getLeft() != NULL){
		leftNum  = convertCharPointerToInt(getLeft()->getChar());
	}
	
	if(getRight() != NULL){
		rightNum  = convertCharPointerToInt(getRight()->getChar());
	}


	if(getLeft() == NULL && getRight() == NULL){//no children, easy part
		if(getParent() != NULL){
			if(getParent()->getRight() == NULL){
				getParent()->setLeft(NULL);
				delete this;
			}else if(getParent()->getLeft() == NULL){
				getParent()->setRight(NULL);
				delete this;
			}else{
				if(getParent()->getLeft()[0] == this[0]){
					getParent()->setLeft(NULL);
					delete this;
				}else if(getParent()->getRight()[0] == this[0]){
					getParent()->setRight(NULL);
					delete this;
				}else{
					cout << "CRITICAL ERROR: PARENT CHILDREN NOT EQUIVELENT TO THIS";
					exit(20);
				}
			}
		}else{
			delete this;
			cout << "No more chilren to delete.";
			exit(0);
		}
	}else if(getLeft() != NULL || getRight() != NULL){//left child only , right child only, both
		if(getParent() != NULL){
			
			if(getLeft() != NULL){
				getLeft()->setParent(getParent());
				getParent()->setLeft(getLeft());
			}
			
			if(getRight() != NULL){
				getRight()->setParent(getParent());
				getParent()->setRight(getRight());
			}
			
			delete this;
			
		}else{
			TreeNode* tRight = NULL;
			TreeNode* tLeft = NULL;
			int tChar = getLeft()->getChar();
			
			if(getLeft()->getLeft() != NULL){
				tLeft = getLeft()->getLeft();
			}
			
			if(getLeft()->getRight() != NULL){
				tRight = getLeft()->getRight();
			}
			if(tRight != NULL){
				tRight->setParent(this);
				setRight(tRight);
			}
			
			if(tLeft != NULL){
				tLeft->setParent(this);
				setLeft(tLeft);
			}
			setChar(tChar);
			
			delete (getLeft());
			
		}
	}else{
		cout <<"Error: safeDelete rare exception";
		exit(20);
	}
}

int TreeNode::convertCharPointerToInt(char* c){
	int count = 1;

	int newNum = convertCharToInt(c[0]);

	while(c[count] != '\0'){
		
		newNum = (newNum * 10) + convertCharToInt(c[count]);
		count++;
		
	}
	
	return newNum;
}

int TreeNode::getDepth(){
	TreeNode* current = this;
	int depth = 0;
	while(current != NULL){
		if(current->getParent() != NULL){
			depth++;
			current = current->getParent();
		}else{
			return depth;
		}
	}
	return depth;
}