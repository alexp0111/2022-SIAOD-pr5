#ifndef RBT
#define RBT

#include <iostream>
#include <fstream>
#include <windows.h>
#include "Record.h"
#include "Item.h"

using namespace std;

struct NodeRBTree {
	Item value;
	char color = 'B'; // R v B;

	NodeRBTree* parent;
	NodeRBTree* left;
	NodeRBTree* right;

	NodeRBTree(Item _val) {
		value = _val;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		color = 'R';
	}

	NodeRBTree(Item _val, NodeRBTree* h) {
		value = _val;
		this->parent = h;
		left = nullptr;
		right = nullptr;
		color = 'R';
	}

	bool hasNoChildren() {
		if (this->left == nullptr && this->right == nullptr) return true;
		return false;
	}
};

struct RBTTree {
	NodeRBTree* root = nullptr;
	Item dflt;

	RBTTree(NodeRBTree* root = nullptr) {
		this->root = nullptr;
	}

	bool is_empty() {
		return root->hasNoChildren();
	}

	void InsertInRBTree(Item _val) {
		NodeRBTree* node = push(_val);
		CorrectRBTree(node);
	}

	NodeRBTree* push(Item _val) {
		if (root == nullptr) {
			NodeRBTree* firstNode = new NodeRBTree(_val);
			firstNode->value = _val;
			root = firstNode;
			return root;
		}

		NodeRBTree* currentNode = root;
		while (true)
		{
			if (_val.getKey() >= currentNode->value.getKey()) {
				if (currentNode->right == nullptr) {
					NodeRBTree* tmp1 = new NodeRBTree(_val, currentNode);

					currentNode->right = tmp1;
					return tmp1;
					break;
				}
				else {
					currentNode = currentNode->right;
				}
			}
			else {
				if (currentNode->left == nullptr) {
					NodeRBTree* tmp2 = new NodeRBTree(_val, currentNode);

					currentNode->left = tmp2;
					return tmp2;
					break;
				}
				else {
					currentNode = currentNode->left;
				}
			}
		}
	}

	void CorrectRBTree(NodeRBTree* x) {
		NodeRBTree* Y;
		while (x != root && x->parent->color == 'R')
		{
			if (x->parent == x->parent->parent->left)
			{
				Y = x->parent->parent->right;
				if (Y && Y->color == 'R')
				{
					Y->color = 'B';
					x->parent->color = 'B';
					x->parent->parent->color = 'R';
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->right)
					{
						x = x->parent;
						rotateLeft(x);
					}
					x->parent->color = 'B';
					x->parent->parent->color = 'R';
					rotateRight(x->parent->parent);
				}
			}
			else
			{
				Y = x->parent->parent->left;
				if (Y && Y->color == 'R')
				{
					Y->color = 'B';
					x->parent->color = 'B';
					x->parent->parent->color = 'R';
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->left)
					{
						x = x->parent;
						rotateRight(x);
					}
					x->parent->color = 'B';
					x->parent->parent->color = 'R';
					rotateLeft(x->parent->parent);
				}
			}
		}
		root->color = 'B';
	}

	void rotateLeft(NodeRBTree* x) {
		NodeRBTree* y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rotateRight(NodeRBTree* x) {
		NodeRBTree* y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void print(NodeRBTree* currentNode, int level) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (currentNode) {
			print(currentNode->right, level + 1);
			for (int i = 0; i < level; i++) cout << "   ";

			if (currentNode->color == 'B') SetConsoleTextAttribute(hConsole, 8);
			else SetConsoleTextAttribute(hConsole, 4);

			cout << currentNode->value.getKey() << endl;
			print(currentNode->left, level + 1);
		}
	}

	// Convert to delete by key
	void deleteByKey(int key) {
		if (!root) return;
		root = deleteNode(root, key);
		NodeRBTree* tmp = getNodeByKey(key, root);
		if (tmp) CorrectRBTree2(tmp);
	}

	NodeRBTree* deleteNode(NodeRBTree* currentNode, int key) {
		if (currentNode->value.key == key) {
			if (!currentNode->left && !currentNode->right)
				return nullptr;

			if (!currentNode->left)
				return currentNode->right;

			if (!currentNode->right)
				return currentNode->left;

			NodeRBTree* minNodeInRightSubtree = findMinElement(currentNode->right);
			currentNode->value = minNodeInRightSubtree->value;

			currentNode->right = this->deleteNode(currentNode->right, minNodeInRightSubtree->value.key);
			return currentNode;
		}

		if (key < currentNode->value.key) {
			if (!currentNode->left) {
				cout << "No such elem" << endl;
				return currentNode;
			}

			currentNode->left = deleteNode(currentNode->left, key);
			return currentNode;
		}

		if (key > currentNode->value.key) {
			if (!currentNode->right) {
				cout << "No such elem" << endl;
				return currentNode;
			}

			currentNode->right = deleteNode(currentNode->right, key);
			return currentNode;
		}
	}

	void CorrectRBTree2(NodeRBTree* x) {
		NodeRBTree* y;
		while (x != root && x->color == 'B')
		{
			if (x == x->parent->left)
			{
				y = x->parent->right;
				if (y && y->color == 'R')
				{
					y->color = 'B';
					x->parent->color = 'R';
					rotateLeft(x->parent);
					y = x->parent->right;
				}
				if (y && y->left->color == 'B' && y->right->color == 'B')
				{
					y->color = 'R';
					x = x->parent;
				}
				else {
					if (y->right->color == 'B') {
						y->left->color = 'B';
						y->color = 'R';
						rotateRight(y);
						y = x->parent->right;
					}
					y->color = x->parent->color;
					x->parent->color = 'B';
					y->right->color = 'B';
					rotateLeft(x->parent);
					x = root;
				}
			}
			else {
				y = x->parent->left;
				if (y && y->color == 'R')
				{
					y->color = 'B';
					x->parent->color = 'R';
					rotateRight(x->parent);
					y = x->parent->left;
				}
				if (y && y->left->color == 'B' && y->right->color == 'B')
				{
					y->color = 'R';
					x = x->parent;
				}
				else {
					if (y->left->color == 'B') {
						y->right->color = 'B';
						y->color = 'R';
						rotateLeft(y);
						y = x->parent->left;
					}
					y->color = x->parent->color;
					x->parent->color = 'B';
					y->left->color = 'B';
					rotateRight(x->parent);
					x = root;
				}
			}
		}
		x->color = 'B';
	}

	NodeRBTree* findMinElement(NodeRBTree* node) {
		if (!node->left) return node;
		return findMinElement(node->left);
	}

	NodeRBTree* getNodeByKey(int key, NodeRBTree* currentNode) {
		if (!currentNode) return nullptr;
		if (currentNode->value.key == key) return currentNode;
		if (currentNode->value.key > key) getNodeByKey(key, currentNode->left);
		else getNodeByKey(key, currentNode->right);
	}

	Item getItemByKey(int key, NodeRBTree* currentNode) {
		if (!currentNode) return dflt;
		if (currentNode->value.key == key) return currentNode->value;
		if (currentNode->value.key > key) getItemByKey(key, currentNode->left);
		else getItemByKey(key, currentNode->right);
	}

	void buildTreeFromFile(ifstream& fb) {
		int counter = 0;
		Record x;

		fb.read((char*)&x, sizeof(Record));
		while (!fb.eof())
		{
			Item item(x.numOfTST, counter);
			counter++;

			this->InsertInRBTree(item);

			fb.read((char*)&x, sizeof(Record));
		}

		cout << "done" << endl;
	}
};

#endif