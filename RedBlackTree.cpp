#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>
#include <windows.h>
#include "cases.h"
#define DEBUG 1
bool _max = false;
bool firstRBcheck = true;
int hoehe = 0;
using namespace std;



class BinaryTree
{
public:
	BinaryTree *left, *right, *parent;
	int data;
	char color;
	BinaryTree() {};
	BinaryTree(int val);
	string toString()
	{
		stringstream ss;
		ss << this->data << this->color;
		return ss.str();
	}

};


class NilNode : public BinaryTree
{
public:
	NilNode()
	{
		this->left = NULL;
		this->right = NULL;
		this->data = 0;
		this->color = 'b';
	};
};

NilNode* nil = new NilNode;


BinaryTree::BinaryTree(int val) : data(val)
{
	this->left = nil;
	this->right = nil;
	this->color = 'r';
}

BinaryTree *root;

int maxHeight(BinaryTree *p)
{
	if (!p) return 0;
	int leftHeight = maxHeight(p->left);
	int rightHeight = maxHeight(p->right);
	return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

string intToString(int val)
{
	ostringstream ss;
	ss << val;
	return ss.str();
}
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out)
{
	deque<BinaryTree*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel / 2; i++)
	{
		out << ((i == 0) ? setw(startLen - 1) : setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
		out << setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");

	}
	out << endl;
}

void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out)
{
	deque<BinaryTree*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++)
	{
		out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
		out << setw(branchLen + 2) << ((*iter) ? (*iter)->toString() : "");
		out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');

	}
	out << endl;
}

void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out)
{
	deque<BinaryTree*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++)
	{
		out << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? (*iter)->toString() : "");

	}
	out << endl;
}

void printPretty(int level, int indentSpace, ostream& out)
{
	int h = maxHeight(root);
	int nodesInThisLevel = 1;

	int branchLen = 2 * ((int)pow(2.0, h) - 1) - (3 - level)*(int)pow(2.0, h - 1);
	int nodeSpaceLen = 2 + (level + 1)*(int)pow(2.0, h);
	int startLen = branchLen + (3 - level) + indentSpace;

	deque<BinaryTree*> nodesQueue;
	nodesQueue.push_back(root);
	for (int r = 1; r < h; r++)
	{
		printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
		branchLen = branchLen / 2 - 1;
		nodeSpaceLen = nodeSpaceLen / 2 + 1;
		startLen = branchLen + (3 - level) + indentSpace;
		printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

		for (int i = 0; i < nodesInThisLevel; i++)
		{
			BinaryTree *currNode = nodesQueue.front();
			nodesQueue.pop_front();
			if (currNode)
			{
				nodesQueue.push_back(currNode->left);
				nodesQueue.push_back(currNode->right);
			}
			else
			{
				nodesQueue.push_back(NULL);
				nodesQueue.push_back(NULL);
			}
		}
		nodesInThisLevel *= 2;
	}
	printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
	printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}


void rightRotate(BinaryTree* pivot)
{
	BinaryTree* grandFather = pivot->parent->parent;
	if (grandFather != nil)
	{
		grandFather->left = pivot;
		if (DEBUG) cout << "grandFather: " << grandFather->toString() << "->left jetzt: " << grandFather->left->toString() << endl;
	}
	BinaryTree* father = pivot->parent;
	//bool fatherRightChild = (father==father->parent->right);
	if (DEBUG) cout << "right rotate, pivot: " << pivot->toString() << endl;
	father->left = pivot->right;
	if (DEBUG) cout << "father->left jetzt: " << father->left->toString() << endl;
	father->left->parent = father->parent;
	if (DEBUG) cout << "father->left->parent jetzt: " << father->left->parent->toString() << endl;
	pivot->parent = pivot->parent->parent;
	if (DEBUG) cout << "pivot->parent jetzt: " << pivot->parent->toString() << endl;
	pivot->right = father;
	if (DEBUG) cout << "pivot->right jetzt:" << pivot->right->toString() << endl;
	father->parent = pivot;
	if (DEBUG) cout << "father->parent jetzt:" << father->parent->toString() << endl;


	if (root == pivot->right)
		root = pivot;

	/*if(fatherRightChild){
	grandFather->right = pivot;
	cout << "grandFather->right jetzt" << grandFather->right->toString() << endl;
	}
	else{
	grandFather->left=pivot;
	cout << "grandFather->left jetzt: " << grandFather->left->toString() << endl;
	}*/


}

void leftRotate(BinaryTree* pivot)
{
	BinaryTree* grandFather = pivot->parent->parent;
	if (grandFather != nil)
	{
		grandFather->right = pivot;
		if (DEBUG) cout << "grandFather: " << grandFather->toString() << "->right jetzt: " << grandFather->right->toString() << endl;
	}
	BinaryTree* father = pivot->parent;
	//bool fatherRightChild = (father==father->parent->right);
	if (DEBUG) cout << "left rotate, pivot: " << pivot->toString() << endl;
	father->right = pivot->left;
	if (DEBUG) cout << "father->right jetzt: " << father->right->toString() << endl;
	father->right->parent = father;
	if (DEBUG) cout << "father->right->parent jetzt: " << father->right->parent->toString() << endl;
	pivot->parent = pivot->parent->parent;
	if (DEBUG) cout << "pivot->parent jetzt: " << pivot->parent->toString() << endl;
	pivot->left = father;
	if (DEBUG) cout << "pivot->left jetzt:" << pivot->left->toString() << endl;
	father->parent = pivot;
	if (DEBUG) cout << "father->parent jetzt:" << father->parent->toString() << endl;

	if (root == pivot->left)
		root = pivot;

	/*if(fatherRightChild){
	grandFather->right = pivot;
	cout << "grandFather->right jetzt" << grandFather->right->toString() << endl;
	}
	else{
	grandFather->left=pivot;
	cout << "grandFather->left jetzt: " << grandFather->left->toString() << endl;
	}*/
}

void tidy(BinaryTree* aktuell)
{
	//if(aktuell->parent==nil) return;
	while (aktuell->parent->color == 'r')
	{
		if (aktuell->parent == aktuell->parent->parent->left)
		{
			BinaryTree* uncle = aktuell->parent->parent->right;
			/**** fall 1 *******************************/
			if (uncle->color == 'r')
			{
				if (DEBUG) fall1(aktuell->toString());
				aktuell->parent->color = 'b';
				uncle->color = 'b';
				aktuell->parent->parent->color = 'r';
				aktuell = aktuell->parent->parent;
			}

			/**** fall 2 ******************************/
			else
			{
				if (aktuell == aktuell->parent->right)
				{
					aktuell = aktuell->parent;
					if (DEBUG) fall2(aktuell->toString());
					if (aktuell != root)rightRotate(aktuell);
					if (DEBUG)
					{
						cout << "nach 2" << endl;
						printPretty(1, 5, cout);
					}
				}

				 /**** fall 3 ****************************/
				if (DEBUG) fall3(aktuell->toString());
				aktuell->parent->color = 'b';
				aktuell->parent->parent->color = 'r';
				aktuell = aktuell->parent;
				if (aktuell != root)rightRotate(aktuell);
				if (DEBUG)
				{
					cout << "nach 3" << endl;
					printPretty(1, 5, cout);
				}
			}

		}
		else
		{


			if (aktuell->parent == aktuell->parent->parent->right)
			{
				BinaryTree* uncle = aktuell->parent->parent->left;
				/**** fall 4 *********************************/
				if (uncle->color == 'r')
				{
					if (DEBUG) fall4(aktuell->toString());
					aktuell->parent->color = 'b';
					uncle->color = 'b';
					aktuell->parent->parent->color = 'r';
					aktuell = aktuell->parent->parent;
				}

				/**** fall 5 ***********************************/
				else
				{
					if (aktuell == aktuell->parent->right)
					{
						aktuell = aktuell->parent;
						if (DEBUG) fall5(aktuell->toString());
						if (aktuell!=root)leftRotate(aktuell);
						if (DEBUG)
						{
							cout << "nach fuenf" << endl;
							printPretty(1, 5, cout);
						}
					}

					 /**** fall 6 *******************************/
					if (DEBUG) fall6(aktuell->toString());
					aktuell->parent->color = 'b';
					aktuell->parent->parent->color = 'r';
					aktuell = aktuell->parent;
					if (aktuell != root)leftRotate(aktuell);
					else leftRotate(aktuell->right);
					if (DEBUG)
					{
						cout << "nach 6" << endl;
						printPretty(1, 5, cout);
					}
				}

			}

		}
		if (DEBUG)
		{
			root->color = 'b';
			return;
		}
	}
	root->color = 'b';

}

void insertRBtree(BinaryTree* aktuell, int value)
{
	BinaryTree* newNode = new BinaryTree(value);

	while (1)
	{

		if (value < aktuell->data)
		{
			if (aktuell->left == nil)
			{
				newNode->parent = aktuell;
				aktuell->left = newNode;

				if (DEBUG)
				{
					cout << "nach dem einfuegen" << endl;
					printPretty(1, 5, cout);
				}

				tidy(newNode);
				return;
			}
			else aktuell = aktuell->left;
		}
		else if (value > aktuell->data)
		{
			if (aktuell->right == nil)
			{
				newNode->parent = aktuell;
				aktuell->right = newNode;
				if (DEBUG)
				{
					cout << "nach dem einfuegen" << endl;
					printPretty(1, 5, cout);
				}
				tidy(newNode);
				return;
			}
			else aktuell = aktuell->right;

		}
		else
		{
			cout << "fehler beim einfuegen (doppelter schluessel)" << endl;
			return;
		}

	}

}


bool rbCheck(BinaryTree* node)
{
	if (firstRBcheck) {

		while (node != nil) node = node->left;

	}
	firstRBcheck = false;
	int counter = 0;
	BinaryTree* niterator = node;
	if (node->color == 'r'
		&&node->parent != NULL
		&&node->parent->color == 'r') return false;

	if (node->right == NULL&&node->left == NULL)
	{

		while (niterator != root)
		{
			if (!_max&&niterator->color == 'b') hoehe++;
			if (niterator->color == 'b')counter++;
			niterator = niterator->parent;
		}
		_max = true;
		if (counter != hoehe) return false;
	}

	return true;
}


int main()
{
	root = new BinaryTree(8);
	root->parent = nil;
	root->color = 'b';
	insertRBtree(root, 7);
	insertRBtree(root, 6);
	insertRBtree(root, 5);
	insertRBtree(root, 4);
	//insertRBtree(root, 3);
	insertRBtree(root, 9);
	insertRBtree(root, 10);
	/*root->left = new BinaryTree(3);
	root->right = new BinaryTree(7);
	root->left->left = new BinaryTree(2);
	root->left->right = new BinaryTree(4);
	root->right->left = new BinaryTree(6);
	root->right->right = new BinaryTree(8);*/

	/*root->left->left->left = new BinaryTree(5);
	root->left->left->right = new BinaryTree(15);
	root->left->right->right = new BinaryTree(28);
	root->right->right->left = new BinaryTree(41);*/

	string input;
	while (1)
	{
		cin >> input;

		if (input == "pri") printPretty(1, 5, cout);
		else if (input == "ins")
		{
			cout << "enter key!" << endl;
			int inputVal;
			cin >> inputVal;
			insertRBtree(root, inputVal);
		}
		else if (input == "esc") break;
		else if (input == "check") {
			if (rbCheck(root)) cout << "tree correct" << endl;
			else cout << "tree faulty" << endl;
			firstRBcheck = true;
			hoehe = 0;
		}
		else cout << "unknown command" << endl;

	}




	//ofstream fout("tree_pretty.txt");
	// Now print a tree that's more spread out to the file
	//printPretty(root, 5, 0, fout);

	return 0;
}
