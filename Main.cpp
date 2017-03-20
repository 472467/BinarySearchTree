#include "treeNode.h"
#include <iostream>
#include <fstream> 
#include <ctype.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

using namespace std;


void createExpressionTree(char*);
void visualizeTree(TreeNode*);
char* directionsToBalancedNode(int, int, char*&);
bool isNumber(char);
int convertCharToInt(char);
void seperatedInput(char*);
void convertFileInput(char*);
void addNumberToTree(TreeNode*, TreeNode*, TreeNode*);
int convertCharPointerToInt(char*);
void separateInput(char*);
void visualizeTreeUntilMaxDepth(TreeNode*);
void searchAndDelete(TreeNode*, char* input, bool&);


int main(){

	cout << "Would you like to input an expression or textfile (1 = expression, 2 = textfile):\n";
	char* input = new char[2];
	cin.getline(input, 2);
	
	if(input[0] == '2'){//instructions never specified using a while loop to repeatdly get input
		
		cout << "Input file name:\n";
		input = new char[100];
		cin.getline(input, 100);
		
		convertFileInput(input);

	}else{
		
		cout << "Input an expression in infix notation:\n";
		input = new char[50];
		cin.getline(input, 50);
		
		separateInput(input);
	}
	
}

void createExpressionTree(char** seperatedInput){//creates expression tree after the input is converted to postfix, runs through printNode rofl
	TreeNode* head = new TreeNode(NULL, seperatedInput[0]);
	int count = 1;
	for(int x = 0; x < 1000; x++){
		if(strcmp(seperatedInput[x],"null") == 0){
			break;
		}
		cout << seperatedInput[x] << " ";
	}
	cout << "\n";
	while(strcmp(seperatedInput[count], "null") != 0){
		TreeNode* newNode = new TreeNode(NULL, seperatedInput[count]);
		TreeNode* current = head;
		addNumberToTree(head, newNode, current);
		
		count++;
	}
	
	visualizeTreeUntilMaxDepth(head);
	
	cout << "would you like to delete a number? (1 = yes, 2 = no) \n";
	char* input = new char[2];
	cin.getline(input, 2);
	
	if(input[0] == '1'){
		while(true){
			cout << "Enter number to delete: ";
			input = new char[6];
			cin.getline(input, 6);
			
			bool numFound = false;
			searchAndDelete(head, input, numFound);
			
			cout << endl;
			visualizeTreeUntilMaxDepth(head);
			
			cout << "Would you like to delete something else? (1 = yes, 2 = no)\n";
			input = new char[2];
			cin.getline(input, 2);
			if(input[0] != '1'){
				break;
			}
			
		}
		
	}else{
		exit(420);//lel
	}
	
	
}

void addNumberToTree(TreeNode* head, TreeNode* newNode, TreeNode* current){
	if(current != NULL){
		
		
		int newNum = convertCharPointerToInt(newNode->getChar());
		int currentNum = convertCharPointerToInt(current->getChar());
		
		if(newNum >= currentNum){
			if(current->getRight() != NULL){
				
				current = current->getRight();
				addNumberToTree(head, newNode, current);
				
			}else{
				
				current->setRight(newNode);
				newNode->setParent(current);
			}
			
		}else{
			if(current->getLeft() != NULL){
				
				current = current->getLeft();
				addNumberToTree(head, newNode, current);
				
			}else{
				
				current->setLeft(newNode);
				newNode->setParent(current);
				
			}
		}
		
	}else{
		cout << "Current is NULL" << endl;
	}
		
	
}

void searchAndDelete(TreeNode* current, char* input, bool& numberFound){
	if(current != NULL){
		int newNum = convertCharPointerToInt(input);
		int currentNum = convertCharPointerToInt(current->getChar());
		
		if(newNum == currentNum){
			if(!numberFound){
				numberFound = true;
				current->safeDelete();
			}
			
		}else{
			if(current->getLeft() != NULL){
				
				current = current->getLeft();
				searchAndDelete(current, input, numberFound);
				
			}
			
			if(current->getRight() != NULL){
				
				current = current->getRight();
				searchAndDelete(current, input, numberFound);
				
			}
			
		}
		
	}else{
		cout << "Current is NULL" << endl;
	}
	
}

void separateInput(char* input){
	int count = 0;
	int currentLength = 0;
	int numberAmount = 0;
	
	char** seperatedInput = new char*[1000];
	
	for(int x = 0; x < 1000; x++){
		seperatedInput[x] = new char[40];
		strcpy(seperatedInput[x], "null");
	}
	char* currentNum = new char[5];
	
	
	while(input[count] != '\0'){
		char c = input[count];
		
		if(c == ' ' || c == '\n'){
			
			if(currentLength > 0){
				seperatedInput[numberAmount][currentLength] = '\0';
				
				currentLength = 0;
				numberAmount++;
			}
			
		}else{
			seperatedInput[numberAmount][currentLength] = c;
			currentLength++;
			
			if(input[count] != '\0'){
				seperatedInput[numberAmount][currentLength] = '\0';
			}
		}
		
		
		count++;
	}
	
	createExpressionTree(seperatedInput);
}

void convertFileInput(char* f){
	char* input = new char[10000];
	
	int count = 0;
	ifstream fin(f);
	
	if(fin.is_open()){//THIS CONVERTS INPUT TO A LONG ASS INT ARRAY

		cout << "File Opened successfully!!!. Reading data from file into array" << endl;
		
		while(!fin.eof()){
			char c;
			fin.get(c);
			input[count] = c;
			
			count++;
		}
		
		input[count + 1] = '\0';
		cout << input << endl; 
		separateInput(input);
		
	}
	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
	}
	
	
}

int findDeepest(TreeNode* head){
	TreeNode* current = head;
	
	
}

void visualizeTreeUntilMaxDepth(TreeNode* head){
	int currentDepth = 0;
	int depthProgression = 1;
	TreeNode* tCurrent = head;
	bool allNull = false;
	int nullCounter = 0;

	while(!allNull){
		
		char* directions;
		directionsToBalancedNode(currentDepth, depthProgression, directions);//sets direction
		int count = 0;
		while(directions[count] != '\0'){//adds newNode to the most balanced spot by following the directions provided
			if(directions[count] == 'L'){
				if(tCurrent->getLeft() != NULL){
					tCurrent = tCurrent->getLeft();
					
				}else{
					nullCounter++;
					tCurrent = NULL;
					break;
				}
				
			}else{
				if(tCurrent->getRight() != NULL){
					tCurrent = tCurrent->getRight();
				}else{
					nullCounter++;
					tCurrent = NULL;
					break;
				}
			}

			count++;
		}
		
		if(depthProgression == 1){
			cout << currentDepth << ": ";
		}
		if(tCurrent != NULL){
			cout << tCurrent->getChar() << " || ";
		}else{
			cout << " || ";
		}
		
		if(nullCounter == pow(2, currentDepth)){
			allNull = true;
			break;
		}
		
		depthProgression++;
		if(depthProgression > pow(2, currentDepth)){//designates where the most balanced spot on the tree to add next
			nullCounter = 0;
			depthProgression = 1;
			currentDepth++;
			cout << "\n";
		}
		tCurrent = head;
	}
	
	cout << "\n\n";
}

void visualizeTree(TreeNode* head){
	int currentDepth = 0;
	int depthProgression = 1;
	TreeNode* tCurrent = head;

	while(tCurrent != NULL){
		
		if(currentDepth == 0){
			cout << "0: " ;
			cout << tCurrent->getChar() << " || ";
		}else{
			char* directions;
			directionsToBalancedNode(currentDepth, depthProgression, directions);//sets direction
			int count = 0;
			while(directions[count] != '\0'){//adds newNode to the most balanced spot by following the directions provided
				if(directions[count] == 'L'){
					if(tCurrent->getLeft() != NULL){
						tCurrent = tCurrent->getLeft();
					}else{
						tCurrent = NULL;
						break;
					}
					
				}else{
					if(tCurrent->getRight() != NULL){
						tCurrent = tCurrent->getRight();
					}else{
						tCurrent = NULL;
						break;
					}
				}

				count++;
			}
			
			if(tCurrent == NULL){
				break;
			}else{
				if(depthProgression == 1){
					cout << currentDepth << ": ";
				}
				
				cout << tCurrent->getChar() << " || ";
			}
			
		}
		
		depthProgression++;
		if(depthProgression > pow(2, currentDepth)){//designates where the most balanced spot on the tree to add next
			depthProgression = 1;
			currentDepth++;
			cout << "\n";
		}
		if(tCurrent != NULL){
			tCurrent = head;
		}
	}
	
	cout << "\n\n";
}

char* directionsToBalancedNode(int currentDepth, int depthProgression, char*& directions){//this gives directions to next balanced node in the heap
	directions = new char[currentDepth + 1];
	
	for(int x  = currentDepth; x > 0; x--){//builds upwards from the designated location
		if(depthProgression % 2 ==  0){
			directions[x - 1] = 'R';
		}else{
			directions[x - 1] = 'L';
		}
		int newProgression = 1;
		int tProgression =  depthProgression;// 2
		bool running = true;
		
		while(running){
			tProgression =  tProgression -2;
			if(tProgression > 0){
				//cout << tProgression << "TProg"<< endl;
				newProgression++;
			}else{
				//cout << newProgression << endl;
				running = false;
			}
		}
		depthProgression = newProgression;
	}
	directions[currentDepth] = '\0';
	
	return directions;
}

bool isNumber(char c){
	if(c == '0'){
		return true;
	}else if(c == '1'){
		return true;
	}else if(c == '2'){
		return true;
	}else if(c == '3'){
		return true;
	}else if(c == '4'){
		return true;
	}else if(c == '5'){
		return true;
	}else if(c == '6'){
		return true;
	}else if(c == '7'){
		return true;
	}else if(c == '8'){
		return true;
	}else if(c == '9'){
		return true;
	}
	return false;
}

int convertCharPointerToInt(char* c){
	int count = 1;

	int newNum = convertCharToInt(c[0]);

	while(c[count] != '\0'){
		
		newNum = (newNum * 10) + convertCharToInt(c[count]);
		count++;
		
	}
	
	return newNum;
}

int convertCharToInt(char c){
	//cout << c;
	if(c == '0'){
		return 0;
	}else if(c == '1'){
		return 1;
	}else if(c == '2'){
		return 2;
	}else if(c == '3'){
		return 3;
	}else if(c == '4'){
		return 4;
	}else if(c == '5'){
		return 5;
	}else if(c == '6'){
		return 6;
	}else if(c == '7'){
		return 7;
	}else if(c == '8'){
		return 8;
	}else if(c == '9'){
		return 9;
	}
	
	//cout << "error";
	return NULL;
}